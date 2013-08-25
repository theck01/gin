#include "../../include/geom/Constants.hpp"
#include "../../include/geom/Line.hpp"

int main(){

  geom::Line l1, l2, l3;
  geom::Point p, result;

  // setup test lines
  l1.set(-1,-1,1,1);
  l2.set(1,0,0,1);
  l3.set(-0.25,-1,-0.25,1);


  // test slope
  assert(fabs(l1.slope() - 1) < geom::ERROR_MARGIN);
  assert(fabs(l2.slope() + 1) < geom::ERROR_MARGIN);
  assert(isinf(l3.slope()));


  // test y_intersect
  assert(fabs(l1.y_intersect()) < geom::ERROR_MARGIN);
  assert(fabs(l2.y_intersect() - 1) < geom::ERROR_MARGIN);
  assert(isnan(l3.y_intersect()));


  // test contains
  p.x = 0.25;
  p.y = 0.25;
  assert(l1.contains(&p));
  assert(!l2.contains(&p));
  assert(!l3.contains(&p));

  p.x = 1.0/3.0;
  p.y = 2.0/3.0;
  assert(!l1.contains(&p));
  assert(l2.contains(&p));
  assert(!l3.contains(&p));

  p.x = -0.25;
  p.y = 0.9;
  assert(!l1.contains(&p));
  assert(!l2.contains(&p));
  assert(l3.contains(&p));


  // test intersects
  assert(l1.intersects(&l2));
  assert(l2.intersects(&l1));
  assert(l1.intersects(&l3));
  assert(l3.intersects(&l1));
  assert(!l2.intersects(&l3));
  assert(!l3.intersects(&l2));
  assert(!l1.intersects(&l1));
  assert(!l3.intersects(&l3));


  // test point of intersection
  assert(l1.point_of_intersection(&l2, &result));
  assert(fabs(result.x - 0.5) < geom::ERROR_MARGIN);
  assert(fabs(result.y - 0.5) < geom::ERROR_MARGIN);

  assert(l1.point_of_intersection(&l3, &result));
  assert(fabs(result.x + 0.25) < geom::ERROR_MARGIN);
  assert(fabs(result.y + 0.25) < geom::ERROR_MARGIN);

  assert(l2.point_of_intersection(&l3) == NULL);


  std::cout << "geom::Line -- TESTS PASSED" << std::endl;
}
