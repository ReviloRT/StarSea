
#include "SimParameters.hpp"
#include "SimThreads.hpp"
#include "SimSolver.hpp"

void solverThreadFunction(pipe pIn, pipe pOut) {
	childThreadInterface threadI(pIn, pOut);
	BaseSolver solver();
	
	bool *outWriteLock = null;
	double *outWriteArray = null;

	// Superloop
	while (true) {
		// Handle incoming messages
		threadI.handleMessages(solver);
		
		// Advance Solver
		if (status == StatusTypes::Active) {
			if (outWriteLock == null) continue;
			if (outWriteArray == null) continue;
			solver.solveStep();
			*outWriteLock.lock();
			solver.writeState(outWriteArray);
			*outWriteLock.unlock();
			threadI.sendMessage(MessageType::UPDATE, threadI.status(), 0, solver.time(), 0);
		}
	}
	
}

int main() {
	ParameterManager params();
	params.addIntParameter("Dimentions",2,2,3);
	params.addIntParameter("Object Count",1,1,1000);
	addSolverParameters(params);
	

	double solverOut = new double[ params.getIntParam("Dimentions")*params.getIntParam("Object Count")];
	parentThreadInterface solverI(&solverThreadFunction);
	solverI.sendMessage(MessageTypes:STATUS, StatusTypes:RESET, 0, 0, &solverOut);

return 0;
}
