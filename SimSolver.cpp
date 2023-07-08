
#include "SimSolver.hpp"

void BaseSolver::addParameters(ParameterManager &params){
    params.addDoubleParameter("Grav Const",1,-100,100);
    params.addDoubleParameter("dt",1,0,10);
}