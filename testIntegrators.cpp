
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

  const int testNum = 2;
  SolveMethod testMethods[testNum] = {Rkf45,DormPrince};

  SpaceObjs objs(dims,numObjs);
  ForceSolver solver;
  Integrator integrator;
  for (size_t i = 0; i < testNum; i++) {
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

    std::cout << "Solver " << testMethods[i] << std::endl;
    solver.bigG = 0.01;
    solver.method = 0;
    integrator.method = testMethods[i];
    integrator.errorTol = 0.00000001;
    integrator.dt = 0.000001;
    integrator.endTime = 24.1839915231*10000;
    integrator.savePeriod = 24.1839915231*100;
    // if (i == 0) {integrator.usePosError = true;} else {integrator.usePosError = false;}

    objs = integrator.solve(objs,solver);
  }

}

void clearFile() {
  std::fstream file;
  file.open(SAVEFILE,std::ios::out | std::ios::trunc);
  file.close();
}
