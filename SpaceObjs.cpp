#ifndef SPACE_OBJS
#define SPACE_OBJS

#ifndef SAVEFILE
#define SAVEFILE "stars.txt"
#endif

#include <iostream>
#include <fstream>
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
  SpaceObjs(SpaceObjs const &);
  void operator=(SpaceObjs const &);

  int len() const ;
  void print() const ;
  void sprint(std::ostream &) const ;
  void save() const ;
};

SpaceObjs::SpaceObjs(int dims, int length) : time(0){
  this->time = 0;
  if (length < 1) { this->length = 0; }
  else { this->length = length; }
  this->mass = ArrayWrapper(this->length,1);
  this->pos = SpaceVectors(dims,length);
  this->vel = SpaceVectors(dims,length);
}

SpaceObjs::SpaceObjs(SpaceObjs const &oth){
  this->time = oth.time;
  this->length = oth.len();
  this->mass = oth.mass;
  this->pos = oth.pos;
  this->vel = oth.vel;
}
void SpaceObjs::operator=(SpaceObjs const &oth){
  this->time = oth.time;
  this->length = oth.len();
  this->mass = oth.mass;
  this->pos = oth.pos;
  this->vel = oth.vel;
}

int SpaceObjs::len() const {
  return this->length;
}

void SpaceObjs::print() const {
  std::cout << "SpaceObjs: time " << this->time << " num " << this->length << std::endl << "Mass:" << std::endl;
  this->mass.print();
  std::cout << "Pos: ";
  this->pos.print();
  std::cout << "Vel: ";
  this->vel.print();
}

void SpaceObjs::sprint(std::ostream &stream) const {
  stream << "SpaceObjs:t" <<this->time << "n" << this->length << "m";
  this->mass.sprint(stream);
  stream << "p";
  this->pos.sprint(stream);
  stream << "v";
  this->vel.sprint(stream);
  stream << std::endl;

}

void SpaceObjs::save() const {
  std::fstream file;
  file.open(SAVEFILE,std::ios::app);
  this->sprint(file);
  file.close();
}



#endif
