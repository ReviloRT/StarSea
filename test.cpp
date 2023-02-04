
#include <iostream>
#include <cassert>

#include "ArrayWrapper.cpp"
#include "SpaceVectors.cpp"
#include "SpaceObjs.cpp"
#include "ForceSolver.cpp"
#include "Integrator.cpp"

using namespace std;

void testArrayWrapper();
void testSpaceVectors();
void testSpaceObjs();
void testForceSolver();
void testIntegrator();

int main() {

  testArrayWrapper();
  testSpaceVectors();
  testSpaceObjs();
  testForceSolver();
  testIntegrator();

  cout << "Tests Completed, all successful" << endl;
}

// TODO: write test conditions for operator +, -, *, /
// TODO: write test for sum, max, min, abs
void testArrayWrapper() {
  cout << "Testing ArrayWrapper" << endl;
  // Test Constructors
  {
    ArrayWrapper array1;
    assert(array1.len() == 0);
    assert(array1.array == NULL);

    ArrayWrapper array2(2,1);
    assert(array2.len() == 2);
    assert(array2.array[0] == 1);
    assert(array2.array[1] == 1);

    ArrayWrapper array3(4,5,20);
    assert(array3.len() == 4);
    assert(array3.array[0] >= 5);
    assert(array3.array[0] < 20);
    assert(array3.array[3] >= 5);
    assert(array3.array[3] < 20);

    ArrayWrapper array4 = array2;
    assert(array4.len() == 2);
    assert(array4.array[0] == 1);
    assert(array4.array[1] == 1);

    array2 = array3;
    assert(array2.len() == 4);
    assert(array2.array[0] == array3.array[0]);
    assert(array2.array[3] == array3.array[3]);

    array2 = array1;
    assert(array2.len() == 0);
    assert(array2.array == NULL);

    ArrayWrapper array5(0);
    assert(array5.len() == 0);
    assert(array5.array == NULL);

    array3.rand(-2,-1);
    assert(array3.len() == 4);
    assert(array3.array[0] >= -2);
    assert(array3.array[0] < -1);
    assert(array3.array[3] >= -2);
    assert(array3.array[3] < -1);
  }
  // Test Operands
  {
    ArrayWrapper array1;
    array1 += array1;
    array1 -= array1;
    array1 *= array1;
    array1 /= array1;
    assert(array1.array == NULL);
    assert(array1.len() == 0);

    ArrayWrapper array2(10);
    array2 += array1;
    array2 -= array1;
    array2 *= array1;
    array2 /= array1;
    assert(array2.array[4] == 0);
    assert(array2.len() == 10);

    array1 = ArrayWrapper(10,4);
    array2 += array1;
    assert(array2.array[2] == 4);
    array2 /= array1;
    assert(array2.array[9] == 1);
    array2 -= array1;
    assert(array2.array[0] == -3);
    array2 *= array1;
    assert(array2.array[5] == -12);

    array2 += 1;
    assert(array2.array[7] == -11);
    array2 -= -20;
    assert(array2.array[4] == 9);
    array2 *= 2;
    assert(array2.array[2] == 18);
    array2 /= 6;
    assert(array2.array[8] == 3);
  }
}

// TODO: write test conditions for operator +, -, *, /
// TODO: write test for rand, max, min, abs
void testSpaceVectors() {
  cout << "Testing SpaceVectors" << endl;
  // Test Constructors
  {
    SpaceVectors vect1;
    assert(vect1.getDims() == 2);
    assert(vect1.len() == 0);
    assert(vect1.x.array == NULL);
    assert(vect1.z.array == NULL);
    assert(vect1.y.len() == 0);

    SpaceVectors vect2(3,2);
    assert(vect2.getDims() == 3);
    assert(vect2.len() == 2);
    assert(vect2.x.array[1] == 0);
    assert(vect2.z.array[0] == 0);
    assert(vect2.y.len() == 2);
    assert(vect2.y.array[0] == 0);

    SpaceVectors vect3(2,4,234);
    assert(vect3.getDims() == 2);
    assert(vect3.len() == 4);
    assert(vect3.y.array[3] == 234);
    assert(vect3.z.array == NULL);
    assert(vect3.x.len() == 4);

    SpaceVectors vect4(-3,1,45,46);
    assert(vect4.getDims() == 2);
    assert(vect4.len() == 1);
    assert(vect4.x.array[0] >= 45);
    assert(vect4.x.array[0] < 46);
    assert(vect4.z.array == NULL);
    assert(vect4.y.len() == 1);
    assert(vect4.y.array[0] >= 45);
    assert(vect4.y.array[0] < 46);

    SpaceVectors vect5 = vect4;
    assert(vect5.getDims() == 2);
    assert(vect5.len() == 1);
    assert(vect5.x.array[0] == vect4.x.array[0]);
    assert(vect5.z.array == NULL);
    assert(vect5.y.len() == 1);
    assert(vect5.y.array[0] == vect4.y.array[0]);

    vect2 = vect3;
    assert(vect2.getDims() == 2);
    assert(vect2.len() == 4);
    assert(vect2.y.array[3] == 234);
    assert(vect2.z.array == NULL);
    assert(vect2.x.len() == 4);
  }
  // Test Operands
  {
    SpaceVectors vect1;
    vect1 += vect1;
    vect1 -= vect1;
    vect1 *= vect1;
    vect1 /= vect1;
    vect1 += 1;
    vect1 -= 1;
    vect1 *= 1;
    vect1 /= 1;
    assert(vect1.len() == 0);
    assert(vect1.getDims() == 2);

    SpaceVectors vect2(2,5,1);
    vect2 += vect1;
    vect2 -= vect1;
    vect2 *= vect1;
    vect2 /= vect1;
    assert(vect2.len() == 5);
    assert(vect2.getDims() == 2);
    assert(vect2.x.array[0] == 1);

    SpaceVectors vect3(3,5,1);
    vect2 += vect3;
    vect2 -= vect3;
    vect2 *= vect3;
    vect2 /= vect3;
    assert(vect2.len() == 5);
    assert(vect2.getDims() == 2);
    assert(vect2.x.array[0] == 1);

    SpaceVectors vect4(3,5,2);
    vect4 += vect3;
    assert(vect4.len() == 5);
    assert(vect4.getDims() == 3);
    assert(vect4.x.array[0] == 3);
    assert(vect4.y.array[0] == 3);
    assert(vect4.z.array[0] == 3);
    vect4 -= vect3;
    assert(vect4.len() == 5);
    assert(vect4.getDims() == 3);
    assert(vect4.x.array[0] == 2);
    assert(vect4.y.array[0] == 2);
    assert(vect4.z.array[0] == 2);
    vect4 *= vect4;
    assert(vect4.len() == 5);
    assert(vect4.getDims() == 3);
    assert(vect4.x.array[0] == 4);
    assert(vect4.y.array[0] == 4);
    assert(vect4.z.array[0] == 4);
    vect4 /= vect4;
    assert(vect4.len() == 5);
    assert(vect4.getDims() == 3);
    assert(vect4.x.array[0] == 1);
    assert(vect4.y.array[0] == 1);
    assert(vect4.z.array[0] == 1);

    vect4 += 4;
    assert(vect4.x.array[0] == 5);
    assert(vect4.y.array[0] == 5);
    assert(vect4.z.array[0] == 5);
    vect4 -= 4;
    assert(vect4.x.array[0] == 1);
    assert(vect4.y.array[0] == 1);
    assert(vect4.z.array[0] == 1);
    vect4 *= 4;
    assert(vect4.x.array[0] == 4);
    assert(vect4.y.array[0] == 4);
    assert(vect4.z.array[0] == 4);
    vect4 /= 4;
    assert(vect4.x.array[0] == 1);
    assert(vect4.y.array[0] == 1);
    assert(vect4.z.array[0] == 1);

  }

}

// TODO: write test for oper=
void testSpaceObjs() {
  cout << "Testing SpaceObjs" << endl;

  SpaceObjs objs1(0,-5);
  assert(objs1.pos.getDims() == 2);
  assert(objs1.len() == 0);
  assert(objs1.mass.len() == 0);
  assert(objs1.pos.len() == 0);
  assert(objs1.vel.len() == 0);

  SpaceObjs objs2(3,20);
  assert(objs2.vel.getDims() == 3);
  assert(objs2.len() == 20);
  assert(objs2.mass.len() == 20);
  assert(objs2.pos.len() == 20);
  assert(objs2.vel.len() == 20);

  SpaceObjs objs3(2,20);
  assert(objs3.pos.getDims() == 2);
  assert(objs3.len() == 20);
  assert(objs3.mass.len() == 20);
  assert(objs3.pos.len() == 20);
  assert(objs3.vel.len() == 20);

  SpaceObjs objs4(9,-123);
  assert(objs4.vel.getDims() == 2);
  assert(objs4.len() == 0);
  assert(objs4.mass.len() == 0);
  assert(objs4.pos.len() == 0);
  assert(objs4.vel.len() == 0);


}

void testForceSolver() {
  cout << "Testing ForceSolver" << endl;

  ForceSolver solver;
  solver.bigG = 1;
  SpaceObjs obj1(2,0);

  SpaceVectors forces = solver.solveForcesDirect(obj1);
  assert(forces.len() == 0);
  assert(forces.getDims() == 2);
  assert(forces.x.array == NULL);

  SpaceObjs obj2(3,1);
  forces = solver.solveForcesDirect(obj2);
  assert(forces.len() == 1);
  assert(forces.getDims() == 3);
  forces.x.array[0] = 0;
  forces.y.array[0] = 0;
  forces.z.array[0] = 0;

  SpaceObjs obj3(2,2);
  obj3.pos.x.array[0] = -0.5;
  obj3.pos.x.array[1] = 0.5;
  forces = solver.solveForcesDirect(obj3);
  assert(forces.len() == 2);
  assert(forces.getDims() == 2);
  assert(forces.x.array[0] == 1);
  assert(forces.y.array[0] == 0);
  assert(forces.x.array[1] == -1);
  assert(forces.y.array[1] == 0);


  SpaceObjs obj4(2,2);
  obj4.pos.x.array[0] = 1;
  obj4.pos.y.array[0] = 1;
  obj4.pos.x.array[1] = -1;
  obj4.pos.y.array[1] = -1;
  forces = solver.solveForcesDirect(obj4);
  assert(forces.len() == 2);
  assert(forces.getDims() == 2);
  assert(forces.x.array[0] > -1/8.0/std::sqrt(2)-0.0000000000001);
  assert(forces.x.array[0] < -1/8.0/std::sqrt(2)+0.0000000000001);
  assert(forces.y.array[0] > -1/8.0/std::sqrt(2)-0.0000000000001);
  assert(forces.y.array[0] < -1/8.0/std::sqrt(2)+0.0000000000001);
  assert(forces.x.array[1] > 1/8.0/std::sqrt(2)-0.0000000000001);
  assert(forces.x.array[1] < 1/8.0/std::sqrt(2)+0.0000000000001);
  assert(forces.y.array[1] > 1/8.0/std::sqrt(2)-0.0000000000001);
  assert(forces.y.array[1] < 1/8.0/std::sqrt(2)+0.0000000000001);

}

// TODO: Write test conditions for integrator
void testIntegrator() {
  cout << "Testing Integrator" << endl;
}
