#ifndef SPACETIME
#define SPACETIME


#define SAVEFILE "stars.txt"

#include <iostream>
#include <fstream>

#include "vectors.cpp"
#include "SpaceObj.cpp"


class SpaceTime {
public:
	double time;
	int objCount;
	SpaceObj *state;
	
	
	SpaceTime();
	SpaceTime(SpaceObj *, int);
	~SpaceTime();
	
	void print();
	void save();
	void clearFile(int);
};

SpaceTime::SpaceTime() : time(0), objCount(0), state(NULL) {}
SpaceTime::SpaceTime(SpaceObj *state, int objCount) : time(0), objCount(objCount), state(state) {}

SpaceTime::~SpaceTime() {
	delete[] state;
}

void SpaceTime::print() {
  std::cout << "SpaceTime: t" << this->time << " c" << this->objCount << '\n';
  for (size_t i = 0; i < this->objCount; i++) {
	std::cout << "	" <<this->state[i].string() << '\n';
  }
}

void SpaceTime::save() {
  std::fstream file;
  file.open(SAVEFILE,std::ios::app);
  file << "t" << this->time << "c" << this->objCount;
  for (size_t i = 0; i < this->objCount; i++) {
	file << this->state[i].string();
  }
  file << std::endl;
  file.close();
}

void SpaceTime::clearFile(int dim) {
  std::fstream file;
  file.open(SAVEFILE,std::ios::out | std::ios::trunc);
  file << dim;
  file.close();
}




#endif