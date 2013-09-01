#include "../../include/geom/Polygon.hpp"

int main(){
  
  geom::Polygon *square, *triangle, *p;
  geom::Point square_points[4];
  geom::Point triangle_points[4];
  geom::Point *center;
  geom::Rectangle bbox;
  std::vector<geom::Point> ips;

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
  assert(abs(square->area() - 1) < geom::ERROR_MARGIN);
  assert(abs(triangle->area() - 0.5) < geom::ERROR_MARGIN);

  // test bounding box method
  square->bounding_box(&bbox);
  assert(fabs(bbox.bot_left.x) < geom::ERROR_MARGIN);
  assert(fabs(bbox.bot_left.y) < geom::ERROR_MARGIN);
  assert(fabs(bbox.top_right.x - 1) < geom::ERROR_MARGIN);
  assert(fabs(bbox.top_right.y - 1) < geom::ERROR_MARGIN);

  // test the center method
  center =  square->center();
  assert(center->x > 0.499 && center->x < 0.501 && center->y > 0.499 &&
         center->y < 0.501);
  center->release();

  center =  triangle->center();
  assert(center->x > -1.501 && center->x < -1.499 && center->y > 0.332 &&
         center->y < 0.334);
  center->release();

  // test contains method (direct cordinates only rather than point
  assert(square->contains(0.5,0.5));
  assert(square->contains(0.99,0.01));
  assert(square->contains(0.01,0.01));
  assert(!square->contains(1.01,0.5));
  assert(!square->contains(-0.01,0.5));

  assert(triangle->contains(-1.5,0.5));
  assert(triangle->contains(-1.8,0.01));
  assert(triangle->contains(-1.01,geom::ERROR_MARGIN));
  assert(!triangle->contains(-1.76,0.5));
  assert(!triangle->contains(-1.5,-geom::ERROR_MARGIN));

  // test moment of area methods
  assert(fabs(square->moment_area_in_x() - 1.0/12) < geom::ERROR_MARGIN);
  assert(fabs(square->moment_area_in_y() - 1.0/12) < geom::ERROR_MARGIN);
  assert(fabs(square->moment_area_polar() - square->moment_area_in_x() -
              square->moment_area_in_y()) < geom::ERROR_MARGIN);
  
  // test orientation method
  assert(square->orientation() == 1);
  assert(triangle->orientation() == -1);

  // test translation
  triangle->translate(1,0);
  assert(!triangle->contains(-1.5,0.5));
  assert(triangle->contains(-0.5,0.5));
  assert(abs(triangle->area() - 0.5) < geom::ERROR_MARGIN);

  // test scaling
  assert(!square->contains(-0.1,-0.1));
  assert(!square->contains(1.1,1.1));

  square->scale(2);

  assert(square->contains(-0.1,-0.1));
  assert(!square->contains(-0.6,-0.6));
  assert(square->contains(1.1,1.1));
  assert(!square->contains(1.6,1.6));

  square->scale(0.5);

  assert(!square->contains(-0.1,-0.1));
  assert(!square->contains(1.1,1.1));


  // test rotation
  square->rotate(0.5, 0.5, M_PI/2);
  assert(square->contains(0.5,0.5));
  assert(square->contains(0.99,0.01));
  assert(square->contains(0.01,0.01));
  assert(!square->contains(1.01,0.5));
  assert(!square->contains(-0.01,0.5));
  assert(abs(square->area() - 1) < geom::ERROR_MARGIN);

  square->rotate(0, 0, -M_PI/2);
  assert(square->contains(0.5,-0.5));
  assert(square->contains(0.99,-0.01));
  assert(square->contains(0.01,-0.01));
  assert(!square->contains(1.01,-0.5));
  assert(!square->contains(-0.01,-0.5));
  assert(abs(square->area() - 1) < geom::ERROR_MARGIN);

  // test intersects
  assert(!square->intersects(triangle));
  square->translate(-0.5, 0.5);
  assert(square->intersects(triangle));

  // test intersection_points
  square->intersection_points(triangle, &ips);
  assert(ips.size() == 2);
  assert(fabs(ips[0].x + 0.25) < geom::ERROR_MARGIN);
  assert(fabs(ips[0].y - 0.5) < geom::ERROR_MARGIN);
  assert(fabs(ips[1].x + 0.5) < geom::ERROR_MARGIN);
  assert(fabs(ips[1].y) < geom::ERROR_MARGIN);

  // test copy
  p = new geom::Polygon(square);
  assert(abs(p->area() - 1) < geom::ERROR_MARGIN);
  p->translate(10,10);
  assert(square->intersects(triangle));
  assert(!square->intersects(p));
  assert(!p->intersects(triangle));

  // memory cleanup
  p->release();
  square->release();
  triangle->release();

  // tests completed
  std::cout << "geom::Polygon -- TESTS PASSED" << std::endl;
}
