
#define STARSEA_VERSION 1.0

#define SAVEFILE "stars.txt"


#include <iostream>
#include <fstream>


#include "SpaceObjs.cpp"


int main() {
  std::cout << "StarSea v" << STARSEA_VERSION << std::endl;

  std::srand(0);
  int dims = 3;
  int numObjs = 2;

  SpaceObjs objs(dims,numObjs);

  objs.print();

}
