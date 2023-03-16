
#define STARSEA_VERSION 1.0

#define SAVEFILE "stars.txt"

#include <iostream>
#include <fstream>

#include "include/vectors.cpp"
#include "include/SpaceObj.cpp"
#include "include/SpaceTime.cpp"
#include "include/StandardSolving.cpp"
#include "include/SpaceTreeSolving.cpp"
#include "include/RungeKuttaSolvers.cpp"

void stepFunction(SSolve::SystemParameters &params, SpaceTime &spt) {
  RK::solveRKN76Step(params,spt);
  // SSolve::solveMergesDirect(params,spt);
}

int main() {

  std::cout << "StarSea v" << STARSEA_VERSION << std::endl;
  std::srand(0);


  SSolve::SystemParameters params;
  params.dt = 0.0001;
  params.endTime = 20;
  params.savePeriod = 0.1;
  params.bigG = 0.001;
  params.displayDims = 3;

  params.sigma = 0.05;
  // params.forceFunc = SSolve::solveForcesDirect;
  params.forceFunc = solveForcesGridTree;

  params.unitContactDist = 0.0001;

  params.errorTollerance = 0.000000001;
  params.butcherTab = &RK::RKF45_BT[0][0];
  params.butcherSize = RK::RKF45_BTSize;
  params.stepFunc = stepFunction;

  int objCount = 1000;
  SpaceObj *state = new SpaceObj[objCount];
  for (size_t ind1 = 0; ind1 < objCount; ind1++){
    state[ind1] = SpaceObj(1,vect::vector3(vect::RAND,-0.8,0.8),vect::vector3(vect::RAND,-0.05,0.05));
    // state[ind1] = SpaceObj(1,vect::vector3(vect::RAND,-0.5,0.5),vect::vector3());
    // state[ind1].pos.z = 0;
    // state[ind1].vel.z = 0;
  }
  SpaceTime spaceTime(state,objCount);

  spaceTime.clearFile(params.displayDims);
  spaceTime.save();


  double dp = SSolve::solveSystem(params, spaceTime);
  std::cout << std::endl << "Momentum Change: " << std::setprecision(20) << std::setw(20) << dp << std::endl;


}
