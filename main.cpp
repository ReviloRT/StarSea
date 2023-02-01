
#define STARSEA_VERSION 1.0

// #define DIM2D
#define DIM3D
#define SAVEFILE "stars.txt"


#ifdef DIM3D
#define DIMVECT vector3
#endif
#ifdef DIM2D
#define DIMVECT vector2
#endif

#include <iostream>
#include <fstream>

#include "vectors.cpp"
#include "SpaceObj.cpp"

void clearFile();
void save(double, SpaceObj, SpaceObj);

int main() {

  std::cout << "StarSea v" << STARSEA_VERSION << std::endl;
  // Initalise two objects
  std::srand(0);
  SpaceObj obj1(1,DIMVECT("rand",-1,1),DIMVECT("rand",-0.1,0.1));
  SpaceObj obj2(1,DIMVECT("rand",-1,1),DIMVECT("rand",-0.1,0.1));

  double time = 0;
  double dt = 0.1;
  double bigG = 1;

  obj1.print();
  obj2.print();

  clearFile();
  save(time,obj1,obj2);

  for (size_t step = 0; step < 100; step++) {
    // Calculate forces
    double dist = (obj1.pos-obj2.pos).mag();
    double force = bigG*obj1.mass * obj2.mass/(dist*dist);
    DIMVECT forceVect = (obj1.pos-obj2.pos).unit() * force;

    // Integration step with euler
    obj1.vel -= forceVect/obj1.mass * dt;
    obj2.vel += forceVect/obj2.mass * dt;
    obj1.pos += obj1.vel * dt;
    obj2.pos += obj2.vel * dt;

    time += dt;

    obj1.print();
    obj2.print();
    save(time,obj1,obj2);
  }

}

void save(double time, SpaceObj obj1, SpaceObj obj2) {
  std::fstream file;
  file.open(SAVEFILE,std::ios::app);
  file << "t=" << time << obj1.string() << obj2.string();
  file << std::endl;
  file.close();
}

void clearFile() {
  std::fstream file;
  file.open(SAVEFILE,std::ios::out | std::ios::trunc);
  #ifdef DIM2D
  file << 2;
  #endif
  #ifdef DIM3D
  file << 3;
  #endif
  file.close();
}
