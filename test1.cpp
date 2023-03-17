
#include <iostream>
#include <fstream>

#include "include/vectors.cpp"

#define SAVEFILE "stars.txt"

// 24.1839915231
const int maxObjCount = 100;
const double bigG = -0.0001;
const int displayDims = 3;
const double endTime = 100;
// const double endTime = 24.1839915231;
const double savePeriod = 0.1;
// const double savePeriod = 24.1839915231/100;
const double errorTollerance = 0.0000001;
const double treeSigma = 0.1;
const double softeningConst = 10000000;
const double minMergeDist = 0.00001;

class TreeNode {
public:
  int index;
  vect::vector3 lowBound;
  vect::vector3 size;
  vect::vector3 com;
  double mass;
  TreeNode *child[2][2][2];
  bool isLeaf;

  TreeNode(int newIndex,vect::vector3 lowBound, vect::vector3 size, vect::vector3 *positions);
  // return the box a new object would fit into
  int chooseBox(int newIndex, vect::vector3 *positions);
  // return the new lob bounds for a given child index
  vect::vector3 newBoxLowBounds(int boxIndex);
  // add an object to the correct child (create child if needed)
  void addObj(int newIndex, vect::vector3 *positions);
  // Calculate the force acting on the given index
  vect::vector3 calcForce(int targetIndex, vect::vector3 *positions);
  // Update COMS for the given position list
  vect::vector3 updateCOMS(vect::vector3 *positions);
  // Remove this node and repair tree
  // void popObj();
  ~TreeNode();
};

int objCount = 100;
double dt = 0.1;
double currTime = 0;
int stepCount = 0;
int saveCounter = 0;
TreeNode *root;


const double SQRT21 = std::sqrt(21);
vect::vector3 pos1[maxObjCount];
vect::vector3 pos2[maxObjCount];
vect::vector3 vel1[maxObjCount];
vect::vector3 velCalc[9][maxObjCount];
vect::vector3 accelCalc[9][maxObjCount];
double masses[maxObjCount];


void clearFile() {
  std::fstream file;
  file.open(SAVEFILE,std::ios::out | std::ios::trunc);
  file << displayDims;
  file.close();
}

void saveStep() {
  std::fstream file;
  file.open(SAVEFILE,std::ios::app);
  file << 't' << currTime << 'c' << objCount;
  for (size_t i = 0; i < objCount; i++) {
    file << 'm' << masses[i] << 'p' << pos1[i].string() << 'v' << vel1[i].string();
  }
  file << '\n';
  file.close();
}

void init2BodyTestObjs() {
  objCount = 2;
  masses[0] = 1;
  masses[1] = 1;
  pos1[0] = vect::vector3(-0.5,0,0);
  vel1[0] = vect::vector3(0,0.05,0);
  pos1[1] = vect::vector3(0.5,0,0);
  vel1[1] = vect::vector3(0,-0.05,0);
}

vect::vector3 solveForce(vect::vector3 pos1, vect::vector3 pos2, double mass1, double mass2) {
  vect::vector3 dif = (pos1-pos2);
  double dist2 = dif.sqmag();
  if (dist2 == 0) {dif.zero(); return dif;}
  double fmag = (bigG * mass1 * mass2) / (dist2 * std::sqrt(dist2)) * (1-std::exp(-softeningConst*dist2));
  return dif * fmag;
}

void solveAccelsDirect(vect::vector3 *accels, vect::vector3 *positions) {
  // Clear accels array
  for (size_t i = 0; i < objCount; i++) {
    accels[i] = 0;
  }
  vect::vector3 force;
  // Solve Forces
  for (size_t i = 0; i < objCount; i++) {
    for (size_t j = i+1; j < objCount; j++) {
      // if (i == j) {continue;}
      // vect::vector3 dif = (positions[i]-positions[j]);
      // double dist2 = dif.sqmag();
      // if (dist2 == 0) {accels[i].zero(); accels[j].zero(); continue;}
      // double fmag = (bigG * masses[i]* masses[j] / (dist2 * std::sqrt(dist2)));
      // accels[i] += dif * ( fmag / masses[j]);
      // accels[j] += dif * (-fmag / masses[i]);
      force = solveForce(positions[i],positions[j],masses[i],masses[j]);
      accels[i] += force*masses[j];
      accels[j] += force*-masses[i];
    }
  }
}

TreeNode::TreeNode(int newIndex,vect::vector3 lowBound, vect::vector3 size, vect::vector3 *positions) {
  this->index = newIndex;
  this->com = positions[newIndex];
  this->mass = masses[newIndex];
  this->isLeaf = true;
  this->lowBound = lowBound;
  this->size = size;
  for (size_t i = 0; i < 8; i++) {
    this->child[i%2][i/2%2][i/4] = NULL;
  }
}
int TreeNode::chooseBox(int newIndex, vect::vector3 *positions) {
  return ((positions[newIndex]-this->lowBound)/this->size*vect::vector3(1,2,4)).sum();
}
vect::vector3 TreeNode::newBoxLowBounds(int boxIndex) {
  return this->lowBound + this->size * vect::vector3(boxIndex%2,boxIndex/2%2,boxIndex/4) /2;
}
void TreeNode::addObj(int newIndex, vect::vector3 *positions) {
  int newBox = chooseBox(newIndex, positions);
  if (child[newBox%2][newBox/2%2][newBox/4] == NULL) {
    child[newBox%2][newBox/2%2][newBox/4] = new TreeNode(newIndex,newBoxLowBounds(newBox),this->size/2, positions);
  } else {
    child[newBox%2][newBox/2%2][newBox/4]->addObj(newIndex, positions);
  }

  this->isLeaf = false;
  this->com = this->com/this->mass + positions[newIndex]*masses[newIndex];
  this->mass += masses[newIndex];
  this->com /= this->mass;
}
vect::vector3 TreeNode::calcForce(int targetIndex, vect::vector3 *positions) {
  vect::vector3 retForce;
  if (this->isLeaf) {
    if (this->index != targetIndex) { retForce = solveForce(positions[targetIndex], positions[this->index], masses[targetIndex], masses[this->index])*masses[this->index]; }
    return retForce;
  }
  if (this->index == targetIndex) {
    for (size_t i = 0; i < 8; i++) {
      if (this->child[i%2][i/2%2][i/4] == NULL) {continue;}
      retForce += this->child[i%2][i/2%2][i/4]->calcForce(targetIndex, positions);
    }
  } else {
    if ((this->size.sqmag()/(this->com-pos1[targetIndex]).sqmag()) < treeSigma*treeSigma) {
      retForce = solveForce(positions[targetIndex], this->com, masses[targetIndex], this->mass)*this->mass;
      // std::cout << "Skipped mass: " << this->mass << std::endl;
    } else {
      retForce = solveForce(positions[targetIndex], positions[this->index], masses[targetIndex], masses[this->index])*masses[this->index];
      for (size_t i = 0; i < 8; i++) {
        if (this->child[i%2][i/2%2][i/4] == NULL) {continue;}
        retForce += this->child[i%2][i/2%2][i/4]->calcForce(targetIndex, positions);
      }
    }
  }
  return retForce;

}
vect::vector3 TreeNode::updateCOMS(vect::vector3 *positions) {
  this->com = positions[this->index];
  if (!this->isLeaf) {
    for (size_t i = 0; i < 8; i++) {
      if (this->child[i%2][i/2%2][i/4] == NULL) {continue;}
      this->com += this->child[i%2][i/2%2][i/4]->updateCOMS(positions);
    }
  }
  this->com /= this->mass;
  return this->com;

}
TreeNode::~TreeNode() {
  for (size_t i = 0; i < 8; i++) {
    delete this->child[i%2][i/2%2][i/4];
  }
}

void solveAccelsTree(vect::vector3 *accels, vect::vector3 *positions) {
  root->updateCOMS(positions);
  for (size_t i = 0; i < objCount; i++) {
    accels[i] = root->calcForce(i, positions);
  }
}

void solveEulerIntegration(void (*accelFunc)(vect::vector3 *accels, vect::vector3 *positions)) {
  accelFunc(accelCalc[0], pos1);
  for (size_t i = 0; i < objCount; i++) {
    pos1[i] += vel1[i] * dt;
    vel1[i] += accelCalc[0][i] * dt;
  }
}

void solveRK4Integration(void (*accelFunc)(vect::vector3 *accels, vect::vector3 *positions)) {
  accelFunc(accelCalc[0], pos1);

  for (size_t i = 0; i < objCount; i++) {
    velCalc[0][i] = vel1[i]  +  accelCalc[0][i] * (0.5 * dt);
    pos2[i] = pos1[i] + velCalc[0][i] * (0.5 * dt);
  }
  accelFunc(accelCalc[1], pos2);

  for (size_t i = 0; i < objCount; i++) {
    velCalc[1][i] = vel1[i]  +  accelCalc[1][i] * (0.5 * dt);
    pos2[i] = pos1[i] + velCalc[1][i] * (0.5 * dt);
  }
  accelFunc(accelCalc[2], pos2);

  for (size_t i = 0; i < objCount; i++) {
    velCalc[2][i] = vel1[i]  +  accelCalc[2][i] * (dt);
    pos2[i] = pos1[i] + velCalc[2][i] * (dt);
  }
  accelFunc(accelCalc[3], pos2);

  for (size_t i = 0; i < objCount; i++) {
    pos1[i] += velCalc[0][i] * (1/6.0 * dt) + velCalc[1][i] * (1/3.0 * dt);
    pos1[i] += velCalc[2][i] * (1/3.0 * dt) + velCalc[3][i] * (1/6.0 * dt);
    vel1[i] += accelCalc[0][i] * (1/6.0 * dt) + accelCalc[1][i] * (1/3.0 * dt);
    vel1[i] += accelCalc[2][i] * (1/3.0 * dt) + accelCalc[3][i] * (1/6.0 * dt);
  }


}

void solveRKN76Integration(void (*accelFunc)(vect::vector3 *accels, vect::vector3 *positions)) {
  double error = errorTollerance * 2;
  double lastdt = dt;
  while (error > errorTollerance) {
    accelFunc(accelCalc[0], pos1);

    for (size_t i = 0; i < objCount; i++) {
      pos2[i] = pos1[i] + vel1[i] * (0.1 * dt);
      pos2[i] += accelCalc[0][i] * (1/200.0 * dt * dt);
    }
    accelFunc(accelCalc[1], pos2);

    for (size_t i = 0; i < objCount; i++) {
      pos2[i] = pos1[i] + vel1[i] * (0.2 * dt);
      pos2[i] += accelCalc[0][i] * (1/150.0 * dt * dt);
      pos2[i] += accelCalc[1][i] * (1/75.0 * dt * dt);
    }
    accelFunc(accelCalc[2], pos2);

    for (size_t i = 0; i < objCount; i++) {
      pos2[i] = pos1[i] + vel1[i] * (0.375 * dt);
      pos2[i] += accelCalc[0][i] * (171/8192.0 * dt * dt);
      pos2[i] += accelCalc[1][i] * (45/4096.0 * dt * dt);
      pos2[i] += accelCalc[2][i] * (315/8192.0 * dt * dt);
    }
    accelFunc(accelCalc[3], pos2);

    for (size_t i = 0; i < objCount; i++) {
      pos2[i] = pos1[i] + vel1[i] * (0.5 * dt);
      pos2[i] += accelCalc[0][i] * (5/288.0 * dt * dt);
      pos2[i] += accelCalc[1][i] * (25/528.0 * dt * dt);
      pos2[i] += accelCalc[2][i] * (25/672.0 * dt * dt);
      pos2[i] += accelCalc[3][i] * (16/693.0 * dt * dt);
    }
    accelFunc(accelCalc[4], pos2);

    for (size_t i = 0; i < objCount; i++) {
      pos2[i] = pos1[i] + vel1[i] * ((7-SQRT21)/14.0 * dt);
      pos2[i] += accelCalc[0][i] * ((1003-205*SQRT21)/12348.0 * dt * dt);
      pos2[i] += accelCalc[1][i] * (-25/90552.0*(751-173*SQRT21) * dt * dt);
      pos2[i] += accelCalc[2][i] * (25/43218.0*(624-137*SQRT21) * dt * dt);
      pos2[i] += accelCalc[3][i] * (-128/237699.0*(361-79*SQRT21) * dt * dt);
      pos2[i] += accelCalc[4][i] * ((3411-745*SQRT21)/24696.0 * dt * dt);
    }
    accelFunc(accelCalc[5], pos2);

    for (size_t i = 0; i < objCount; i++) {
      pos2[i] = pos1[i] + vel1[i] * ((7+SQRT21)/14.0 * dt);
      pos2[i] += accelCalc[0][i] * ((793+187*SQRT21)/12348.0 * dt * dt);
      pos2[i] += accelCalc[1][i] * (-25/90552.0*(331+113*SQRT21) * dt * dt);
      pos2[i] += accelCalc[2][i] * (25/43218.0*(1044+247*SQRT21) * dt * dt);
      pos2[i] += accelCalc[3][i] * (-128/9745659.0*(14885+3779*SQRT21) * dt * dt);
      pos2[i] += accelCalc[4][i] * ((3327+797*SQRT21)/24696.0 * dt * dt);
      pos2[i] += accelCalc[5][i] * (-(581+127*SQRT21)/1722.0 * dt * dt);
    }
    accelFunc(accelCalc[6], pos2);

    for (size_t i = 0; i < objCount; i++) {
      pos2[i] = pos1[i] + vel1[i] * (dt);
      pos2[i] += accelCalc[0][i] * (-(157-3*SQRT21)/378.0 * dt * dt);
      pos2[i] += accelCalc[1][i] * (25*(143-10*SQRT21)/2772.0 * dt * dt);
      pos2[i] += accelCalc[2][i] * (-25/3969.0*(876+55*SQRT21) * dt * dt);
      pos2[i] += accelCalc[3][i] * (1280/596673.0*(913+18*SQRT21) * dt * dt);
      pos2[i] += accelCalc[4][i] * (-1/2268.0*(1353+26*SQRT21) * dt * dt);
      pos2[i] += accelCalc[5][i] * (7/4428.0*(1777+377*SQRT21) * dt * dt);
      pos2[i] += accelCalc[6][i] * (7*(5-SQRT21)/36.0 * dt * dt);
    }
    accelFunc(accelCalc[7], pos2);

    for (size_t i = 0; i < objCount; i++) {
      pos2[i] = pos1[i] + vel1[i] * (dt);
      pos2[i] += accelCalc[0][i] * (0.05 * dt * dt);
      pos2[i] += accelCalc[4][i] * (8/45.0 * dt * dt);
      pos2[i] += accelCalc[5][i] * (7/360.0*(7+SQRT21) * dt * dt);
      pos2[i] += accelCalc[6][i] * (7/360.0*(7-SQRT21) * dt * dt);
    }
    accelFunc(accelCalc[8], pos2);

    error = 0;
    vect::vector3 pos8;
    for (size_t i = 0; i < objCount; i++) {
      pos8 = pos1[i] + vel1[i] * (dt);
      pos8 += accelCalc[0][i] * (0.05 * dt * dt);
      pos8 += accelCalc[4][i] * (8/45.0 * dt * dt);
      pos8 += accelCalc[5][i] * (7/360.0*(7+SQRT21) * dt * dt);
      pos8 += accelCalc[6][i] * (7/360.0*(7-SQRT21) * dt * dt);
      pos8 += accelCalc[7][i] * (-0.05 * dt * dt);
      pos8 += accelCalc[8][i] * (0.05 * dt * dt);
      error = std::max(error,(pos2[i]-pos8).mag());
      // std::cout << error << std::endl;
    }
    lastdt = dt;
    if (error != 0){
      dt *= 0.9*std::pow(errorTollerance/error,(1.0/6.0));
    } else {
      dt *= 1.1;
    }
    // std::cout << "Step: " << error << " " << dt << " " << (error > errorTollerance) <<std::endl;

  }
  for (size_t i = 0; i < objCount; i++) {
    pos1[i] = pos2[i];
    vel1[i] += accelCalc[0][i] * (0.05 * lastdt);
    vel1[i] += accelCalc[4][i] * (16/45.0 * lastdt);
    vel1[i] += accelCalc[5][i] * (49/180.0 * lastdt);
    vel1[i] += accelCalc[6][i] * (49/180.0 * lastdt);
    vel1[i] += accelCalc[7][i] * (0.05 * lastdt);
  }
  // std::cout << "FinalStep: " << error << " " << dt << "\n" <<std::endl;
}

void solveMergesDirect() {
  for (size_t i = 0; i < objCount; i++) {
    for (size_t j = i+1; j < objCount; j++) {
      if ((pos1[i]-pos1[j]).sqmag() < minMergeDist*minMergeDist) {
        pos1[i] = (pos1[i]*masses[i] + pos1[j]*masses[j])/(masses[i] + masses[j]);
        vel1[i] = (vel1[i]*masses[i] + vel1[j]*masses[j])/(masses[i] + masses[j]);
        masses[i] = masses[i] + masses[j];
        pos1[j] = pos1[objCount-1];
        vel1[j] = vel1[objCount-1];
        masses[j] = masses[objCount-1];
        objCount --;
      }
    }
  }
}

double solveSystemMomentum() {
  vect::vector3 momentum;
  for (size_t i = 0; i < objCount; i++) {
    momentum += vel1[i] * masses[i];
  }
  return momentum.mag();
}

void solveSystem() {
  while (currTime < endTime) {
    // Solve integration
    // solveEulerIntegration(solveAccelsDirect);
    // solveRK4Integration(solveAccelsDirect);
    solveRKN76Integration(solveAccelsDirect);

    // Build tree
    // delete root;
    // vect::vector3 lowBound = vect::vector3(-1,-1,-1);
    // vect::vector3 highBound = vect::vector3(1,1,1);
    // root = new TreeNode(0,lowBound,highBound-lowBound, pos1);
    // for (size_t i = 1; i < objCount; i++) {
    //   if (pos1[i].lessThan(highBound).all() && pos1[i].greaterThan(lowBound).all()) {
    //     root->addObj(i,pos1);
    //   }
    // }
    // solveRKN76Integration(solveAccelsTree);

    // Ensure z = 0
    if (displayDims == 2) {
      for (size_t i = 0; i < objCount; i++) {
        pos1[i].z = 0;
        vel1[i].z = 0;
      }
    }

    // increment time and stepcount
    currTime += dt;
    stepCount ++;

    // Print status and save step
    std::cout << " S" << saveCounter << "   t" << currTime << "   s" << stepCount << "   dt" << dt << "   o" << objCount << "               \r";
    if (currTime > (saveCounter+1) * savePeriod) {
      // save step
      saveStep();
      std::cout << '\n';
      saveCounter ++;
      stepCount = 0;
    }

    // Limit dt
    dt = std::min(dt, savePeriod/2);
    // dt = std::max(dt,0.000000000001);

    solveMergesDirect();

  }
}

int main() {

  std::srand(0);

  clearFile();

  for (size_t i = 0; i < objCount; i++) {
    pos1[i].rand(-0.25,0.25);
    vel1[i].rand(-0.1,0.1);
    if (displayDims == 2) {
      pos1[i].z = 0;
      vel1[i].z = 0;
    }
    masses[i] = 1;
  }


  // init2BodyTestObjs();

  saveStep();

  double initalMomentum = solveSystemMomentum();

  solveSystem();

  std::cout << "Inital Momentum: " << initalMomentum << "   Final Momentum: " << solveSystemMomentum();

}













// end space
