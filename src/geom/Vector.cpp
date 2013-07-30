#include "../../include/geom/Vector.hpp"

void geom::Vector::init(double x, double y, double u, double v, double mag){
  origin.x = x;
  origin.y = y;
  unit.x = u;
  unit.y = v;
  size = mag;
  unitize();
}


void geom::Vector::init(double x, double y, double angle, double mag){
  double u, v;
  u = cos(angle);
  v = sin(angle);
  init(x,y,u,v,mag);
}


void geom::Vector::unitize(){
  double mag = sqrt(unit.x*unit.x + unit.y*unit.y);
  unit.x /= mag;
  unit.y /= mag;
}


geom::Vector::Vector(geom::Point *o, geom::Point *dir, double mag){
  init(o->x, o->y, dir->x, dir->y, mag);
}


geom::Vector::Vector(geom::Point *o, double angle, double mag){
  init(o->x, o->y, angle, mag);
}


geom::Vector::Vector(double x, double y, double angle, double mag){
  init(x, y, angle, mag);
}


geom::Vector::Vector(geom::Vector *v){
  init(v->origin.x, v->origin.y, v->unit.x, v->unit.y, v->size);
}


double geom::Vector::angle(){
  if(unit.x > 0) return atan(unit.y/unit.x);
  return atan(unit.y/unit.x) + M_PI;
}


double geom::Vector::cross(geom::Vector *v){
  return (origin.x * size * v->origin.y * v->size) - 
         (origin.y * size * v->origin.x * v->size);
}


double geom::Vector::dot(geom::Vector *v){
  return (origin.x * size * v->origin.x * v->size) + 
         (origin.y * size * v->origin.y * v->size);
}


double geom::Vector::magnitude(){
  return size;
}


void geom::Vector::rotate(double rad){
  double rx, ry, sine, cosine;

  sine = sin(rad);
  cosine = cos(rad);

  rx = cosine*unit.x - sine*unit.y;
  ry = sine*unit.x + cosine*unit.y;

  unit.x = rx;
  unit.y = ry;
}


void geom::Vector::scale(double factor){
  size *= factor;
}


void geom::Vector::translate(geom::Point *p){
  translate(p->x, p->y);
}


void geom::Vector::translate(double x, double y){
  origin.x += x;
  origin.y += y;
}
