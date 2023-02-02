#ifndef SPACE_VECTORS
#define SPACE_VECTORS

#include <iostream>
#include "ArrayWrapper.cpp"

class SpaceVectors {
  private:
    int dims;
    int length;
  public:
    ArrayWrapper x;
    ArrayWrapper y;
    ArrayWrapper z;

    SpaceVectors();
    SpaceVectors(int, int, double);
    SpaceVectors(int, int, double, double);
    SpaceVectors(SpaceVectors const &oth);
    void operator=(SpaceVectors const &oth);

    int getDims() const ;
    int len() const ;
    void print() const ;
    void sprint(std::ostream &) const ;
};


SpaceVectors::SpaceVectors() {
  this->dims = 2;
  this->length = 0;
}
SpaceVectors::SpaceVectors(int dims, int length, double initVal = 0) {
  if (dims != 3) { this->dims = 2; }
  else { this->dims = 3; }
  if (length < 1) { this->length = 0; }
  else { this->length = length; }
  this->x = ArrayWrapper(this->length,initVal);
  this->y = ArrayWrapper(this->length,initVal);
  if (this->dims == 3){
    this->z = ArrayWrapper(this->length,initVal);
  }
}
SpaceVectors::SpaceVectors(int dims, int length, double min, double max) {
  if (dims != 3) { this->dims = 2; }
  else { this->dims = 3; }
  if (length < 1) { this->length = 0; }
  else { this->length = length; }
  this->x = ArrayWrapper(this->length,min,max);
  this->y = ArrayWrapper(this->length,min,max);
  if (this->dims == 3){
    this->z = ArrayWrapper(this->length,min,max);
  }
}
SpaceVectors::SpaceVectors(SpaceVectors const &oth) {
  this->dims = oth.getDims();
  this->length = oth.length;
  this->x = oth.x;
  this->y = oth.y;
  this->z = oth.z;
}
void SpaceVectors::operator=(SpaceVectors const &oth) {
  this->dims = oth.getDims();
  this->length = oth.length;
  this->x = oth.x;
  this->y = oth.y;
  this->z = oth.z;
}

int SpaceVectors::getDims() const {
  return this->dims;
}

int SpaceVectors::len() const {
  return this->length;
}

void SpaceVectors::print() const {
  std::cout << "SpaceVectors: dims "<< this->dims << " num " << this->length << std::endl;
  this->x.print();
  this->y.print();
  if (this->dims == 3) { this->z.print(); }
}

void SpaceVectors::sprint(std::ostream &stream) const {
  stream << "SpaceVectors:d"<< this->dims << "n" << this->length << "x";
  this->x.sprint(stream);
  stream << "y";
  this->y.sprint(stream);
  if (dims == 3) {
    stream << "z";
    this->z.sprint(stream);
  }
}


#endif
