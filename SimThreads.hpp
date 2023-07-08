#ifndef SIM_THREADS_HPP
#define SIM_THREADS_HPP

enum MessageTypes {STATUS, PARAMETERINT, PARAMETERDOUBLE, PARAMETERPTR, UPDATE}
enum StatusTypes {ACTIVE, IDLE, RESET, TERMINATED}

struct ThreadMessage {
	int type;
	int id;
	int valueInt;
	double valueDouble;
	double *ptr;
};

class childThreadInterface {
private:
	pipe pipeIn;
	pipe pipeOut;
	StatusTypes status;
public:
	childThreadInterface(pipe pIn, pipe pOut);
	int awaitingIn();
	int awaitingOut();
	void sendMessage(ThreadMessage message);
	ThreadMessage getMessage();
	void handleMessages(BaseProcess &process);
	StatusTypes getStatus();
};

class parentThreadInterface {
private:
	pipe pipeIn;
	pipe pipeOut;
public:
	parentThreadInterface((void) *(threadFunction)(pipe pIn, pipe pOut));
	void joinChild();
	void terminateChild();
	int awaitingIn();
	int awaitingOut();
	void sendMessage(ThreadMessage message);
	void sendMessage(int type, int id, int valueInt, double valueDouble, double *ptr);
	ThreadMessage getMessage();
};

class BaseProcess {
	private:
		bool initalised; 
	public:
		BaseProcess();
		void virtual initalise(double *ptr);
		void virtual updateParameter(int id, int value);
		void virtual updateParameter(int id, double value);
		
		bool isInitalised();
};


#endif