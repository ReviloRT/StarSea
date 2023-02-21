#ifndef SPACE_TREE
#define SPACE_TREE

#include "SpaceObj.cpp"
#include "vectors.cpp"
#include "StandardSolving.cpp"

class spaceTreeNode {
public:
  SpaceObj *obj;
  vect::vector3 highBound;
  vect::vector3 lowBound;
  vect::vector3 size;
  vect::vector3 com;
  double mass;
  bool leaf;
  int index;
  spaceTreeNode *children[2][2][2];
  
  spaceTreeNode(SpaceObj &obj, vect::vector3 highBound, vect::vector3 lowBound) : highBound(highBound), lowBound(lowBound){
	  this->obj = &obj;
    this->com = obj.pos;
    this->mass = obj.mass;
    this->leaf = true;
    this->size = highBound-lowBound;
    for (size_t i = 0; i < 8; i++){
      this->children[i%2][i/2%2][i/2/2] = NULL;
    }
  }
  
  ~spaceTreeNode() {
    for (size_t i = 0; i < 8; i++){
      delete this->children[i%2][i/2%2][i/2/2];
    }
  }
  
  vect::vector3 chooseBox(SpaceObj &obj) {
    return (obj.pos-this->lowBound)*(this->size)*0.5;
  }
  
  vect::vector3 calcChildLowBound(vect::vector3 &ivect) {
    return ivect.greaterThan(1.0) * (this->size)*0.5 + this->lowBound;
  }
  
  vect::vector3 calcChildHighBound(vect::vector3 &ivect) {
    return (ivect.greaterThan(1.0)+1) * (this->size)*0.5 + this->lowBound;
  }
  
  void addNode(SpaceObj &obj) {
    vect::vector3 ivect = this->chooseBox(obj);
    if (this->children[(ivect.x >= 1)][(ivect.y >= 1)][(ivect.z >= 1)] == NULL) {
      this->children[(ivect.x >= 1)][(ivect.y >= 1)][(ivect.z >= 1)] = new spaceTreeNode(obj, this->calcChildHighBound(ivect), this->calcChildLowBound(ivect));
    } else {
      this->children[(ivect.x >= 1)][(ivect.y >= 1)][(ivect.z >= 1)]->addNode(obj);
    }
    this->com = (this->com*this->mass + obj.pos * obj.mass) / (this->mass + obj.mass);
    this->mass = this->mass + obj.mass;
	  this->leaf = false;
  }
  
  vect::vector3 calcForceCOM(SpaceObj &obj1, double bigG) {
   // Calculate forces
    vect::vector3 dif = (this->com-obj1.pos);
    double dist2 = dif.sqmag();
    if (dist2 == 0) {dif.zero(); return dif;}
    dif *= bigG * obj1.mass * this->mass / (dist2 * std::sqrt(dist2));
    return dif;
}
  
  void solveForceRecursive(SpaceObj &obj1, SSolve::SystemParameters params, vect::vector3 &treeForce) {
    if (&obj1 != this->obj) {
      // std::cout << (this->size.max()/(this->com-obj1.pos).mag()) << " " <<(this->com-obj1.pos).mag() << std::endl;
      if ((this->size.max()/(this->com-obj1.pos).mag()) < params.sigma) {
        treeForce += this->calcForceCOM(obj1, params.bigG);
        return;
      }
      treeForce += SSolve::calcForce(obj1, *this->obj, params.bigG);
    }
    if (!this->leaf) {
      for (size_t i = 0; i < 8; i++){
        if (this->children[i%2][i/2%2][i/2/2] == NULL) {continue;}
        this->children[i%2][i/2%2][i/2/2]->solveForceRecursive(obj1, params, treeForce);
      }
    }
  }
  
};


vect::vector3*  solveForcesGridTree(SSolve::SystemParameters &params, SpaceObj *objList, int objCount) {
	spaceTreeNode root = spaceTreeNode(objList[0], vect::vector3(1,1,1), vect::vector3(-1,-1,-1));
	// int outOfBoundsIndexes[objCount];
  // int outOfBoundCount = 0;
	for (size_t ind1 = 1; ind1 < objCount; ind1++) { 
    if ((objList[ind1].pos.greaterThan(root.highBound)).any() || (objList[ind1].pos.lessThan(root.lowBound)).any()) {
      // outOfBoundsIndexes[outOfBoundCount] = ind1;
      // outOfBoundCount ++ ;
      continue;
    }
		root.addNode(objList[ind1]);
	}
	vect::vector3 *forces = new vector3[objCount];
	for (size_t ind1 = 0; ind1 < objCount; ind1++) { 
		root.solveForceRecursive(objList[ind1], params, forces[ind1]);
    forces[ind1] /= objList[ind1].mass;
	}
  // for (size_t outInd1 = 0; outInd1 < outOfBoundCount; outInd1 ++) {
  //   int ind1 = outOfBoundsIndexes[outInd1];
  //   for (size_t outInd2 = 0; outInd2 < outOfBoundCount; outInd2 ++) {
  //     if (outInd1 == outInd2) {continue;}
  //     int ind2 = outOfBoundsIndexes[outInd2];
  //     forces[ind1] += calcForce(objList[ind1],objList[ind2]);
  //   }
  // }
  
	return forces;
}



#endif