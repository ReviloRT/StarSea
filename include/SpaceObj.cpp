#ifndef SPACEOBJ
#define SPACEOBJ

#include <iostream>

#include "vectors.cpp"

using namespace vect;

class SpaceObj {
public:
  double mass;
  vector3 pos;
  vector3 vel;

  SpaceObj(double = 1, vector3 = vector3(), vector3 = vector3());
  SpaceObj(SpaceObj const &);
  ~SpaceObj();
  void operator=(SpaceObj const &);

  bool operator==(SpaceObj const &);
  bool operator!=(SpaceObj const &);

  void print();
  std::string string();
};

SpaceObj::SpaceObj(double mass, vector3 pos, vector3 vel){
  this->mass = mass;
  this->pos = pos;
  this->vel = vel;
}
SpaceObj::SpaceObj(SpaceObj const &oth) {
  this->mass = oth.mass;
  this->pos = oth.pos;
  this->vel = oth.vel;
}
void SpaceObj::operator=(SpaceObj const &oth){
  this->mass = oth.mass;
  this->pos = oth.pos;
  this->vel = oth.vel;
}
SpaceObj::~SpaceObj(){
  // std::cout << "Del " << this << std::endl;
}

bool SpaceObj::operator==(SpaceObj const &oth) {
  return (this == &oth);
}
bool SpaceObj::operator!=(SpaceObj const &oth) {
  return (this != &oth);
}

void SpaceObj::print() {
  std::cout << this->string() << std::endl;
}
std::string SpaceObj::string() {
  return "m"+ std::to_string(this->mass) + "p" + this->pos.string() + "v"+ this->vel.string();
}


#endif
