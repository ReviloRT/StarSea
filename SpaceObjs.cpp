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
  void sprint(std::ostream &);
};

SpaceObjs::SpaceObjs(int dims, int numObjs) {
  if (dims != 3) { this->dims = 2; }
  else { this->dims = 3; }
  if (numObjs < 1) { this->numObjs = 0; }
  else { this->numObjs = numObjs; }
  this->mass = ArrayWrapper(this->numObjs,1);
  this->posx = ArrayWrapper(this->numObjs,-1,1);
  this->posy = ArrayWrapper(this->numObjs,-1,1);
  this->velx = ArrayWrapper(this->numObjs,0);
  this->vely = ArrayWrapper(this->numObjs,0);
  if (this->dims == 3){
    this->posz = ArrayWrapper(this->numObjs,-1,1);
    this->velz = ArrayWrapper(this->numObjs,0);
  }
}

void SpaceObjs::print() {
  std::cout << "SpaceObjs: dims "<< this->dims << " num " << this->numObjs << std::endl;
  this->mass.print();
  this->posx.print();
  this->posy.print();
  if (this->dims == 3) { this->posz.print(); }
  this->velx.print();
  this->vely.print();
  if (this->dims == 3) { this->velz.print(); }
}

void SpaceObjs::sprint(std::ostream &stream) {
  stream << "SpaceObjs:d"<< this->dims << "n" << this->numObjs << "m";
  this->mass.sprint(stream);
  stream << "x";
  this->posx.sprint(stream);
  stream << "y";
  this->posy.sprint(stream);
  if (dims == 3 ) {
    stream << "z";
    this->posz.sprint(stream);
  }
  stream << "vx";
  this->velx.sprint(stream);
  stream << "vy";
  this->vely.sprint(stream);
  if (dims == 3) {
    stream << "vz";
    this->velz.sprint(stream);
  }
  stream << std::endl;

}

#endif
