#include "../../include/geom/Vector.hpp"

void geom::Vector::init(double x0, double y0, double x1, double y1){
  geom::Point p;
  p.x = x0;
  p.y = y0;
  double angle = atan((y1-y0)/(x1-x0));
  double magnitude = sqrt((y1-y0)*(y1-y0) + (x1-x0)*(x1-x0));
  init(&p, angle, magnitude);
}


void geom::Vector::init(const geom::Point *o, double angle, double mag){
  origin.x = o->x;
  origin.y = o->y;
  unit.x = cos(angle);
  unit.y = sin(angle);
  size = mag;
}


double geom::Vector::unitize(){
  double mag = sqrt(unit.x*unit.x + unit.y*unit.y);
  unit.x /= mag;
  unit.y /= mag;
  return mag;
}


geom::Vector::Vector(const geom::Point *o, const geom::Point *endpoint){
  init(o->x, o->y, endpoint->x, endpoint->y);
}


geom::Vector::Vector(double x0, double y0, double x1, double y1){
  init(x0, y0, x1, y1);
}


geom::Vector::Vector(const geom::Point *o, double angle, double mag){
  init(o, angle, mag);
}


geom::Vector::Vector(const geom::Vector *v){
  init(v->origin.x, v->origin.y, v->unit.x*v->size, v->unit.y*v->size);
}


geom::Vector * geom::Vector::add(const geom::Vector *v) const{
  geom::Vector *result = new Vector(0,0,0,0);
  add(v, result);
  return result;
}


void geom::Vector::add(const geom::Vector *v, geom::Vector *result) const{
  result->origin.x = origin.x;
  result->origin.y = origin.y;
  result->unit.x = unit.x*size + v->unit.x*v->size;
  result->unit.y = unit.y*size + v->unit.y*v->size;
  result->size = result->unitize();
}


double geom::Vector::angle() const{
  if(unit.x > 0) return atan(unit.y/unit.x);
  return atan(unit.y/unit.x) + M_PI;
}


double geom::Vector::angle_between(const geom::Vector *v) const{
  return acos(dot(v)/(magnitude()*v->magnitude()));
}


double geom::Vector::cross(const geom::Vector *v) const{
  return (unit.x * size * v->unit.y * v->size) - 
         (unit.y * size * v->unit.x * v->size);
}


double geom::Vector::dot(const geom::Vector *v) const{
  return (unit.x * size * v->unit.x * v->size) + 
         (unit.y * size * v->unit.y * v->size);
}


geom::Point * geom::Vector::endpoint() const{
  geom::Point *p = new Point();
  endpoint(p);
  return p;
}

void geom::Vector::endpoint(geom::Point *p) const{
  p->x = origin.x + unit.x*size;
  p->y = origin.y + unit.y*size;
}


double geom::Vector::magnitude() const{
  return size;
}


void geom::Vector::print() const{
  std::cerr << "Vector:" << std::endl;
  std::cerr << "    origin: (" << origin.x << "," << origin.y << ")";
  std::cerr << std::endl;
  std::cerr << "    angle: " << angle()  << " rad" << std::endl;
  std::cerr << "    magnitude: " << magnitude()  << std::endl;
}


geom::Vector * geom::Vector::projection(const geom::Vector *v) const{
  geom::Vector *result = new Vector(0,0,0,0);
  projection(v, result);
  return result;
}


void geom::Vector::projection(const geom::Vector *v, 
                              geom::Vector *result) const{
  result->origin.x = origin.x;
  result->origin.y = origin.y;
  result->unit.x = v->unit.x;
  result->unit.y = v->unit.y;
  result->size = 1;
  result->size = dot(result);
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


geom::Vector * geom::Vector::sub(const geom::Vector *v) const{
  geom::Vector *result = new Vector(0,0,0,0);
  sub(v, result);
  return result;
}


void geom::Vector::sub(const geom::Vector *v, geom::Vector *result) const{
  result->origin.x = origin.x;
  result->origin.y = origin.y;
  result->unit.x = unit.x*size - v->unit.x*v->size;
  result->unit.y = unit.y*size - v->unit.y*v->size;
  result->size = result->unitize();
}


void geom::Vector::translate(const geom::Point *p){
  translate(p->x, p->y);
}


void geom::Vector::translate(double x, double y){
  origin.x += x;
  origin.y += y;
}
