#ifndef FORCE_SOLVER
#define FORCE_SOLVER

#include "SpaceObjs.cpp"
#include <cmath>

class ForceSolver {
public:
  double bigG;

  ForceSolver();
  SpaceVectors solveForcesDirect(SpaceObjs &);
  void solveForcesDirect2D(SpaceVectors&, SpaceObjs &);
  void solveForcesDirect3D(SpaceVectors&, SpaceObjs &);

};

ForceSolver::ForceSolver() {
  this->bigG = 1;
}

void ForceSolver::solveForcesDirect2D(SpaceVectors& forces, SpaceObjs &objs) {
  for (size_t ind1 = 0; ind1 < objs.len(); ind1++) {
    for (size_t ind2 = 0; ind2 < objs.len(); ind2++) {
      if (ind1 == ind2) { continue;}
      double dx = (objs.pos.x.array[ind2] - objs.pos.x.array[ind1]);
      double dy = (objs.pos.y.array[ind2] - objs.pos.y.array[ind1]);
      double dm2 = dx*dx + dy*dy;
      double dm = std::sqrt(dm2);
      double fMag = this->bigG * objs.mass.array[ind1] * objs.mass.array[ind2] / (dm2);
      forces.x.array[ind1] += fMag * dx/(dm);
      forces.y.array[ind1] += fMag * dy/(dm);
    }
  }
}

void ForceSolver::solveForcesDirect3D(SpaceVectors& forces, SpaceObjs &objs) {
  for (size_t ind1 = 0; ind1 < objs.len(); ind1++) {
    for (size_t ind2 = 0; ind2 < objs.len(); ind2++) {
      if (ind1 == ind2) { continue;}
      double dx = (objs.pos.x.array[ind2] - objs.pos.x.array[ind1]);
      double dy = (objs.pos.y.array[ind2] - objs.pos.y.array[ind1]);
      double dz = (objs.pos.z.array[ind2] - objs.pos.z.array[ind1]);
      double dm2 = dx*dx + dy*dy;
      double dm = std::sqrt(dm2);
      double fMag = this->bigG * objs.mass.array[ind1] * objs.mass.array[ind2] / (dm2);
      forces.x.array[ind1] += fMag * dx/(dm);
      forces.y.array[ind1] += fMag * dy/(dm);
      forces.z.array[ind1] += fMag * dz/(dm);
    }
  }
}

SpaceVectors ForceSolver::solveForcesDirect(SpaceObjs &objs) {
  bool is3D = (objs.pos.getDims() == 3);
  SpaceVectors forces(2+is3D,objs.len(),0);
  if (is3D) {this->solveForcesDirect3D(forces,objs);}
  else {this->solveForcesDirect2D(forces,objs);}
  return forces;
}


#endif
