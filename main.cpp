
#define STARSEA_VERSION 1.0

#define SAVEFILE "stars.txt"

#include <iostream>
#include <fstream>

#include "SpaceObjs.cpp"
#include "ForceSolver.cpp"
#include "Integrator.cpp"

void clearFile();

int main() {
  std::cout << "StarSea v" << STARSEA_VERSION << std::endl;

  std::srand(0);
  clearFile();
  int dims = 2;
  int numObjs = 2;

  SpaceObjs objs(dims,numObjs);
  // objs.pos.rand(-1,1);
  // objs.pos.x.array[0] = 0.5;
  // objs.pos.x.array[1] = -0.5;
  // objs.vel.y.array[0] = 0.05;
  // objs.vel.y.array[1] = -0.05;
  objs.mass.array[0] = 1;
  objs.mass.array[1] = 1;
  objs.pos.x.array[0] = -0.5;
  objs.pos.x.array[1] = 0.5;
  objs.pos.y.array[0] = 0;
  objs.pos.y.array[1] = 0;
  objs.vel.x.array[0] = 0;
  objs.vel.x.array[1] = 0;
  objs.vel.y.array[0] = 0.05;
  objs.vel.y.array[1] = -0.05;
  objs.time = 0;
  // objs.print();

  ForceSolver solver;
  solver.bigG = 0.01;
  solver.method = 0;
  Integrator integrator;
  integrator.method = EulerSimp;
  integrator.dt = 0.01;
  integrator.endTime = 100;
  integrator.savePeriod = 0.5;

  objs = integrator.solve(objs,solver);

  // objs.print();


}

void clearFile() {
  std::fstream file;
  file.open(SAVEFILE,std::ios::out | std::ios::trunc);
  file.close();
}
