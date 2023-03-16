
#define STARSEA_VERSION 1.0

#define SAVEFILE "stars.txt"

#include <iostream>
#include <fstream>

#include "include/vectors.cpp"
#include "include/SpaceObj.cpp"
#include "include/SpaceTime.cpp"
#include "include/StandardSolving.cpp"
#include "include/RungeKuttaSolvers.cpp"

int main() {

  std::cout << "StarSea v" << STARSEA_VERSION << std::endl;

  SSolve::SystemParameters params;
  params.dt = 24.1839915231/100;
  params.endTime = 24.1839915231*1000;
  params.savePeriod = 24.1839915231*10+24.1839915231/100;
  params.bigG = 0.01;
  params.displayDims = 2;

  params.forceFunc = SSolve::solveForcesDirect;

  params.errorTollerance = 0.000000000001;
  params.butcherTab = &RK::RK4_BT[0][0];
  params.butcherSize = RK::RK4_BTSize;
  // params.butcherTab = &RK::RKF45_BT[0][0];
  // params.butcherSize = RK::RKF45_BTSize;
  // params.stepFunc = RK::solveRKExplicitStep;
  // params.stepFunc = RK::solveRKEmbeddedStep;
  params.stepFunc = RK::solveRKN76Step;
  // params.stepFunc = SSolve::solveEulerStep;

  int objCount = 2;
  SpaceObj *state = new SpaceObj[objCount];
  state[0] = SpaceObj(1,vect::vector3(-0.5,0,0),vect::vector3(0,0.05,0));
  state[1] = SpaceObj(1,vect::vector3(0.5,0,0),vect::vector3(0,-0.05,0));
  SpaceTime spaceTime(state,objCount);

  spaceTime.clearFile(2);
  spaceTime.save();

  double dp = SSolve::solveSystem(params, spaceTime);
  std::cout << std::endl << "Momentum Change: " << std::setprecision(20) << std::setw(20) << dp << std::endl;


}
