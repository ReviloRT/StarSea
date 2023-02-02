#ifndef SPACE_OBJS
#define SPACE_OBJS

#include <iostream>
#include "ArrayWrapper.cpp"

class SpaceObjs {
public:
  int dims;
  int numObjs;
  ArrayWrapper mass;
  ArrayWrapper posx;
  ArrayWrapper posy;
  ArrayWrapper posz;
  ArrayWrapper velx;
  ArrayWrapper vely;
  ArrayWrapper velz;

  SpaceObjs(int, int);

  void print();
};

SpaceObjs::SpaceObjs(int dims, int numObjs) {
  this->dims = dims;
  this->numObjs = numObjs;
  this->mass = ArrayWrapper(numObjs,1);
  this->posx = ArrayWrapper(numObjs,-1,1);
  this->posy = ArrayWrapper(numObjs,-1,1);
  this->velx = ArrayWrapper(numObjs,0);
  this->vely = ArrayWrapper(numObjs,0);
  if (this->dims == 3){
    this->posz = ArrayWrapper(numObjs,-1,1);
    this->velz = ArrayWrapper(numObjs,0);
  }
}

void SpaceObjs::print() {
  std::cout << "SpaceObjs: dims = " << this->dims << " objs = " << this->numObjs << std::endl;
  this->mass.print();
  this->posx.print();
  this->posy.print();
  if (this->dims == 3) { this->posz.print(); }
  this->velx.print();
  this->vely.print();
  if (this->dims == 3) { this->velz.print(); }
}

#endif
