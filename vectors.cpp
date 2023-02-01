
#ifndef VECTORS
#define VECTORS

#include <cmath>
#include <iostream>
#include <cstdlib>


double doubleRand(double min = 0, double max = 1) {
  // std::cout << (double(std::rand()) / (double(RAND_MAX) + 1.0))  * (max-min)<< std::endl;
  return (double(std::rand()) / (double(RAND_MAX) + 1.0)) * (max-min) + min;

}

class vector2 {
public:
  double x;
  double y;

  // Init Functions
  vector2();
  vector2(double);
  vector2(double,double);
  vector2(vector2 const &);
  ~vector2();

  // Set functions
  void zero();
  void fill(double);
  void set(double, double);
  void rand(double, double);

  // Boolean Operators
  const bool operator==(vector2 const &);
  const bool operator!=(vector2 const &);

  // Basic arithmatic functions with other vectors
  const vector2 operator+(vector2 const &);
  const vector2 operator-(vector2 const &);
  const vector2 operator*(vector2 const &);
  const vector2 operator/(vector2 const &);

  // Basic arithmatic functions with constants
  const vector2 operator+(double);
  const vector2 operator-(double);
  const vector2 operator*(double);
  const vector2 operator/(double);

  // self arithmatic functions with vectors
  void operator=(vector2 const &);
  void operator+=(vector2 const &);
  void operator-=(vector2 const &);
  void operator*=(vector2 const &);
  void operator/=(vector2 const &);

  // self arithmatic functions with constants
  void operator=(double);
  void operator+=(double);
  void operator-=(double);
  void operator*=(double);
  void operator/=(double);

  // special functions
  const double mag();
  const double sqmag();
  const vector2 unit();
  const double max();
  const double min();
  const double dot(vector2 const &);
  const double cross(vector2 const &);

  // Display functions
  const void print();
  const std::string string();

};

vector2::vector2() {
  this->x = 0;
  this->y = 0;
}
vector2::vector2(double a) {
  this->x = a;
  this->y = a;
}
vector2::vector2(double x, double y) {
  this->x = x;
  this->y = y;
}
vector2::vector2(vector2 const &obj) {
  this->x = obj.x;
  this->y = obj.y;
}
vector2::~vector2(){}

void vector2::zero() {
  this->x = 0;
  this->y = 0;
}
void vector2::fill(double a) {
  this->x = a;
  this->y = a;
}
void vector2::set(double x, double y) {
  this->x = x;
  this->y = y;
}
void vector2::rand(double min = 0, double max = 1) {
  this->x = doubleRand(min,max);
  this->y = doubleRand(min,max);
}

const bool vector2::operator==(vector2 const &obj) {
  return ((this->x == obj.x) && (this->y == obj.y));
}
const bool vector2::operator!=(vector2 const &obj) {
  return ((this->x != obj.x) || (this->y != obj.y));
}

const vector2 vector2::operator+(vector2 const &obj) {
  return vector2(this->x + obj.x, this->y + obj.y);
}
const vector2 vector2::operator-(vector2 const &obj) {
  return vector2(this->x - obj.x, this->y - obj.y);
}
const vector2 vector2::operator*(vector2 const &obj) {
  return vector2(this->x * obj.x, this->y * obj.y);
}
const vector2 vector2::operator/(vector2 const &obj) {
  return vector2(this->x / obj.x, this->y / obj.y);
}

const vector2 vector2::operator+(double a) {
  return vector2(this->x + a, this->y + a);
}
const vector2 vector2::operator-(double a) {
  return vector2(this->x - a, this->y - a);
}
const vector2 vector2::operator*(double a) {
  return vector2(this->x * a, this->y * a);
}
const vector2 vector2::operator/(double a) {
  return vector2(this->x / a, this->y / a);
}

void vector2::operator=(vector2 const &obj) {
  this->x = obj.x;
  this->y = obj.y;
}
void vector2::operator+=(vector2 const &obj) {
  this->x += obj.x;
  this->y += obj.y;
}
void vector2::operator-=(vector2 const &obj) {
  this->x -= obj.x;
  this->y -= obj.y;
}
void vector2::operator*=(vector2 const &obj) {
  this->x *= obj.x;
  this->y *= obj.y;
}
void vector2::operator/=(vector2 const &obj) {
  this->x /= obj.x;
  this->y /= obj.y;
}

void vector2::operator=(double a) {
  this->x = a;
  this->y = a;
}
void vector2::operator+=(double a) {
  this->x += a;
  this->y += a;
}
void vector2::operator-=(double a) {
  this->x -= a;
  this->y -= a;
}
void vector2::operator*=(double a) {
  this->x *= a;
  this->y *= a;
}
void vector2::operator/=(double a) {
  this->x /= a;
  this->y /= a;
}

const double vector2::mag() {
  return std::sqrt(this->x*this->x + this->y*this->y);
}
const double vector2::sqmag() {
  return this->x*this->x + this->y*this->y;
}
const vector2 vector2::unit() {
  return *this/this->mag();
}
const double vector2::max(){
  return std::max(this->x,this->y);
}
const double vector2::min(){
  return std::min(this->x,this->y);
}
const double vector2::dot(vector2 const &obj) {
  return this->x * obj.x + this->y * obj.y;
}
const double vector2::cross(vector2 const &obj) {
  return this->x * obj.y - this->y* obj.x;
}

const void vector2::print() {
  std::cout << "x" << this->x << " y" << this->y;
}
const std::string vector2::string() {
  return "x" + std::to_string(this->x) + "y" + std::to_string(this->y);
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
  ~vector3();

  // Set functions
  void zero();
  void fill(double);
  void set(double, double, double);
  void rand(double, double);

  // Boolean Operators
  const bool operator==(vector3 const &);
  const bool operator!=(vector3 const &);

  // Basic Arithmatic operators with vectors
  const vector3 operator+(vector3 const &);
  const vector3 operator-(vector3 const &);
  const vector3 operator*(vector3 const &);
  const vector3 operator/(vector3 const &);

  // Basic Arithmatic operators with constants
  const vector3 operator+(double);
  const vector3 operator-(double);
  const vector3 operator*(double);
  const vector3 operator/(double);

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
  const double mag();
  const double sqmag();
  const vector3 unit();
  const double max();
  const double min();
  const double dot(vector3 const &);
  const vector3 cross(vector3 const &);

  const void print();
  const std::string string();

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

const bool vector3::operator==(vector3 const &obj) {
  return ((this->x == obj.x) && (this->y == obj.y) && (this->z == obj.z));
}
const bool vector3::operator!=(vector3 const &obj) {
  return ((this->x != obj.x) || (this->y != obj.y) || (this->z != obj.z));
}

const vector3 vector3::operator+(vector3 const &obj) {
  return vector3(this->x + obj.x, this->y + obj.y, this->z + obj.z);
}
const vector3 vector3::operator-(vector3 const &obj) {
  return vector3(this->x - obj.x, this->y - obj.y, this->z - obj.z);
}
const vector3 vector3::operator*(vector3 const &obj) {
  return vector3(this->x * obj.x, this->y * obj.y, this->z * obj.z);
}
const vector3 vector3::operator/(vector3 const &obj) {
  return vector3(this->x / obj.x, this->y / obj.y, this->z / obj.z);
}

const vector3 vector3::operator+(double a) {
  return vector3(this->x + a, this->y + a, this->z + a);
}
const vector3 vector3::operator-(double a) {
  return vector3(this->x - a, this->y - a, this->z - a);
}
const vector3 vector3::operator*(double a) {
  return vector3(this->x * a, this->y * a, this->z * a);
}
const vector3 vector3::operator/(double a) {
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

const double vector3::mag() {
  return std::sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}
const double vector3::sqmag() {
  return this->x*this->x + this->y*this->y + this->z*this->z;
}
const vector3 vector3::unit() {
  return *this/this->mag();
}
const double vector3::max(){
  return std::max(std::max(this->x,this->y),this->z);
}
const double vector3::min(){
  return std::min(std::min(this->x,this->y),this->z);
}
const double vector3::dot(vector3 const &obj){
  return this->x*obj.x + this->y * obj.y + this->z * obj.z;
}
const vector3 vector3::cross(vector3 const &obj){
  return vector3(this->y*obj.z-this->z*obj.y, this->z*obj.x-this->x*obj.z,this->x*obj.y-this->y*obj.x);
}


const std::string vector3::string() {
  return "x" + std::to_string(this->x) + "y" + std::to_string(this->y)+ "z" + std::to_string(this->z);
}
const void vector3::print() {
  std::cout << "x" << this->x << " y" << this->y << "z" << this->z;
}


#endif
