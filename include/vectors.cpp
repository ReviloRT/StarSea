
#ifndef VECTORS
#define VECTORS

#include <cmath>
#include <iostream>
#include <cstdlib>

namespace vect {
  
enum VectInitFlag {SET, FILL, FILL2D, RAND, RAND2D, ZERO};

double doubleRand(double min = 0, double max = 1) {
  // std::cout << (double(std::rand()) / (double(RAND_MAX) + 1.0))  * (max-min)<< std::endl;
  return (double(std::rand()) / (double(RAND_MAX) + 1.0)) * (max-min) + min;

}

class vector3 {
public:
  double x;
  double y;
  double z;

  // Init functions
  vector3();
  vector3(double);
  vector3(double,double,double);
  vector3(vector3 const &);
  vector3(VectInitFlag , double, double, double);
  ~vector3();

  // Set functions
  void zero();
  void fill(double);
  void fill2D(double);
  void set(double, double, double);
  void rand(double, double);
  void rand2D(double, double);

  // Boolean Operators
  bool operator==(vector3 const &);
  bool operator!=(vector3 const &);

  // Basic Arithmatic operators with vectors
  vector3 operator+(vector3 const &);
  vector3 operator-(vector3 const &);
  vector3 operator*(vector3 const &);
  vector3 operator/(vector3 const &);

  // Basic Arithmatic operators with constants
  vector3 operator+(double);
  vector3 operator-(double);
  vector3 operator*(double);
  vector3 operator/(double);

  // Self Arithmatic operators with vectors
  void operator=(vector3 const &);
  void operator+=(vector3 const &);
  void operator-=(vector3 const &);
  void operator*=(vector3 const &);
  void operator/=(vector3 const &);

  // Self Arithmatic operators with constants
  void operator=(double);
  void operator+=(double);
  void operator-=(double);
  void operator*=(double);
  void operator/=(double);

  // Special functions
  double mag();
  double sqmag();
  vector3 squared();
  vector3 unit();
  double max();
  double min();
  double dot(vector3 const &);
  vector3 cross(vector3 const &);
  vector3 greaterThan(vector3 const &obj);
  vector3 lessThan(vector3 const &obj);
  bool any();
  bool all();

  void print();
  std::string string();

};

vector3::vector3() {
  this->x = 0;
  this->y = 0;
  this->z = 0;
}
vector3::vector3(double a){
  this->x = a;
  this->y = a;
  this->z = a;
}
vector3::vector3(double x, double y, double z) {
  this->x = x;
  this->y = y;
  this->z = z;
}
vector3::vector3(vector3 const &obj) {
  this->x = obj.x;
  this->y = obj.y;
  this->z = obj.z;
}
vector3::vector3(VectInitFlag flag, double a = 0, double b = 0, double c = 0) {
  switch(flag) {
    case SET : this->set(a,b,c); break;
    case FILL : this->fill(a); break;
    case FILL2D : this->fill2D(a); break;
    case RAND : this->rand(a,b); break;
    case RAND2D : this->rand2D(a,b); break;
    case ZERO : this->zero(); break;
    default : this->zero(); break;
  }
}
vector3::~vector3(){}

void vector3::zero(){
  this->x = 0;
  this->y = 0;
  this->z = 0;
}
void vector3::fill(double a){
  this->x = a;
  this->y = a;
  this->z = a;
}
void vector3::fill2D(double a){
  this->x = a;
  this->y = a;
  this->z = 0;
}
void vector3::set(double x, double y, double z){
  this->x = x;
  this->y = y;
  this->z = z;
}
void vector3::rand(double min = 0, double max = 1){
  this->x = doubleRand(min, max);
  this->y = doubleRand(min, max);
  this->z = doubleRand(min, max);
}
void vector3::rand2D(double min = 0, double max = 1){
  this->x = doubleRand(min, max);
  this->y = doubleRand(min, max);
  this->z = 0;
}

bool vector3::operator==(vector3 const &obj) {
  return ((this->x == obj.x) && (this->y == obj.y) && (this->z == obj.z));
}
bool vector3::operator!=(vector3 const &obj) {
  return ((this->x != obj.x) || (this->y != obj.y) || (this->z != obj.z));
}

vector3 vector3::operator+(vector3 const &obj) {
  return vector3(this->x + obj.x, this->y + obj.y, this->z + obj.z);
}
vector3 vector3::operator-(vector3 const &obj) {
  return vector3(this->x - obj.x, this->y - obj.y, this->z - obj.z);
}
vector3 vector3::operator*(vector3 const &obj) {
  return vector3(this->x * obj.x, this->y * obj.y, this->z * obj.z);
}
vector3 vector3::operator/(vector3 const &obj) {
  return vector3(this->x / obj.x, this->y / obj.y, this->z / obj.z);
}

vector3 vector3::operator+(double a) {
  return vector3(this->x + a, this->y + a, this->z + a);
}
vector3 vector3::operator-(double a) {
  return vector3(this->x - a, this->y - a, this->z - a);
}
vector3 vector3::operator*(double a) {
  return vector3(this->x * a, this->y * a, this->z * a);
}
vector3 vector3::operator/(double a) {
  return vector3(this->x / a, this->y / a, this->z / a);
}

void vector3::operator=(vector3 const &obj) {
  this->x = obj.x;
  this->y = obj.y;
  this->z = obj.z;
}
void vector3::operator+=(vector3 const &obj) {
  this->x += obj.x;
  this->y += obj.y;
  this->z += obj.z;
}
void vector3::operator-=(vector3 const &obj) {
  this->x -= obj.x;
  this->y -= obj.y;
  this->z -= obj.z;
}
void vector3::operator*=(vector3 const &obj) {
  this->x *= obj.x;
  this->y *= obj.y;
  this->z *= obj.z;
}
void vector3::operator/=(vector3 const &obj) {
  this->x /= obj.x;
  this->y /= obj.y;
  this->z /= obj.z;
}

void vector3::operator=(double a) {
  this->x = a;
  this->y = a;
  this->z = a;
}
void vector3::operator+=(double a) {
  this->x += a;
  this->y += a;
  this->z += a;
}
void vector3::operator-=(double a) {
  this->x -= a;
  this->y -= a;
  this->z -= a;
}
void vector3::operator*=(double a) {
  this->x *= a;
  this->y *= a;
  this->z *= a;
}
void vector3::operator/=(double a) {
  this->x /= a;
  this->y /= a;
  this->z /= a;
}

double vector3::mag() {
  return std::sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}
double vector3::sqmag() {
  return this->x*this->x + this->y*this->y + this->z*this->z;
}
vector3 vector3::squared() {
  return vector3((this->x * this->x),(this->y * this->y),(this->z * this->z)) ; 
}
vector3 vector3::unit() {
  return *this/this->mag();
}
double vector3::max(){
  return std::max(std::max(this->x,this->y),this->z);
}
double vector3::min(){
  return std::min(std::min(this->x,this->y),this->z);
}
double vector3::dot(vector3 const &obj){
  return this->x*obj.x + this->y * obj.y + this->z * obj.z;
}
vector3 vector3::cross(vector3 const &obj){
  return vector3(this->y*obj.z-this->z*obj.y, this->z*obj.x-this->x*obj.z,this->x*obj.y-this->y*obj.x);
}
vector3 vector3::greaterThan(vector3 const &obj) {
  return vector3((this->x>obj.x),(this->y>obj.y),(this->z>obj.z)) ; 
}
vector3 vector3::lessThan(vector3 const &obj) {
  return vector3((this->x<obj.x),(this->y<obj.y),(this->z<obj.z)) ; 
}
bool vector3::any() {
  return (this->x != 0) || (this->y != 0) || (this->z != 0);
}
bool vector3::all() {
  return (this->x != 0) && (this->y != 0) && (this->z != 0);
}

std::string vector3::string() {
  return "x" + std::to_string(this->x) + "y" + std::to_string(this->y)+ "z" + std::to_string(this->z);
}
void vector3::print() {
  std::cout << std::setprecision(20) << "x" << this->x << " y" << this->y << "z" << this->z;
}

}

#endif

