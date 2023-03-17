

#define SAVEFILE "stars.txt"

// 2 body test orbital period 24.1839915231

const bool merges = false;
const bool test2Bodies = true;

const int displayDims = 2;
const int maxObjCount = 100;
const double startSpace = 0.25;
const double startSpeed = 0.2;

const double endTime = 30;
const double savePeriod = 1;

const double bigG = -0.01;
const double errorTollerance = 0.0000001;
const double treeSigma = 0.1;
const double softeningConst = 10000000;
const double minMergeDist = 0.00001;

int objCount = 100;
double dt = 0.1;


#include "solverFunctions.cpp"


int main() {

  std::srand(0);

  clearFile();

  initRandomObjs();

  if (test2Bodies) {
    init2BodyTestObjs();
  }

  saveStep();

  double initalMomentum = solveSystemMomentum();

  solveSystem();

  std::cout << "Inital Momentum: " << initalMomentum << "   Final Momentum: " << solveSystemMomentum();

}
