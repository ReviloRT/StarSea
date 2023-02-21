#ifndef RUNGE_KUTTA_SOLVERS
#define RUNGE_KUTTA_SOLVERS

#include "StandardSolving.cpp"
#include "SpaceTime.cpp"



namespace RK {

const int Euler_BTSize = 1;
const double Euler_BT[1][1] = {{1}};
const int Midpoint_BTSize = 2;
const double Midpoint_BT[2][2] = {{0.5,0},{0,1}};
const int ThreeEigth_BTSize = 4;
const double ThreeEighth_BT[4][4] = {{1/3.0,0,0,0},{-1/3.0,1,0,0},{1,-1,1,0},{1/8.0,3/8.0,3/8.0,1/8.0}};
const int RK4_BTSize = 4;
const double RK4_BT[4][4] = {{1/2.0,0,0,0},{0,1/2.0,0,0},{0,0,1,0},{1/6.0,1/3.0,1/3.0,1/6.0}};

const int HeunEuler_BTSize = 2;
const double HeunEuler_BT[3][2] = {{1,0},{0.5,0.5},{1,0}};
const int RKF45_BTSize = 6;
const double RKF45_BT[7][6] = { {      1/4.0,            0,           0,             0,        0,      0},
                                {     3/32.0,       9/32.0,           0,             0,        0,      0},
                                {1932/2197.0, -7200/2197.0, 7296/2197.0,             0,        0,      0},
                                {  439/216.0,         -8.0,  3680/513.0,   -845/4104.0,        0,      0},
                                {    -8/27.0,          2.0,-3544/2565.0,   1859/4104.0, -11/40.0,      0},
                                {   16/135.0,            0,6656/12825.0, 28561/56430.0,  -9/50.0, 2/55.0},
                                {   25/216.0,            0, 1408/2565.0,   2197/4104.0,   -1/5.0,      0}};

const double RKN76_C[9]    = { 0, 0.1, 0.2, 0.375, 0.5, (7-std::sqrt(21))/14.0, (7+std::sqrt(21))/14.0, 1, 1};
const double RKN76_A[9][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                              {1/200.0, 0, 0, 0, 0, 0, 0, 0},
                              {1/150.0, 1/75.0, 0, 0, 0, 0, 0, 0},
                              {171/8192.0, 45/4096.0, 315/8192.0, 0, 0, 0, 0, 0},
                              {5/288.0, 25/528.0, 25/672.0, 16/693.0, 0, 0, 0, 0},
                              {(1003-205*std::sqrt(21))/12348.0, -25/90552.0*(751-173*std::sqrt(21)), 25/43218.0*(624-137*std::sqrt(21)), -128/237699.0*(361-79*std::sqrt(21)), (3411-745*std::sqrt(21))/24696.0,0,0, 0},
                              {(793+187*std::sqrt(21))/12348.0, -25/90552.0*(331+113*std::sqrt(21)), 25/43218.0*(1044+247*std::sqrt(21)), -128/9745659.0*(14885+3779*std::sqrt(21)), (3327+797*std::sqrt(21))/24696.0,-(581+127*std::sqrt(21))/1722.0,0, 0},
                              {-(157-3*std::sqrt(21))/378.0, 25*(143-10*std::sqrt(21))/2772.0, -25/3969.0*(876+55*std::sqrt(21)), 1280/596673.0*(913+18*std::sqrt(21)),-1/2268.0*(1353+26*std::sqrt(21)), 7/4428.0*(1777+377*std::sqrt(21)),7*(5-std::sqrt(21))/36.0, 0},
                              {0.05,0,0,0,8/45.0,7/360.0*(7+std::sqrt(21)),7/360.0*(7-std::sqrt(21)),0}};
const double RKN76_B[3][9] = {{0.05,0,0,0,8/45.0,7/360.0*(7+std::sqrt(21)),7/360.0*(7-std::sqrt(21)),0,0},
                              {0.05,0,0,0,8/45.0,7/360.0*(7+std::sqrt(21)),7/360.0*(7-std::sqrt(21)),-0.05,0.05},
                              {0.05,0,0,0,16/45.0,49/180.0,49/180.0,0.05,0}};

void solveRKExplicitStep(SSolve::SystemParameters &params, SpaceTime &spt) {
  SSolve::kval *kvals = new SSolve::kval[params.butcherSize];
  SpaceObj *calcState = new SpaceObj[spt.objCount];
  
  for (size_t kind1 = 0; kind1 < params.butcherSize; kind1++) {
    for (size_t ind1 = 0; ind1 < spt.objCount; ind1++) {
      calcState[ind1] = spt.state[ind1];
      for (size_t kind2 = 0; kind2 < kind1; kind2++) {
        double a = (params.dt * *(params.butcherTab + kind1*params.butcherSize + kind2));
        calcState[ind1].pos += kvals[kind2].ka[ind1] * a;
        calcState[ind1].vel += kvals[kind2].kb[ind1] * a;
      }
    }
    kvals[kind1].ka = SSolve::transposeVel(calcState, spt.objCount);
    kvals[kind1].kb = params.forceFunc(params, calcState, spt.objCount);
  }

  for (size_t ind1 = 0; ind1 < spt.objCount; ind1++) {
    for (size_t kind = 0; kind < params.butcherSize; kind++) {
      spt.state[ind1].pos += kvals[kind].ka[ind1] * (params.dt * *(params.butcherTab + (params.butcherSize-1)*params.butcherSize + kind));
      spt.state[ind1].vel += kvals[kind].kb[ind1] * (params.dt * *(params.butcherTab + (params.butcherSize-1)*params.butcherSize + kind));
  }
  spt.time += params.dt;
  
  for (size_t kind = 0; kind < params.butcherSize; kind++) {
    delete[] kvals[kind].ka;
    delete[] kvals[kind].kb;
  }
  delete[] kvals;
  delete[] calcState;
}
}

void solveRKEmbeddedStep(SSolve::SystemParameters &params, SpaceTime &spt) {
  SSolve::kval *kvals = new SSolve::kval[params.butcherSize];
  SpaceObj *calcState = new SpaceObj[spt.objCount];
  double lastdt = 0;
  double error = 1000000;
  
  while (error >= params.errorTollerance) {
    
    for (size_t kind1 = 0; kind1 < params.butcherSize+1; kind1++) {
      for (size_t ind1 = 0; ind1 < spt.objCount; ind1++) {
        calcState[ind1] = spt.state[ind1];
        for (size_t kind2 = 0; kind2 < kind1; kind2++) {
          double a = (params.dt * *(params.butcherTab + (kind1-1)*params.butcherSize + kind2));
          calcState[ind1].pos += kvals[kind2].ka[ind1] * a;
          calcState[ind1].vel += kvals[kind2].kb[ind1] * a;
        }
      }
      kvals[kind1].ka = SSolve::transposeVel(calcState, spt.objCount);
      kvals[kind1].kb = params.forceFunc(params, calcState, spt.objCount);
    }
    
    error = 0;
    vect::vector3 errorPos;
    double indError = 0;
    
    for (size_t ind1 = 0; ind1 < spt.objCount; ind1++) {
      errorPos = spt.state[ind1].pos;
      for (size_t kind = 0; kind < params.butcherSize; kind++) {
        errorPos += kvals[kind].ka[ind1] * (params.dt * *(params.butcherTab + params.butcherSize*params.butcherSize + kind));
      }
      indError = std::abs((calcState[ind1].pos - errorPos).mag());
      if (indError > error) {error = indError;}
    }
    lastdt = params.dt;
    params.dt *= 0.9*std::pow(params.errorTollerance/error,(1.0/(params.butcherSize+1)));
  }
  
  delete[] spt.state;
  spt.state = calcState;
  spt.time += lastdt;
  
  for (size_t kind = 0; kind < params.butcherSize; kind++) {
    delete[] kvals[kind].ka;
    delete[] kvals[kind].kb;
  }
  delete[] kvals;
}

void solveRKN76Step(SSolve::SystemParameters &params, SpaceTime &spt) {
  vect::vector3 *fvals[9];
  vect::vector3 *errorPos = new vect::vector3[spt.objCount];
  SpaceObj *calcState = new SpaceObj[spt.objCount];
  double lastdt = 0;
  double error = 1000000;
    
  // repeat until error is within tollerance
  while (error >= params.errorTollerance) {
    
    // Solve fvals
    for (size_t kind1 = 0; kind1 < 9; kind1++) {
      for (size_t ind1 = 0; ind1 < spt.objCount; ind1++) {
        calcState[ind1] = spt.state[ind1];
        calcState[ind1].pos += calcState[ind1].vel * (RKN76_C[kind1] * params.dt);
        for (size_t kind2 = 0; kind2 < kind1; kind2++) {
          calcState[ind1].pos += fvals[kind2][ind1] * (params.dt * params.dt * RKN76_A[kind1][kind2]);
        }
      }
      
      fvals[kind1] = params.forceFunc(params, calcState, spt.objCount);
    }
    
    
    // Calculate the next state
    for (size_t ind1 = 0; ind1 < spt.objCount; ind1++) {
        calcState[ind1] = spt.state[ind1];
        calcState[ind1].pos += spt.state[ind1].vel * params.dt;
        errorPos[ind1] = calcState[ind1].pos;
        for (size_t kind2 = 0; kind2 < 9; kind2++) {
          calcState[ind1].pos += fvals[kind2][ind1] * (params.dt * params.dt * RKN76_B[0][kind2]);
          calcState[ind1].vel += fvals[kind2][ind1] * (params.dt * RKN76_B[2][kind2]);
          errorPos[ind1] += fvals[kind2][ind1] * (params.dt * params.dt * RKN76_B[1][kind2]);
        }
    }
    
    // Solve for error
    error = 0;
    double indError = 0;
    for (size_t ind1 = 0; ind1 < spt.objCount; ind1++) {
      indError = (errorPos[ind1] - calcState[ind1].pos).mag();
      if (indError > error) {error = indError;}
    }
    
    lastdt = params.dt;
    if (error != 0) {
      params.dt *= 0.9*std::pow(params.errorTollerance/error,(1.0/6.0));
    } else {
      params.dt *= 1.1;
    }
  }
  
  std::cout << "e " << error << " ";
  
  delete[] errorPos;
  delete[] spt.state;
  spt.state = calcState;
  spt.time += lastdt;
  
  for (size_t kind = 0; kind < 9; kind++) {
    delete[] fvals[kind];
  }
}


}


#endif