#ifndef STANDARD_SOLVING
#define STANDARD_SOLVING

#include "vectors.cpp"
#include "SpaceObj.cpp"
#include "SpaceTime.cpp"

namespace SSolve {

struct kval {
  vect::vector3 *ka;
  vect::vector3 *kb;
};

struct SystemParameters {
	double dt;
	double endTime;
	double savePeriod;
	double bigG;
	int displayDims;
	vector3* (*forceFunc)(SystemParameters &, SpaceObj *, int);
	void (*stepFunc)(SystemParameters &, SpaceTime &);
	// For other solvers
	double sigma;
  const double *butcherTab;
  int butcherSize;
  double errorTollerance;
};



vect::vector3 calcForce(SpaceObj &obj1, SpaceObj &obj2, double bigG) {
   // Calculate forces
    vect::vector3 dif = (obj2.pos-obj1.pos);
    double dist2 = dif.sqmag();
    if (dist2 == 0) {dif.zero(); return dif;}
    dif *= bigG * obj1.mass * obj2.mass / (dist2 * std::sqrt(dist2));
    return dif;
}

vect::vector3* solveForcesDirect(SystemParameters &params, SpaceObj *objList, int objCount) {
  vect::vector3 *forces = new vector3[objCount];
  for (size_t ind1 = 0; ind1 < objCount; ind1++) {
    for (size_t ind2 = ind1+1; ind2 < objCount; ind2++) {
      vect::vector3 calc = calcForce(objList[ind1],objList[ind2], params.bigG);
      forces[ind1] = calc / objList[ind1].mass;
      forces[ind2] = calc * ( -1 / objList[ind2].mass );
    }
  }
  return forces;
}

vect::vector3* transposeVel(SpaceObj *objList, int objCount) {
  vect::vector3 *velVect = new vect::vector3[objCount];
  for (size_t ind1 = 0; ind1 < objCount; ind1++) {
    velVect[ind1] = objList[ind1].vel;
  }
  return velVect;
}

double systemMomentum(SpaceTime &spt) {
  vect::vector3 totalMomentum;
  for (size_t ind1 = 0; ind1 < spt.objCount; ind1++) {
    totalMomentum += spt.state[ind1].vel * spt.state[ind1].mass;
  }
  return totalMomentum.mag();
}

void solveEulerStep(SystemParameters &params, SpaceTime &spt) {
  kval k1 = {transposeVel(spt.state,spt.objCount), params.forceFunc(params, spt.state,spt.objCount)};
  
  for (size_t ind1 = 0; ind1 < spt.objCount; ind1++) {
    spt.state[ind1].pos += k1.ka[ind1] * params.dt;
    spt.state[ind1].vel += k1.kb[ind1] * params.dt;
  }
  spt.time += params.dt;
  
  delete[] k1.ka;
  delete[] k1.kb;
}

double solveSystem(SystemParameters &params, SpaceTime &spt) {
  double saves = 0;
  int stepCount = 0;
  
  double initalMomentum = systemMomentum(spt);
  
  while (spt.time < params.endTime) {
    
    params.stepFunc(params, spt);
    
    std::cout.setf(std::ios::left);
    std::cout << "t " << std::setprecision(4) << std::setw(5) << spt.time;
    std::cout << " dt " << std::setprecision(4) << std::setw(5) << params.dt;
    std::cout << " p " << std::setprecision(20) << std::setw(20) << systemMomentum(spt);
    std::cout << " c " << std::defaultfloat << spt.objCount;
    std::cout << " s " << stepCount;
    std::cout <<  "                                ";
    
    if ((saves+1)*params.savePeriod <= spt.time) {
      std::cout << '\n';
      spt.save();
      saves ++;
      stepCount = 0;
    } else {
      std::cout << '\r';
	    std::cout.flush();
    }
    
    stepCount ++;
  }
  return systemMomentum(spt) - initalMomentum;
}


}


#endif