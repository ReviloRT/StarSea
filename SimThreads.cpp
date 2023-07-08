
#include "SimThreads.hpp"

childThreadInterface(pipe pIn, pipe pOut);
int awaitingIn();
int awaitingOut();
void sendMessage(ThreadMessage message);
ThreadMessage getMessage();
void handleMessages(BaseProcess &process);
StatusTypes getStatus();

void childThreadInterface::handleMessages(BaseProcess &process) {
	int inCnt = this->awaitingIn();
	for (int i = 0; i < inCnt; i++) {
		ThreadMessage tmes = this->getMessage();
		switch (tmes.type) {
			case MessageTypes::STATUS:
				switch (tmes.id) {
					case StatusTypes::ACTIVE:
						if (!process.isInitalised()) break;
					case StatusTypes::RESET:
						process.initalise(tmes.ptr); 
						this->status = StatusTypes::IDLE;
						break;
					default:
						this->status = (StatusTypes)tmes.id;
				}
				break;
			case MessageTypes::PARAMETERINT:
				process.updateParameter(tmes.id,tmes.valueInt);
				break;
			case MessageTypes::PARAMETERDOUBLE:
				process.updateParameter(tmes.id,tmes.valueDouble);
				break;
			default:
				break;
		}
	}
}

parentThreadInterface((void) *(threadFunction)(pipe pIn, pipe pOut)) {
    
}
void joinChild() {
    
}
void terminateChild() {
    
}
int awaitingIn() {
    
}
int awaitingOut() {
    
}
void sendMessage(ThreadMessage message) {
    
}
void sendMessage(int type, int id, int valueInt, double valueDouble, double *ptr) {
    
}
ThreadMessage getMessage() {
    
}


BaseProcess() {
    
}
bool isInitalised() {
    
}