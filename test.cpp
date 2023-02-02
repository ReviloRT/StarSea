
#include <iostream>
#include <cassert>

#include "ArrayWrapper.cpp"
#include "SpaceObjs.cpp"

using namespace std;

void testArrayWrapper();
void testSpaceObjs();

int main() {

  testArrayWrapper();
  testSpaceObjs();

  cout << "Tests Completed, all successful" << endl;
}

void testArrayWrapper() {
    cout << "Testing ArrayWrapper" << endl;
    ArrayWrapper array1;
    assert(array1.length == 0);
    assert(array1.array == NULL);

    ArrayWrapper array2(2,1);
    assert(array2.length == 2);
    assert(array2.array[0] == 1);
    assert(array2.array[1] == 1);

    ArrayWrapper array3(4,5,20);
    assert(array3.length == 4);
    assert(array3.array[0] >= 5);
    assert(array3.array[0] < 20);
    assert(array3.array[3] >= 5);
    assert(array3.array[3] < 20);

    ArrayWrapper array4 = array2;
    assert(array4.length == 2);
    assert(array4.array[0] == 1);
    assert(array4.array[1] == 1);

    array2 = array3;
    assert(array2.length == 4);
    assert(array2.array[0] == array3.array[0]);
    assert(array2.array[3] == array3.array[3]);

    array2 = array1;
    assert(array2.length == 0);
    assert(array2.array == NULL);

    ArrayWrapper array5(0);
    assert(array5.length == 0);
    assert(array5.array == NULL);
}

void testSpaceObjs() {
  cout << "Testing SpaceObjs" << endl;

  SpaceObjs objs1(0,-5);
  assert(objs1.dims == 2);
  assert(objs1.numObjs == 0);
  assert(objs1.mass.length == 0);
  assert(objs1.posx.length == 0);
  assert(objs1.velz.length == 0);

  SpaceObjs objs2(3,20);
  assert(objs2.dims == 3);
  assert(objs2.numObjs == 20);
  assert(objs2.mass.length == 20);
  assert(objs2.posx.length == 20);
  assert(objs2.velz.length == 20);

  SpaceObjs objs3(2,20);
  assert(objs3.dims == 2);
  assert(objs3.numObjs == 20);
  assert(objs3.mass.length == 20);
  assert(objs3.posx.length == 20);
  assert(objs3.velz.length == 0);

  SpaceObjs objs4(9,-123);
  assert(objs4.dims == 2);
  assert(objs4.numObjs == 0);
  assert(objs4.mass.length == 0);
  assert(objs4.posx.length == 0);
  assert(objs4.velz.length == 0);


}
