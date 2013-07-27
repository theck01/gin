#include "../../include/geom/Polygon.hpp"
#include "../../include/geom/Point.hpp"

int main(){
  
  geom::Polygon *square, *triangle, *p;
  geom::Point square_points[4];
  geom::Point triangle_points[4];

  // initialize points arrays
  square_points[0].x = 0;
  square_points[0].y = 0;
  square_points[1].x = 1;
  square_points[1].y = 0;
  square_points[2].x = 1;
  square_points[2].y = 1;
  square_points[3].x = 0;
  square_points[3].y = 1;

  triangle_points[0].x = -2;
  triangle_points[0].y =  0;
  triangle_points[1].x = -1.5;
  triangle_points[1].y =  1;
  triangle_points[2].x = -1;
  triangle_points[2].y =  0;

  square = new geom::Polygon(square_points, 4);
  triangle = new geom::Polygon(triangle_points, 3);

  // test area method, with some padding to accomadate for the double result
  assert(abs(square->area() - 1) < 0.001);
  assert(abs(triangle->area() - 0.5) < 0.001);

  // test contains method (direct cordinates only rather than point
  assert(square->contains(0.5,0.5));
  assert(square->contains(0.99,0.01));
  assert(square->contains(0.01,0.01));
  assert(!square->contains(1.01,0.5));
  assert(!square->contains(-0.01,0.5));

  assert(triangle->contains(-1.5,0.5));
  assert(triangle->contains(-1.8,0.01));
  assert(triangle->contains(-1.01,0.001));
  assert(!triangle->contains(-1.76,0.5));
  assert(!triangle->contains(-1.5,-0.001));
  
  // test orientation method
  assert(square->orientation() == 1);
  assert(triangle->orientation() == -1);

  // test translation
  triangle->translate(1,0);
  assert(!triangle->contains(-1.5,0.5));
  assert(triangle->contains(-0.5,0.5));
  assert(abs(triangle->area() - 0.5) < 0.001);

  // test rotation
  square->rotate(0.5, 0.5, M_PI/2);
  assert(square->contains(0.5,0.5));
  assert(square->contains(0.99,0.01));
  assert(square->contains(0.01,0.01));
  assert(!square->contains(1.01,0.5));
  assert(!square->contains(-0.01,0.5));
  assert(abs(square->area() - 1) < 0.001);

  square->rotate(0, 0, -M_PI/2);
  assert(square->contains(0.5,-0.5));
  assert(square->contains(0.99,-0.01));
  assert(square->contains(0.01,-0.01));
  assert(!square->contains(1.01,-0.5));
  assert(!square->contains(-0.01,-0.5));
  assert(abs(square->area() - 1) < 0.001);

  // test overlap
  assert(!square->overlaps(triangle));
  square->translate(-0.5, 0.5);
  assert(square->overlaps(triangle));

  // test copy
  p = new geom::Polygon(square);
  assert(abs(p->area() - 1) < 0.001);
  p->translate(10,10);
  assert(square->overlaps(triangle));
  assert(!square->overlaps(p));
  assert(!p->overlaps(triangle));

  // tests completed
  std::cout << "geom::Polygon -- TESTS PASSED" << std::endl;
}
