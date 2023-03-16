
#include <iostream>
#include <fstream>

#include "include/vectors.cpp"

#define SAVEFILE "stars.txt"

const int maxObjCount = 2;
const double bigG = -0.01;
const int displayDims = 2;
const double endTime = 24.1839915231*10;
const double savePeriod = 24.1839915231/1000;
const double errorTollerance = 0.00000001;

volatile int objCount = 2;
volatile double dt = 24.1839915231/50;
volatile double currTime = 0;
volatile int stepCount = 0;
volatile int saveCounter = 0;

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

void solveAccelsDirect(vect::vector3 *accels, vect::vector3 *positions) {
  // Solve Forces
  for (size_t i = 0; i < objCount; i++) {
    for (size_t j = i+1; j < objCount; j++) {
      if (i == j) {continue;}
      vect::vector3 dif = (positions[i]-positions[j]);
      double dist2 = dif.sqmag();
      if (dist2 == 0) {accels[i].zero(); accels[j].zero(); continue;}
      double fmag = (bigG * masses[i]* masses[j] / (dist2 * std::sqrt(dist2)));
      accels[i] = dif * ( fmag / masses[j]);
      accels[j] = dif * (-fmag / masses[i]);
    }
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
    // pos1[i] += accelCalc[0][i] * (1/6.0 * 1/6.0 * dt * dt) + accelCalc[1][i] * (1/3.0 * 1/3.0 * dt * dt);
    // pos1[i] += accelCalc[2][i] * (1/3.0 * 1/3.0 * dt * dt) + accelCalc[3][i] * (1/6.0 * 1/6.0 * dt * dt);
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
      // dt *= 0.9*std::pow(errorTollerance/error,(1.0/6.0));
    } else {
      // dt *= 1.1;
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
    solveRK4Integration(solveAccelsDirect);
    // solveRKN76Integration(solveAccelsDirect);

    // increment time and stepcount
    currTime += dt;
    stepCount ++;

    // Print status and save step
    std::cout << " S" << saveCounter << "   t" << currTime << "   s" << stepCount << "   dt" << dt <<  "               \r";
    if (currTime > (saveCounter+1) * savePeriod) {
      // save step
      saveStep();
      std::cout << '\n';
      saveCounter ++;
      stepCount = 0;
    }
  }
}

int main() {

  clearFile();

  // for (size_t i = 0; i < objCount; i++) {
  //   pos1[i].rand(-1,1);
  //   vel1[i].rand(-0.05,0.05);
  //   pos1[i].z = 0;
  //   vel1[i].z = 0;
  //   masses[i] = 1;
  // }

  init2BodyTestObjs();

  saveStep();

  double initalMomentum = solveSystemMomentum();

  solveSystem();

  std::cout << "Inital Momentum: " << initalMomentum << "   Final Momentum: " << solveSystemMomentum();

}













// end space
