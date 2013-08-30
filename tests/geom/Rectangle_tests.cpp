#include "../../include/geom/Rectangle.hpp"

int main(){
  geom::Rectangle r1, r2, r3;
  geom::Line l1, l2, l3;
  geom::Line lines[3];
  geom::Point p;
  std::vector<geom::Line> v;

  // setup test objects
  r1.set(-1,-1,1,1);
  r2.set(-2,-0.5,2,0.5);
  r3.set(-0.25,-0.25,0.25,0.25);
  l1.set(0.75, 0.75, 0.75, 1.25);
  lines[0].set(&l1);
  l2.set(-3, 0.7, -1.5, 0.2);
  lines[1].set(&l2);
  l3.set(-0.1, 0, 0.1, 0);
  lines[2].set(&l3);
  v.clear();


  // test contains
  p.x = 0;
  p.y = 0;
  assert(r1.contains(&p));
  assert(r2.contains(&p));
  assert(r3.contains(&p));

  p.x = -1.5;
  p.y = 0;
  assert(!r1.contains(&p));
  assert(r2.contains(&p));
  assert(!r3.contains(&p));

  p.x = -0.5;
  p.y = 0.75;
  assert(r1.contains(&p));
  assert(!r2.contains(&p));
  assert(!r3.contains(&p));


  // test line intersects
  assert(r1.intersects(&l1));
  assert(!r2.intersects(&l1));
  assert(!r3.intersects(&l1));

  assert(!r1.intersects(&l2));
  assert(r2.intersects(&l2));
  assert(!r3.intersects(&l2));

  assert(r1.intersects(&l3));
  assert(r2.intersects(&l3));
  assert(r3.intersects(&l3));


  // test rectangle intersects
  assert(r1.intersects(&r2));
  assert(r2.intersects(&r1));
  assert(r1.intersects(&r3));
  assert(r3.intersects(&r1));
  assert(r2.intersects(&r3));
  assert(r3.intersects(&r2));

  r1.set(10,10,11,11);
  assert(!r1.intersects(&r2));
  assert(!r2.intersects(&r1));
  assert(!r1.intersects(&r3));
  assert(!r3.intersects(&r1));
  assert(r2.intersects(&r3));
  assert(r3.intersects(&r2));

  
  // test lines_intersected
  r1.set(-1,-1,1,1);
  r1.lines_intersected(&v, lines, 3);
  assert(v.size() == 2);
  assert(fabs(v[0].p1.x - 0.75) < geom::ERROR_MARGIN);
  assert(fabs(v[1].p1.x + 0.1) < geom::ERROR_MARGIN);

  v.clear();
  r2.lines_intersected(&v, lines, 3);
  assert(v.size() == 2);
  assert(fabs(v[0].p1.x + 3) < geom::ERROR_MARGIN);
  assert(fabs(v[1].p1.x + 0.1) < geom::ERROR_MARGIN);

  v.clear();
  r3.lines_intersected(&v, lines, 3);
  assert(v.size() == 1);
  assert(fabs(v[0].p1.x + 0.1) < geom::ERROR_MARGIN);


  std::cout << "geom::Rectangle -- TESTS PASSED" << std::endl;
}

