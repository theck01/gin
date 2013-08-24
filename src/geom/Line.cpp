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
                                        

double geom::Line::slope() const{
  return (p2.y - p1.y)/(p2.x - p1.x);
}


double geom::Line::y_intersect() const {
  double y = p1.y - slope()*p1.x;
  if(isinf(y)) return NAN;
  return y;
}
