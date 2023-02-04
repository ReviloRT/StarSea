#ifndef INTEGRATOR
#define INTEGRATOR

#include "SpaceObjs.cpp"
#include "ForceSolver.cpp"
#include <cmath>

enum SolveMethod { Euler, Midpoint, Huen, Rals3rd, Rk4, Rals4th, EulerSimp, HuenEuler, BogSham, Rkf45, DormPrince };

class Integrator {
public:
  double dt;
  double endTime;
  double savePeriod;
  SolveMethod method;
  double errorTol;
  bool usePosError;
  Integrator();
  SpaceObjs solveStepEuler(SpaceObjs,ForceSolver &);
  SpaceObjs solveStepMidpoint(SpaceObjs,ForceSolver &);
  SpaceObjs solveStepHuen(SpaceObjs,ForceSolver &);
  SpaceObjs solveStepRalstons3rd(SpaceObjs,ForceSolver &);
  SpaceObjs solveStepRK4(SpaceObjs,ForceSolver &);
  SpaceObjs solveStepRalstons4th(SpaceObjs,ForceSolver &);
  SpaceObjs solveStepHuenEuler(SpaceObjs,ForceSolver &);
  SpaceObjs solveStepEulerSimp(SpaceObjs,ForceSolver &);
  SpaceObjs solveStepBogSham(SpaceObjs,ForceSolver &);
  SpaceObjs solveStepRKF45(SpaceObjs,ForceSolver &);
  SpaceObjs solveStepDormandPrince(SpaceObjs,ForceSolver &);
  SpaceObjs solve(SpaceObjs &,ForceSolver &);
  double systemMomentum(SpaceObjs &objs);
  double systemKinetic(SpaceObjs &objs);


};

Integrator::Integrator() {
  this->dt = 0.1;
  this->endTime = 10.0;
  this->savePeriod = 1.0;
  this->method = Euler;
  this->errorTol = 1;
  this->usePosError = false;
}

SpaceObjs Integrator::solveStepEuler(SpaceObjs objs, ForceSolver &forceSolver) {
  SpaceVectors k1 = forceSolver.solve(objs)/objs.mass;
  objs.pos += objs.vel * this->dt;
  objs.vel += k1 * this->dt;
  objs.time += this->dt;
  return objs;
}

SpaceObjs Integrator::solveStepMidpoint(SpaceObjs objs, ForceSolver &forceSolver) {
  SpaceVectors k1a = objs.vel;
  SpaceVectors k1b = forceSolver.solve(objs)/objs.mass;

  SpaceObjs objs2 = objs;
  objs2.pos += k1a * this->dt/2;
  objs2.vel += k1b * this->dt/2;

  SpaceVectors k2a = objs2.vel;
  SpaceVectors k2b = forceSolver.solve(objs2)/objs2.mass;

  objs.pos += k2a * this->dt;
  objs.vel += k2b * this->dt;
  objs.time += this->dt;
  return objs;
}

SpaceObjs Integrator::solveStepHuen(SpaceObjs objs, ForceSolver &forceSolver) {
  SpaceVectors k1a = objs.vel;
  SpaceVectors k1b = forceSolver.solve(objs)/objs.mass;

  SpaceObjs objs2 = objs;
  objs2.pos += k1a * this->dt;
  objs2.vel += k1b * this->dt;

  SpaceVectors k2a = objs2.vel;
  SpaceVectors k2b = forceSolver.solve(objs2)/objs2.mass;

  objs.pos += (k1a+k2a)/2 * this->dt;
  objs.vel += (k1b+k2b)/2 * this->dt;
  objs.time += this->dt;
  return objs;
}

SpaceObjs Integrator::solveStepRalstons3rd(SpaceObjs objs, ForceSolver &forceSolver) {
  SpaceVectors k1a = objs.vel;
  SpaceVectors k1b = forceSolver.solve(objs)/objs.mass;

  SpaceObjs objs2 = objs;
  objs2.pos += k1a * (this->dt/2.0);
  objs2.vel += k1b * (this->dt/2.0);

  SpaceVectors k2a = objs2.vel;
  SpaceVectors k2b = forceSolver.solve(objs2)/objs2.mass;

  objs2 = objs;
  objs2.pos += k2a * (3.0/4.0*this->dt);
  objs2.vel += k2b * (3.0/4.0*this->dt);

  SpaceVectors k3a = objs2.vel;
  SpaceVectors k3b = forceSolver.solve(objs2)/objs2.mass;

  objs.pos += k1a*(2.0/9.0*this->dt) + k2a*(1.0/3.0*this->dt) + k3a*(4.0/9.0*this->dt);
  objs.vel += k1b*(2.0/9.0*this->dt) + k2b*(1.0/3.0*this->dt) + k3b*(4.0/9.0*this->dt);
  objs.time += this->dt;
  return objs;
}

SpaceObjs Integrator::solveStepRK4(SpaceObjs objs, ForceSolver &forceSolver) {
  SpaceVectors k1a = objs.vel;
  SpaceVectors k1b = forceSolver.solve(objs)/objs.mass;

  SpaceObjs objs2 = objs;
  objs2.pos += k1a * (this->dt/2.0);
  objs2.vel += k1b * (this->dt/2.0);

  SpaceVectors k2a = objs2.vel;
  SpaceVectors k2b = forceSolver.solve(objs2)/objs2.mass;

  objs2 = objs;
  objs2.pos += k2a * (this->dt/2.0);
  objs2.vel += k2b * (this->dt/2.0);

  SpaceVectors k3a = objs2.vel;
  SpaceVectors k3b = forceSolver.solve(objs2)/objs2.mass;

  objs2 = objs;
  objs2.pos += k3a * this->dt;
  objs2.vel += k3b * this->dt;

  SpaceVectors k4a = objs2.vel;
  SpaceVectors k4b = forceSolver.solve(objs2)/objs2.mass;

  objs.pos += k1a*(1.0/6.0*this->dt) + k2a*(1.0/3.0*this->dt) + k3a*(1.0/3.0*this->dt) + k4a*(1.0/6.0*this->dt) ;
  objs.vel += k1b*(1.0/6.0*this->dt) + k2b*(1.0/3.0*this->dt) + k3b*(1.0/3.0*this->dt) + k4b*(1.0/6.0*this->dt);
  objs.time += this->dt;
  return objs;
}

SpaceObjs Integrator::solveStepRalstons4th(SpaceObjs objs, ForceSolver &forceSolver) {
  SpaceVectors k1a = objs.vel;
  SpaceVectors k1b = forceSolver.solve(objs)/objs.mass;

  SpaceObjs objs2 = objs;
  objs2.pos += k1a*(this->dt*0.4);
  objs2.vel += k1b*(this->dt*0.4);

  SpaceVectors k2a = objs2.vel;
  SpaceVectors k2b = forceSolver.solve(objs2)/objs2.mass;

  objs2 = objs;
  objs2.pos += k1a*(0.29697761*this->dt) + k2a*(0.15875964*this->dt);
  objs2.vel += k1b*(0.29697761*this->dt) + k2b*(0.15875964*this->dt);

  SpaceVectors k3a = objs2.vel;
  SpaceVectors k3b = forceSolver.solve(objs2)/objs2.mass;

  objs2 = objs;
  objs2.pos += k1a*(0.21810040*this->dt) + k2a*(-3.05096516*this->dt) + k3a*(3.83286476*this->dt);
  objs2.vel += k1b*(0.21810040*this->dt) + k2b*(-3.05096516*this->dt) + k3b*(3.83286476*this->dt);

  SpaceVectors k4a = objs2.vel;
  SpaceVectors k4b = forceSolver.solve(objs2)/objs2.mass;

  objs.pos += k1a*(0.17476028*this->dt) + k2a*(-0.55148066*this->dt) + k3a*(1.20552560*this->dt) + k4a*(0.17118478*this->dt);
  objs.vel += k1b*(0.17476028*this->dt) + k2b*(-0.55148066*this->dt) + k3b*(1.20552560*this->dt) + k4b*(0.17118478*this->dt);
  objs.time += this->dt;
  return objs;
}

SpaceObjs Integrator::solveStepHuenEuler(SpaceObjs objs, ForceSolver &forceSolver) {
  SpaceVectors k1a = objs.vel;
  SpaceVectors k1b = forceSolver.solve(objs)/objs.mass;

  SpaceObjs objs2 = objs;
  objs2.pos += k1a * this->dt;
  objs2.vel += k1b * this->dt;

  SpaceVectors errorVect;
  if (this->usePosError) { errorVect = objs2.pos; }
  else { errorVect = objs2.vel; }


  SpaceVectors k2a = objs2.vel;
  SpaceVectors k2b = forceSolver.solve(objs2)/objs2.mass;

  objs.pos += (k1a+k2a)/2.0 * this->dt;
  objs.vel += (k1b+k2b)/2.0 * this->dt;
  objs.time += this->dt;

  double error = 0;
  if (this->usePosError) { error = (objs.pos - errorVect).absnew().max()*1.4; }
  else { error = (objs.vel - errorVect).absnew().max()*1.4; }
  this->dt = this->dt*std::pow(this->errorTol/error,0.5);
  // std::cout << "Time: " << objs.time <<" Error: " << error  << " Factor: " << std::pow(this->errorTol/error,0.5) << " dt " << this->dt << std::endl;
  return objs;
}

SpaceObjs Integrator::solveStepBogSham(SpaceObjs objs, ForceSolver &forceSolver) {
  SpaceVectors k1a = objs.vel;
  SpaceVectors k1b = forceSolver.solve(objs)/objs.mass;

  SpaceObjs objs2 = objs;
  objs2.pos += k1a * (this->dt/2.0);
  objs2.vel += k1b * (this->dt/2.0);

  SpaceVectors k2a = objs2.vel;
  SpaceVectors k2b = forceSolver.solve(objs2)/objs2.mass;

  objs2 = objs;
  objs2.pos += k2a * (3.0/4.0*this->dt);
  objs2.vel += k2b * (3.0/4.0*this->dt);

  SpaceVectors k3a = objs2.vel;
  SpaceVectors k3b = forceSolver.solve(objs2)/objs2.mass;

  SpaceVectors errorVect;
  if (this->usePosError) { errorVect = objs.pos + k3a*this->dt; }
  else { errorVect = objs.vel + k3b*this->dt; }

  objs2 = objs;
  objs2.pos += k1a*(2.0/9.0*this->dt) + k2a*(1.0/3.0*this->dt) + k3a*(4.0/9.0*this->dt);
  objs2.vel += k1b*(2.0/9.0*this->dt) + k2b*(1.0/3.0*this->dt) + k3b*(4.0/9.0*this->dt);

  SpaceVectors k4a = objs2.vel;
  SpaceVectors k4b = forceSolver.solve(objs2)/objs2.mass;

  objs.pos += k1a*(7.0/24.0*this->dt) + k2a*(1.0/4.0*this->dt) + k3a*(1.0/3.0*this->dt) + k4a*(1.0/8.0*this->dt);
  objs.vel += k1b*(7.0/24.0*this->dt) + k2b*(1.0/4.0*this->dt) + k3b*(1.0/3.0*this->dt) + k4b*(1.0/8.0*this->dt);
  objs.time += this->dt;

  double error = 0;
  if (this->usePosError) { error = (objs.pos - errorVect).absnew().max()*1.4; }
  else { error = (objs.vel - errorVect).absnew().max()*1.4; }
  this->dt = this->dt*std::pow(this->errorTol/error,0.25);
  // std::cout << "Time: " << objs.time <<" Error: " << error  << " Factor: " << std::pow(this->errorTol/error,0.25) << " dt " << this->dt << std::endl;
  return objs;
}

SpaceObjs Integrator::solveStepRKF45(SpaceObjs objs, ForceSolver &forceSolver) {
  SpaceVectors k1a = objs.vel;
  SpaceVectors k1b = forceSolver.solve(objs)/objs.mass;

  SpaceObjs objs2 = objs;
  objs2.pos += k1a*(this->dt*0.25);
  objs2.vel += k1b*(this->dt*0.25);
  SpaceVectors k2a = objs2.vel;
  SpaceVectors k2b = forceSolver.solve(objs2)/objs2.mass;

  objs2 = objs;
  objs2.pos += k1a*(3.0/32.0*this->dt) + k2a*(9.0/32.0*this->dt);
  objs2.vel += k1b*(3.0/32.0*this->dt) + k2b*(9.0/32.0*this->dt);
  SpaceVectors k3a = objs2.vel;
  SpaceVectors k3b = forceSolver.solve(objs2)/objs2.mass;

  objs2 = objs;
  objs2.pos += k1a*(1932.0/2197.0*this->dt) + k2a*(-7200.0/2197.0*this->dt) + k3a*(7296.0/2197.0*this->dt);
  objs2.vel += k1b*(1932.0/2197.0*this->dt) + k2b*(-7200.0/2197.0*this->dt) + k3b*(7296.0/2197.0*this->dt);
  SpaceVectors k4a = objs2.vel;
  SpaceVectors k4b = forceSolver.solve(objs2)/objs2.mass;

  objs2 = objs;
  objs2.pos += k1a*(439.0/216.0*this->dt) + k2a*(-8.0*this->dt) + k3a*(3680.0/513.0*this->dt) + k4a*(-845.0/4104.0*this->dt);
  objs2.vel += k1b*(439.0/216.0*this->dt) + k2b*(-8.0*this->dt) + k3b*(3680.0/513.0*this->dt) + k4b*(-845.0/4104.0*this->dt);
  SpaceVectors k5a = objs2.vel;
  SpaceVectors k5b = forceSolver.solve(objs2)/objs2.mass;

  objs2 = objs;
  objs2.pos += k1a*(-8.0/27.0*this->dt) + k2a*(2.0*this->dt) + k3a*(-3544.0/2565.0*this->dt) + k4a*(1859.0/4104.0*this->dt) +  k5a*(-11.0/40.0*this->dt);
  objs2.vel += k1b*(-8.0/27.0*this->dt) + k2b*(2.0*this->dt) + k3b*(-3544.0/2565.0*this->dt) + k4b*(1859.0/4104.0*this->dt) +  k5b*(-11.0/40.0*this->dt);
  SpaceVectors k6a = objs2.vel;
  SpaceVectors k6b = forceSolver.solve(objs2)/objs2.mass;

  SpaceVectors errorVect;
  if (this->usePosError) {
    errorVect = objs.pos + k1a*(25.0/216.0*this->dt) + k3a*(1408.0/2565.0*this->dt) + k4a*(2197.0/4104.0*this->dt) +  k5a*(-1.0/5.0*this->dt);
  } else {
    errorVect = objs.vel + k1b*(25.0/216.0*this->dt) + k3b*(1408.0/2565.0*this->dt) + k4b*(2197.0/4104.0*this->dt) +  k5b*(-1.0/5.0*this->dt);
  }


  objs.pos += k1a*(16.0/135.0 *this->dt) + k3a*(6656.0/12825.0*this->dt) + k4a*(28561.0/56430.0*this->dt) +  k5a*(-9.0/50.0*this->dt) +  k6a*(2.0/55.0*this->dt);
  objs.vel += k1b*(16.0/135.0 *this->dt) + k3b*(6656.0/12825.0*this->dt) + k4b*(28561.0/56430.0*this->dt) +  k5b*(-9.0/50.0*this->dt) +  k6b*(2.0/55.0*this->dt);
  objs.time += this->dt;

  double error = 0;
  if (this->usePosError) { error = (objs.pos - errorVect).absnew().max()*1.4; }
  else { error = (objs.vel - errorVect).absnew().max()*1.4; }
  this->dt = this->dt*std::pow(this->errorTol/error,0.2);
  // std::cout << "Time: " << objs.time <<" Error: " << error  << " Factor: " << std::pow(this->errorTol/error,0.2) << " dt " << this->dt << std::endl;
  return objs;
}

SpaceObjs Integrator::solveStepDormandPrince(SpaceObjs objs, ForceSolver &forceSolver) {
  SpaceVectors k1a = objs.vel;
  SpaceVectors k1b = forceSolver.solve(objs)/objs.mass;

  SpaceObjs objs2 = objs;
  objs2.pos += k1a*(this->dt*0.2);
  objs2.vel += k1b*(this->dt*0.2);
  SpaceVectors k2a = objs2.vel;
  SpaceVectors k2b = forceSolver.solve(objs2)/objs2.mass;

  objs2 = objs;
  objs2.pos += k1a*(3.0/40.0*this->dt) + k2a*(9.0/40.0*this->dt);
  objs2.vel += k1b*(3.0/40.0*this->dt) + k2b*(9.0/40.0*this->dt);
  SpaceVectors k3a = objs2.vel;
  SpaceVectors k3b = forceSolver.solve(objs2)/objs2.mass;

  objs2 = objs;
  objs2.pos += k1a*(44.0/45.0*this->dt) + k2a*(-56.0/15.0*this->dt) + k3a*(32.0/9.0*this->dt);
  objs2.vel += k1b*(44.0/45.0*this->dt) + k2b*(-56.0/15.0*this->dt) + k3b*(32.0/9.0*this->dt);
  SpaceVectors k4a = objs2.vel;
  SpaceVectors k4b = forceSolver.solve(objs2)/objs2.mass;

  objs2 = objs;
  objs2.pos += k1a*(19372.0/6561.0*this->dt) + k2a*(-25360.0/2187.0*this->dt) + k3a*(64448.0/6561.0*this->dt) + k4a*(-212.0/729.0*this->dt);
  objs2.vel += k1b*(19372.0/6561.0*this->dt) + k2b*(-25360.0/2187.0*this->dt) + k3b*(64448.0/6561.0*this->dt) + k4b*(-212.0/729.0*this->dt);
  SpaceVectors k5a = objs2.vel;
  SpaceVectors k5b = forceSolver.solve(objs2)/objs2.mass;

  objs2 = objs;
  objs2.pos += k1a*(9017.0/3168.0*this->dt) + k2a*(-355.0/33.0*this->dt) + k3a*(46732.0/5247.0*this->dt) + k4a*(49.0/176.0*this->dt) +  k5a*(-5103.0/18656.0*this->dt);
  objs2.vel += k1b*(9017.0/3168.0*this->dt) + k2b*(-355.0/33.0*this->dt) + k3b*(46732.0/5247.0*this->dt) + k4b*(49.0/176.0*this->dt) +  k5b*(-5103.0/18656.0*this->dt);
  SpaceVectors k6a = objs2.vel;
  SpaceVectors k6b = forceSolver.solve(objs2)/objs2.mass;

  objs2 = objs;
  objs2.pos += k1a*(35.0/384.0*this->dt) + k3a*(500.0/1113.0*this->dt) + k4a*(125.0/192.0*this->dt) + k5a*(-2187.0/6784.0*this->dt) + k6a*(11.0/84.0*this->dt);
  objs2.vel += k1b*(35.0/384.0*this->dt) + k3b*(500.0/1113.0*this->dt) + k4b*(125.0/192.0*this->dt) + k5b*(-2187.0/6784.0*this->dt) + k6b*(11.0/84.0*this->dt);
  SpaceVectors k7a = objs2.vel;
  SpaceVectors k7b = forceSolver.solve(objs2)/objs2.mass;

  SpaceVectors errorVect;
  if (this->usePosError) {
    errorVect = objs.pos + k1a*(5179.0/57600.0 *this->dt) + k3a*(7571.0/16695.0*this->dt) + k4a*(393.0/640.0*this->dt) +  k5a*(-92097.0/339200.0*this->dt) + k6a*(187.0/2100.0*this->dt) + k7a*(1.0/40.0*this->dt);
  } else {
    errorVect = objs.vel + k1b*(5179.0/57600.0 *this->dt) + k3b*(7571.0/16695.0*this->dt) + k4b*(393.0/640.0*this->dt) +  k5b*(-92097.0/339200.0*this->dt) + k6b*(187.0/2100.0*this->dt) + k7b*(1.0/40.0*this->dt);
  }
  objs.pos += k1a*(35.0/384.0*this->dt) + k3a*(500.0/1113.0*this->dt) + k4a*(125.0/192.0*this->dt) +  k5a*(-2187.0/6784.0*this->dt) + k6a*(11.0/84.0*this->dt);
  objs.vel += k1b*(35.0/384.0*this->dt) + k3b*(500.0/1113.0*this->dt) + k4b*(125.0/192.0*this->dt) +  k5b*(-2187.0/6784.0*this->dt) + k6b*(11.0/84.0*this->dt);
  objs.time += this->dt;

  double error = 0;
  if (this->usePosError) { error = (objs.pos - errorVect).absnew().max()*1.4; }
  else { error = (objs.vel - errorVect).absnew().max()*1.4; }
  this->dt = this->dt*std::pow(this->errorTol/error,0.2);
  // std::cout << "Time: " << objs.time <<" Error: " << error  << " Factor: " << std::pow(this->errorTol/error,0.2) << " dt " << this->dt << std::endl;
  return objs;
}

SpaceObjs Integrator::solveStepEulerSimp(SpaceObjs objs, ForceSolver &forceSolver) {
  SpaceVectors k1 = forceSolver.solve(objs)/objs.mass;
  objs.vel += k1 * this->dt;
  objs.pos += objs.vel * this->dt;
  objs.time += this->dt;
  return objs;
}

SpaceObjs Integrator::solve(SpaceObjs &objs,ForceSolver &forceSolver) {
  int saveMod = this->savePeriod/this->dt;
  int saves = 0;
  double initalMomentum = this->systemMomentum(objs);
  double initalKinetic = this->systemKinetic(objs);
  objs.save();
  while (objs.time < endTime) {
    switch (this->method) {
      case Euler      : objs = this->solveStepEuler(objs,forceSolver);        break;
      case Midpoint   : objs = this->solveStepMidpoint(objs,forceSolver);     break;
      case Huen       : objs = this->solveStepHuen(objs,forceSolver);         break;
      case Rals3rd    : objs = this->solveStepRalstons3rd(objs,forceSolver);  break;
      case Rk4        : objs = this->solveStepRK4(objs,forceSolver);          break;
      case Rals4th    : objs = this->solveStepRalstons4th(objs,forceSolver);  break;
      case EulerSimp  : objs = this->solveStepEulerSimp(objs,forceSolver);    break;
      case HuenEuler  : objs = this->solveStepHuenEuler(objs,forceSolver);    break;
      case BogSham    : objs = this->solveStepBogSham(objs,forceSolver);      break;
      case Rkf45      : objs = this->solveStepRKF45(objs,forceSolver);        break;
      case DormPrince : objs = this->solveStepDormandPrince(objs,forceSolver);break;
    }
    if ((saves+1) * this->savePeriod < objs.time) {
      objs.save();
      saves++;
      std::cout << saves << " " << objs.time  << " " << this->systemMomentum(objs) << " " << this->systemKinetic(objs) << std::endl;
    }
  }
  std::cout << "Momentum Error: Inital " << initalMomentum << " Final " << this->systemMomentum(objs) << " Change " << this->systemMomentum(objs)-initalMomentum << std::endl;
  std::cout << "Kinetic Error: Inital " << initalKinetic << " Final " << this->systemKinetic(objs) << " Change " << this->systemKinetic(objs)-initalKinetic << std::endl;
  return objs;
}

double Integrator::systemMomentum(SpaceObjs &objs) {
  double px = (objs.vel.x * objs.mass).sum();
  double py = (objs.vel.y * objs.mass).sum();
  double pz = (objs.vel.z * objs.mass).sum();
  return std::sqrt(px*px + py*py + pz*pz);
}

double Integrator::systemKinetic(SpaceObjs &objs) {
  double kx = (objs.vel.x * objs.vel.x * objs.mass * 0.5).sum();
  double ky = (objs.vel.y * objs.vel.y * objs.mass * 0.5).sum();
  double kz = (objs.vel.z * objs.vel.z * objs.mass * 0.5).sum();
  return std::sqrt(kx*kx + ky*ky + kz*kz);
}


#endif
