#include "../../include/geom/Vector.hpp"

int main(){

  geom::Vector *v1, *v2, *result;
  geom::Point p1, p2, p3;

  // create a new vector at origin (0,0) with angle PI/4 rad, and magnitude 5 
  v1 = new geom::Vector(0, 0, 3, 3, 5);


  // test angle
  assert(fabs(v1->angle() - M_PI/4) < 0.0001);

  // test endpoint
  v1->endpoint(&p1);
  assert(fabs(p1.x - sqrt(12.5)) < 0.0001);
  assert(fabs(p1.y - sqrt(12.5)) < 0.0001);

  // test magnitude
  assert(fabs(v1->magnitude() - 5) < 0.0001);

  // test rotate
  v1->rotate(M_PI/4);
  assert((v1->angle() - M_PI/2) < 0.0001);
  v1->endpoint(&p1);
  assert(fabs(p1.x) < 0.0001);
  assert(fabs(p1.y - 5) < 0.0001);
  assert(fabs(v1->magnitude() - 5) < 0.0001);

  // test scale
  v1->scale(2);
  assert((v1->angle() - M_PI/2) < 0.0001);
  v1->endpoint(&p1);
  assert(fabs(p1.x) < 0.0001);
  assert(fabs(p1.y - 10) < 0.0001);
  assert(fabs(v1->magnitude() - 10) < 0.0001);

  // test translate
  v1->translate(1,1);
  assert((v1->angle() - M_PI/2) < 0.0001);
  v1->endpoint(&p1);
  assert(fabs(p1.x - 1) < 0.0001);
  assert(fabs(p1.y - 11) < 0.0001);
  assert(fabs(v1->magnitude() - 10) < 0.0001);


  // create a new vector at origin (0,0) with angle PI/4 rad, and magnitude 5 
  v1->release();
  v1 = new geom::Vector(0, 0, 3, 3, 5);

  // create a new vector at origin (1,1) with angle 0 rad, and magnitude 3
  v2 = new geom::Vector(0, 0, M_PI/3, 3);

  std::cout << "geom::Vector -- TESTS PASSED" << std::endl;
}
