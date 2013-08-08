#include "../../include/geom/Vector.hpp"

int main(){

  geom::Vector *v1, *v2, *result;
  geom::Point p;
  geom::Point origin;

  origin.x = 0;
  origin.y = 0;

  // create a new vector at origin (0,0) with angle PI/4 rad, and magnitude 5 
  v1 = new geom::Vector(&origin, M_PI/4, 5);


  // test angle
  assert(fabs(v1->angle() - M_PI/4) < 0.0001);

  // test endpoint
  v1->endpoint(&p);
  assert(fabs(p.x - sqrt(12.5)) < 0.0001);
  assert(fabs(p.y - sqrt(12.5)) < 0.0001);

  // test magnitude
  assert(fabs(v1->magnitude() - 5) < 0.0001);

  // test rotate
  v1->rotate(M_PI/4);
  assert((v1->angle() - M_PI/2) < 0.0001);
  v1->endpoint(&p);
  assert(fabs(p.x) < 0.0001);
  assert(fabs(p.y - 5) < 0.0001);
  assert(fabs(v1->magnitude() - 5) < 0.0001);

  // test scale
  v1->scale(2);
  assert((v1->angle() - M_PI/2) < 0.0001);
  v1->endpoint(&p);
  assert(fabs(p.x) < 0.0001);
  assert(fabs(p.y - 10) < 0.0001);
  assert(fabs(v1->magnitude() - 10) < 0.0001);

  // test translate
  v1->translate(1,1);
  assert((v1->angle() - M_PI/2) < 0.0001);
  v1->endpoint(&p);
  assert(fabs(p.x - 1) < 0.0001);
  assert(fabs(p.y - 11) < 0.0001);
  assert(fabs(v1->magnitude() - 10) < 0.0001);


  // create a new vector at origin (0,0) with angle PI/4 rad, and magnitude 5 
  v1->release();
  v1 = new geom::Vector(&origin, M_PI/4, 5);

  // create a new vector at origin (0,0) with angle 0 rad, and magnitude 5
  v2 = new geom::Vector(0, 0, 5, 0);

  // test add
  result = v1->add(v2);
  result->endpoint(&p);
  assert(fabs(p.x - (5+5/sqrt(2))) < 0.0001);
  assert(fabs(p.y - 5/sqrt(2)) < 0.0001);
  result->release();

  // test angle_between
  assert(fabs(v1->angle_between(v2) - M_PI/4) < 0.0001);

  // test cross
  assert(fabs(v2->cross(v1) - 25/sqrt(2)) < 0.0001);

  // test dot
  assert(fabs(cos(v1->angle_between(v2))*v1->magnitude() * v2->magnitude() -
              v1->dot(v2)) < 0.0001);

  // test projection
  result = v1->projection(v2);
  result->endpoint(&p);
  assert(fabs(p.x - 5/sqrt(2)) < 0.0001);
  assert(fabs(p.y) < 0.0001);
  result->release();

  // test subtraction
  result = v1->sub(v2);
  result->endpoint(&p);
  assert(fabs(p.x - (5/sqrt(2) - 5)) < 0.0001);
  assert(fabs(p.y - 5/sqrt(2)) < 0.0001);
  result->release();

  
  // Clean up after tests
  v1->release();
  v2->release();

  std::cout << "geom::Vector -- TESTS PASSED" << std::endl;
}
