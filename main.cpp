
#define STARSEA_VERSION 1.0

#define DIMVECT vector2

#include <iostream>

#include "vectors.cpp"
#include "SpaceObj.cpp"

int main() {
  std::cout << "StarSea v" << STARSEA_VERSION << std::endl;
  // Initalise two objects
  SpaceObj obj1(1,DIMVECT(-1,0));
  SpaceObj obj2(1,DIMVECT(1,0));

  obj1.print();
  obj2.print();

  // Calculate forces
  double dist = (obj1.pos-obj2.pos).mag();
  double force = obj1.mass * obj2.mass/(dist*dist);
  DIMVECT forceVect = (obj1.pos-obj2.pos).unit() * force;

  // Integration step with euler and dt = 1
  obj1.vel += forceVect/obj1.mass;
  obj2.vel -= forceVect/obj2.mass;
  obj1.pos += obj1.vel;
  obj2.pos += obj2.vel;

  obj1.print();
  obj2.print();

}
