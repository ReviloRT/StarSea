#ifndef SIM_SOLVER_HPP
#define SIM_SOLVER_HPP

#include <iostream>
#include "SimParameters.hpp"

class BaseSolver : BaseProcess {
	private:
		double time;
		
	public:
		BaseSolver();
		void initalise(double *ptr);
		void updateParameter(int id, int value);
		void updateParameter(int id, double value);
		
		void solveStep();
		void writeState(double *arrPtr);
		void writeToString(std::ostream writeTarget);
		
		double time();
};

void addSolverParameters(ParameterManager &params);

#endif
