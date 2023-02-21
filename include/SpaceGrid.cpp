#ifndef SPACE_GRID
#define SPACE_GRID
// vector3* solveForcesGrid(SpaceObj *objList, int objCount) {
//   vector3 *forces = new vector3[objCount];
//   vector3 boundHigh = vector3(1,1,1);
//   vector3 boundLow = vector3(1,1,1);
//   vector3 size = boundHigh-boundLow;
//   const int gridDiv = 4;
//   int grid[gridDiv][gridDiv][gridDiv][objCount];
//   int gridCount[gridDiv][gridDiv][gridDiv] = {0};
//   int outOfBounds[objCount];
//   int outOfBoundsCount = 0;
//   for (size_t ind1 = 0; ind1 < objCount; ind1++) {
//     SpaceObj &obj = objList[ind1];
//     if ((obj.pos.greaterThan(boundHigh)) || (obj.pos.lessThan(boundLow))) {
//       outOfBounds[outOfBoundsCount] = ind1;
//       outOfBoundsCount++;
//     } else {
//       vector3 coords = obj.pos*size/gridDiv;
//       int ix = (int)coords.x;
//       int iy = (int)coords.y;
//       int iz = (int)coords.z;
//       int count = gridCount[ix][iy][iz];
//       grid[ix][iy][iz][count] = ind1;
//       gridCount[ix][iy][iz] ++;
//     }
//   }
  
//   for (size_t ind1 = 0; ind1 < objCount; ind1++) {
//     for (size_t ind2 = ind1; ind2 < objCount; ind2++) {
//       vect::vector3 calc = calcForce(objList[ind1],objList[ind2]);
//       forces[ind1] = calc / objList[ind1].mass;
//       forces[ind2] = calc * ( -1 / objList[ind2].mass );
//     }
//   }
//   return forces;
// }

#endif