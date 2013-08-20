
#include "../../include/physics/Object.hpp"


void physics::Object::init(const physics::Material *m){
  // copy over values in material
  mat.density_2D = m->density_2D;
  mat.mu_k = m->mu_k;
  mat.mu_s = m->mu_s;
  mat.restitution = m->restitution;
}

physics::Object::Object(const geom::Point parray[], uint32_t point_count,
                        const physics::Material *m):
                       Polygon(parray, point_count){
  init(m);
}


physics::Object::Object(const geom::Polygon *p, const physics::Material *m): 
                       Polygon(p){
  init(m);
}


physics::Object::Object(const physics::Object *o): 
                       Polygon((geom::Polygon *)o){
  init(&o->mat);
}


double physics::Object::mass() const{
  return mat.density_2D * area();
}


double physics::Object::moment_inertia() const{
  geom::Point p;
  center(&p);
  return moment_inertia(&p);
}


double physics::Object::moment_inertia(const geom::Point *p) const{
  double moment_x, moment_y;
  geom::Point c;

  center(&c);
  moment_x = moment_area_in_x() + area() * (p->x - c.x) * (p->x - c.x);
  moment_y = moment_area_in_y() + area() * (p->y - c.y) * (p->y - c.y);
  return mat.density_2D * (moment_x + moment_y);
}
