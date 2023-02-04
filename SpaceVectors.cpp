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

    void operator+=(SpaceVectors const &);
    void operator-=(SpaceVectors const &);
    void operator*=(SpaceVectors const &);
    void operator/=(SpaceVectors const &);
    void operator+=(ArrayWrapper const &);
    void operator-=(ArrayWrapper const &);
    void operator*=(ArrayWrapper const &);
    void operator/=(ArrayWrapper const &);
    void operator+=(double);
    void operator-=(double);
    void operator*=(double);
    void operator/=(double);

    SpaceVectors operator+(SpaceVectors const &) const ;
    SpaceVectors operator-(SpaceVectors const &) const ;
    SpaceVectors operator*(SpaceVectors const &) const ;
    SpaceVectors operator/(SpaceVectors const &) const ;
    SpaceVectors operator+(ArrayWrapper const &oth) const;
    SpaceVectors operator-(ArrayWrapper const &oth) const;
    SpaceVectors operator*(ArrayWrapper const &oth) const;
    SpaceVectors operator/(ArrayWrapper const &oth) const;
    SpaceVectors operator+(double) const;
    SpaceVectors operator-(double) const;
    SpaceVectors operator*(double) const;
    SpaceVectors operator/(double) const;

    double max() const;
    double min() const;
    void abs();
    SpaceVectors absnew() const ;
    void rand(double, double);
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

void SpaceVectors::operator+=(SpaceVectors const &oth) {
  if ((oth.getDims() != this->dims) || (oth.len() != this->length)) {return;}
  this->x += oth.x;
  this->y += oth.y;
  this->z += oth.z;
}
void SpaceVectors::operator-=(SpaceVectors const &oth) {
  if ((oth.getDims() != this->dims) || (oth.len() != this->length)) {return;}
  this->x -= oth.x;
  this->y -= oth.y;
  this->z -= oth.z;
}
void SpaceVectors::operator*=(SpaceVectors const &oth) {
  if ((oth.getDims() != this->dims) || (oth.len() != this->length)) {return;}
  this->x *= oth.x;
  this->y *= oth.y;
  this->z *= oth.z;
}
void SpaceVectors::operator/=(SpaceVectors const &oth) {
  if ((oth.getDims() != this->dims) || (oth.len() != this->length)) {return;}
  this->x /= oth.x;
  this->y /= oth.y;
  this->z /= oth.z;
}
void SpaceVectors::operator+=(ArrayWrapper const &oth) {
  if (oth.len() != this->length) {return;}
  this->x += oth;
  this->y += oth;
  this->z += oth;
}
void SpaceVectors::operator-=(ArrayWrapper const &oth) {
  if (oth.len() != this->length) {return;}
  this->x -= oth;
  this->y -= oth;
  this->z -= oth;
}
void SpaceVectors::operator*=(ArrayWrapper const &oth) {
  if (oth.len() != this->length) {return;}
  this->x *= oth;
  this->y *= oth;
  this->z *= oth;
}
void SpaceVectors::operator/=(ArrayWrapper const &oth) {
  if (oth.len() != this->length) {return;}
  this->x /= oth;
  this->y /= oth;
  this->z /= oth;
}
void SpaceVectors::operator+=(double a) {
  this->x += a;
  this->y += a;
  this->z += a;
}
void SpaceVectors::operator-=(double a) {
  this->x -= a;
  this->y -= a;
  this->z -= a;
}
void SpaceVectors::operator*=(double a) {
  this->x *= a;
  this->y *= a;
  this->z *= a;
}
void SpaceVectors::operator/=(double a) {
  this->x /= a;
  this->y /= a;
  this->z /= a;
}

SpaceVectors SpaceVectors::operator+(SpaceVectors const &oth) const {
  SpaceVectors retVec = *this;
  retVec += oth;
  return retVec;
}
SpaceVectors SpaceVectors::operator-(SpaceVectors const &oth) const {
  SpaceVectors retVec = *this;
  retVec -= oth;
  return retVec;
}
SpaceVectors SpaceVectors::operator*(SpaceVectors const &oth) const {
  SpaceVectors retVec = *this;
  retVec *= oth;
  return retVec;
}
SpaceVectors SpaceVectors::operator/(SpaceVectors const &oth) const {
  SpaceVectors retVec = *this;
  retVec /= oth;
  return retVec;
}
SpaceVectors SpaceVectors::operator+(ArrayWrapper const &oth) const {
  SpaceVectors retVec = *this;
  retVec += oth;
  return retVec;
}
SpaceVectors SpaceVectors::operator-(ArrayWrapper const &oth) const {
  SpaceVectors retVec = *this;
  retVec -= oth;
  return retVec;
}
SpaceVectors SpaceVectors::operator*(ArrayWrapper const &oth) const {
  SpaceVectors retVec = *this;
  retVec *= oth;
  return retVec;
}
SpaceVectors SpaceVectors::operator/(ArrayWrapper const &oth) const {
  SpaceVectors retVec = *this;
  retVec /= oth;
  return retVec;
}
SpaceVectors SpaceVectors::operator+(double a) const {
  SpaceVectors retVec = *this;
  retVec += a;
  return retVec;
}
SpaceVectors SpaceVectors::operator-(double a) const {
  SpaceVectors retVec = *this;
  retVec -= a;
  return retVec;
}
SpaceVectors SpaceVectors::operator*(double a) const {
  SpaceVectors retVec = *this;
  retVec *= a;
  return retVec;
}
SpaceVectors SpaceVectors::operator/(double a) const {
  SpaceVectors retVec = *this;
  retVec /= a;
  return retVec;
}

double SpaceVectors::max() const{
  if (this->dims == 3) {
    return std::max(std::max(this->x.max(),this->y.max()),this->z.max());
  } else {
    return std::max(this->x.max(),this->y.max());
  }

}
double SpaceVectors::min() const{
  if (this->dims == 3) {
    return std::min(std::min(this->x.min(),this->y.min()),this->z.min());
  } else {
    return std::min(this->x.min(),this->y.min());
  }
}
void SpaceVectors::abs() {
  this->x.abs();
  this->y.abs();
  this->z.abs();
}
SpaceVectors SpaceVectors::absnew() const {
  SpaceVectors retVec = *this;
  retVec.abs();
  return retVec;
}
void SpaceVectors::rand(double min, double max) {
  this->x.rand(min,max);
  this->y.rand(min,max);
  this->z.rand(min,max);
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
  stream << "d"<< this->dims << "n" << this->length << "x";
  this->x.sprint(stream);
  stream << "y";
  this->y.sprint(stream);
  if (dims == 3) {
    stream << "z";
    this->z.sprint(stream);
  }
}


#endif
