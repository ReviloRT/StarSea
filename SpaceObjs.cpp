#ifndef SPACE_OBJS
#define SPACE_OBJS

#include <iostream>
#include "ArrayWrapper.cpp"
#include "SpaceVectors.cpp"


class SpaceObjs {
private:
  int length;
public:
  double time;
  ArrayWrapper mass;
  SpaceVectors pos;
  SpaceVectors vel;

  SpaceObjs(int, int);

  int len() const ;
  void print() const ;
  void sprint(std::ostream &) const ;
};

SpaceObjs::SpaceObjs(int dims, int length) : time(0){
  this->time = 0;
  if (length < 1) { this->length = 0; }
  else { this->length = length; }
  this->mass = ArrayWrapper(this->length,1);
  this->pos = SpaceVectors(dims,length);
  this->vel = SpaceVectors(dims,length);
}

int SpaceObjs::len() const {
  return this->length;
}

void SpaceObjs::print() const {
  std::cout << "SpaceObjs: time " << this->time << " num " << this->length << std::endl;
  this->mass.print();
  this->pos.print();
  this->vel.print();
}

void SpaceObjs::sprint(std::ostream &stream) const {
  stream << "SpaceObjs:t" <<this->time << "n" << this->length << "m";
  this->mass.sprint(stream);
  stream << "x";
  this->pos.sprint(stream);
  stream << "y";
  this->vel.sprint(stream);
  stream << std::endl;

}





#endif
