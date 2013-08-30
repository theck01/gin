#include "../../include/geom/Line.hpp"

bool geom::Line::contains(const geom::Point *p) const{
  double y_at_x;
  
  // special case: vertical line, check x value matches and y is between
  // segment endpoints
  if(isinf(slope())){
    if(fabs(p->x - p1.x) > geom::ERROR_MARGIN) return false;
    if((p->y >= p1.y && p->y >= p2.y) || (p->y <= p1.y && p->y <= p2.y))
      return false;
    return true;
  }

  // if the x coordinate is not between the x coordinates of the Line's
  // endpoints then line cannot contain the point
  if((p->x >= p1.x && p->x >= p2.x) || (p->x <= p1.x && p->x <= p2.x))
    return false;

  // check if y position at p->x is equal to p->y within some error.
  // if not point is not on line
  y_at_x = slope() * p->x + y_intersect();
  if(fabs(p->y - y_at_x) > geom::ERROR_MARGIN) return false;

  return true;
}


bool geom::Line::intersects(const geom::Line *l) const{
  geom::Point p;
  return point_of_intersection(l, &p);
}


geom::Point * geom::Line::midpoint() const{
  geom::Point *p = new geom::Point();
  midpoint(p);
  return p;
}


void geom::Line::midpoint(geom::Point *p) const{

  // if midpoint cannot be determined, set to NAN
  if(isinf(p1.x) || isnan(p1.x) || isinf(p1.y) || isnan(p1.y) ||
     isinf(p2.x) || isnan(p2.x) || isinf(p2.y) || isnan(p2.y)){
    p->x = NAN;
    p->y = NAN;
    return;
  }

  if(isinf(slope())){
    p->x = p1.x;
    p->y = p1.y + (p2.y - p1.y)/2;
    return;
  }

  p->x = p1.x + (p2.x - p1.x)/2;
  p->y = slope()*p->x + y_intersect();
}


geom::Point * geom::Line::point_of_intersection(const geom::Line *l) const{
  geom::Point *p = new geom::Point();
  if(point_of_intersection(l, p))
    return p;

  // lines do not intersect, return NULL
  p->release();
  return NULL;
}


bool geom::Line::point_of_intersection(const geom::Line *l,
                                       geom::Point *p) const{
  
  // if slopes are equal within a small margin of error they are considered
  // parallel and have no intersection
  if((isinf(slope()) && isinf(l->slope())) || 
     fabs(slope() - l->slope()) < geom::ERROR_MARGIN){
    p->x = NAN;
    p->y = NAN;
    return false;
  }

  // find the point of intersection for infinite lines
  if(isinf(slope())){
    p->x = p1.x;
    p->y = l->slope() * p->x + l->y_intersect();
  }
  else if(isinf(l->slope())){
    p->x = l->p1.x;
    p->y = slope() * p->x + y_intersect();
  }
  else{
    p->x = (l->y_intersect() - y_intersect())/(slope() - l->slope());
    p->y = slope() * p->x + y_intersect();
  }

  // if the point of intersection is within the non-infinite lines, return
  // true with p set to the intersection value
  if(contains(p) && l->contains(p)) return true;

  p->x = NAN;
  p->y = NAN;
  return false;
}
                                        

void geom::Line::set(const geom::Line *l){
  set(l->p1.x, l->p1.y, l->p2.x, l->p2.y);
}


void geom::Line::set(const geom::Point *p, const geom::Point *q){
  set(p->x, p->y, q->x, q->y);
}


void geom::Line::set(double x0, double y0, double x1, double y1){
  p1.x = x0;
  p1.y = y0;
  p2.x = x1;
  p2.y = y1;
}


double geom::Line::slope() const{
  return (p2.y - p1.y)/(p2.x - p1.x);
}


double geom::Line::y_intersect() const {
  double y = p1.y - slope()*p1.x;
  if(fabs(slope()) < geom::ERROR_MARGIN) return p1.y;
  if(isinf(y) || isnan(y)) return NAN;
  return y;
}
