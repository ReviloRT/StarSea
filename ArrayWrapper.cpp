#ifndef ARRAY_WRAPPER
#define ARRAY_WRAPPER

#include <cstdlib>
#include <iostream>
#include <iomanip>

double doubleRand(double min = 0, double max = 1) {
  // std::cout << (double(std::rand()) / (double(RAND_MAX) + 1.0))  * (max-min)<< std::endl;
  return (double(std::rand()) / (double(RAND_MAX) + 1.0)) * (max-min) + min;
}

class ArrayWrapper {
public:
  int length;
  double *array;

  ArrayWrapper();
  ArrayWrapper(int,double);
  ArrayWrapper(int,double,double);
  ArrayWrapper(ArrayWrapper const &);
  void operator=(ArrayWrapper const &);
  ~ArrayWrapper();

  void print();
  void sprint(std::ostream &stream);

};

ArrayWrapper::ArrayWrapper() {
  this->length = 0;
  this->array = NULL;
}
ArrayWrapper::ArrayWrapper(int length, double initVal = 0) {
  this->length = length;
  if (this->length <= 0) { this->array = NULL; return;}
  this->array = new double[length];
  for (size_t i = 0; i < length; i++) {
    this->array[i] = initVal;
  }
}
ArrayWrapper::ArrayWrapper(int length, double min, double max) {
  this->length = length;
  if (this->length <= 0) { this->array = NULL; return;}
  this->array = new double[length];
  for (size_t i = 0; i < length; i++) {
    this->array[i] = doubleRand(min,max);
  }
}
ArrayWrapper::ArrayWrapper(ArrayWrapper const &oth) {
  this->length = oth.length;
  if (this->length <= 0) { this->array = NULL; return;}
  this->array = new double[this->length];
  for (size_t ind = 0; ind < this->length; ind++) {
    this->array[ind] = oth.array[ind];
  }
}
void ArrayWrapper::operator=(ArrayWrapper const &oth) {
  delete[] this->array;
  this->length = oth.length;
  if (this->length == 0) { this->array = NULL; return;}
  this->array = new double[this->length];
  for (size_t ind = 0; ind < this->length; ind++) {
    this->array[ind] = oth.array[ind];
  }
}
ArrayWrapper::~ArrayWrapper() {
  delete[] array;
}

void ArrayWrapper::print() {
  std::cout.setf(std::ios::right);
  for (size_t ind = 0; ind < this->length; ind++) {
    std::cout << std::setprecision(3) << std::setw(7) << this->array[ind];
  }
  std::cout << std::endl;
}

void ArrayWrapper::sprint(std::ostream &stream) {
  for (size_t ind = 0; ind < this->length; ind++) {
    stream << this->array[ind] << ",";
  }
}

#endif
