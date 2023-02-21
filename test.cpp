
#include <iostream>
#include <cassert>

#define DIMVECT vector2

#include "vectors.cpp"
#include "SpaceObj.cpp"

using namespace std;

void testVectors();
void testSpaceObj();

int main() {

  testVectors();
  testSpaceObj();

  cout << "Tests Completed, all successful" << endl;
}

// TODO: write flag constructor and 2d test cases

void testVectors() {
  cout << "Testing Vectors" << endl;
  // Test constructors
  {
    vector3 vect = vector3();
    assert(vect.x == 0);
    assert(vect.y == 0);
    assert(vect.z == 0);

    vector3 vect2 = vector3(-20);
    assert(vect2.x == -20);
    assert(vect2.y == -20);
    assert(vect2.z == -20);

    vector3 vect3 = vector3(-20,12,15);
    assert(vect3.x == -20);
    assert(vect3.y == 12);
    assert(vect3.z == 15);

    vector3 vect4 = vector3(vect3);
    assert(vect4.x == -20);
    assert(vect4.y == 12);
    assert(vect4.z == 15);

    // Test operator=
    vector3 vect5 = vect3;
    assert(vect5.x == -20);
    assert(vect5.y == 12);
    assert(vect5.z == 15);

    // Test rand Constructor
    vector3 vect6 = vector3("rand",5,12);
    assert(vect6.x >= 5);
    assert(vect6.x < 12);
    assert(vect6.y >= 5);
    assert(vect6.y < 12);
    assert(vect6.z >= 5);
    assert(vect6.z < 12);
  }

  // Test set functions
  {
    vector3 vect;
    vect.zero();
    assert(vect.x == 0);
    assert(vect.y == 0);
    assert(vect.z == 0);

    vect.fill(5);
    assert(vect.x == 5);
    assert(vect.y == 5);
    assert(vect.z == 5);

    vect.set(2,6,5);
    assert(vect.x == 2);
    assert(vect.y == 6);
    assert(vect.z == 5);

    vect.rand(5,20);
    assert(vect.x >= 5);
    assert(vect.x < 20);
    assert(vect.y >= 5);
    assert(vect.y < 20);
    assert(vect.z >= 5);
    assert(vect.z < 20);
  }

  // Test basic operators
  {
    vector3 vect1(5,2,3);
    vector3 vect2(1,2,6);

    assert(vect1 == vector3(5,2,3));
    assert(!(vect1 == vect2));
    assert(!(vect1 != vector3(5,2,3)));
    assert(vect1 != vect2);

    vector3 vect3 = vect1 + vect2;
    assert(vect3.x == 6);
    assert(vect3.y == 4);
    assert(vect3.z == 9);

    vect3 = vect1 - vect2;
    assert(vect3.x == 4);
    assert(vect3.y == 0);
    assert(vect3.z == -3);

    vect2 = vect1 * vect3;
    assert(vect2.x == 20);
    assert(vect2.y == 0);
    assert(vect2.z == -9);

    vect3 = vect2 / vect1;
    assert(vect3.x == 4);
    assert(vect3.y == 0);
    assert(vect3.z == -3);

    vect2 = vect1 + 1;
    assert(vect2.x == 6);
    assert(vect2.y == 3);
    assert(vect2.z == 4);

    vect2 = vect1 - 1;
    assert(vect2.x == 4);
    assert(vect2.y == 1);
    assert(vect2.z == 2);

    vect2 = vect1 * 2;
    assert(vect2.x == 10);
    assert(vect2.y == 4);
    assert(vect2.z == 6);

    vect2 = vect1 / 2;
    assert(vect2.x == 2.5);
    assert(vect2.y == 1);
    assert(vect2.z == 1.5);
  }

  // Test self operators
  {
    vector3 vect1(2,6,4);
    vector3 vect2(1,2,-2);

    vect1 += vect2;
    assert(vect1.x == 3);
    assert(vect1.y == 8);
    assert(vect1.z == 2);

    vect1 -= vect2;
    assert(vect1.x == 2);
    assert(vect1.y == 6);
    assert(vect1.z == 4);

    vect1 *= vect2;
    assert(vect1.x == 2);
    assert(vect1.y == 12);
    assert(vect1.z == -8);

    vect1 /= vect2;
    assert(vect1.x == 2);
    assert(vect1.y == 6);
    assert(vect1.z == 4);

    vect1 += 1;
    assert(vect1.x == 3);
    assert(vect1.y == 7);
    assert(vect1.z == 5);

    vect1 -= 2;
    assert(vect1.x == 1);
    assert(vect1.y == 5);
    assert(vect1.z == 3);

    vect1 *= 10;
    assert(vect1.x == 10);
    assert(vect1.y == 50);
    assert(vect1.z == 30);

    vect1 /= 5;
    assert(vect1.x == 2);
    assert(vect1.y == 10);
    assert(vect1.z == 6);
  }

  // Test special Functions
  {
    vector3 vect1(3,4,8);
    assert(vect1.mag() >= 9.43398);
    assert(vect1.mag() <= 9.43399);
    assert(vect1.sqmag() == 89);
    assert(vect1.max() == 8);
    assert(vect1.min() == 3);
    assert(vect1.dot(vector3(5,2,1)) == 31);
    vector3 vect2(-12,37,-14);
    vector3 vect3  = vect1.cross(vector3(5,2,1));
    assert(vect3 == vect2);
    assert(vect1.string() == "x3.000000y4.000000z8.000000");
  }
}

void testSpaceObj() {
  cout << "Testing SpaceObj" << endl;
  // Testing Constructors
  {
    SpaceObj obj1;
    assert(obj1.mass == 1);
    assert(obj1.pos == DIMVECT());
    assert(obj1.vel == DIMVECT());

    SpaceObj obj2(5,DIMVECT(4),DIMVECT(1));
    assert(obj2.mass == 5);
    assert(obj2.pos == DIMVECT(4));
    assert(obj2.vel == DIMVECT(1));

    SpaceObj obj3 = obj2;
    assert(obj3.mass == 5);
    assert(obj3.pos == DIMVECT(4));
    assert(obj3.vel == DIMVECT(1));

    obj1 = obj3;
    assert(obj1.mass == 5);
    assert(obj1.pos == DIMVECT(4));
    assert(obj1.vel == DIMVECT(1));
  }
  // Testing Other functions
  {
    SpaceObj obj1;
    SpaceObj obj2;
    assert(obj1 != obj2);
    assert(!(obj1 == obj2));
    assert(obj1 == obj1);
    assert(!(obj1 != obj1));
  }
}
