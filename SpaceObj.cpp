#ifndef SPACEOBJ
#define SPACEOBJ

#ifndef DIMVECT
#define DIMVECT vector2
#endif

#include <iostream>

#include "vectors.cpp"

class SpaceObj {
public:
  double mass;
  DIMVECT pos;
  DIMVECT vel;

  SpaceObj(double = 1, DIMVECT = DIMVECT(), DIMVECT = DIMVECT());
  SpaceObj(SpaceObj const &);
  ~SpaceObj();
  void operator=(SpaceObj const &);

  bool operator==(SpaceObj const &);
  bool operator!=(SpaceObj const &);
  void print();
  std::string string();
};

SpaceObj::SpaceObj(double mass, DIMVECT pos, DIMVECT vel){
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
  return "Om"+ std::to_string(this->mass) + "p" + this->pos.string() + "v"+ this->vel.string();
}


#endif
