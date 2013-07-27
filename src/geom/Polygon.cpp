#include "../../include/geom/Polygon.hpp"

void geom::Polygon::bound(){
  
  uint32_t i;

  bbox[0].x = INFINITY;
  bbox[0].y = INFINITY;
  bbox[1].x = -INFINITY;
  bbox[1].y = -INFINITY;

  for(i=0; i<num_points; i++){
    if(bbox[0].x > points[i].x) bbox[0].x = points[i].x;
    if(bbox[0].y > points[i].y) bbox[0].y = points[i].y;
    if(bbox[1].x < points[i].x) bbox[1].x = points[i].x;
    if(bbox[1].y < points[i].y) bbox[1].y = points[i].y;
  }
}


void geom::Polygon::init(const geom::Point parray[], uint32_t point_count){

  uint32_t i;

  num_points = point_count;
  points = new geom::Point[num_points];
  for(i=0; i<num_points; i++){
    points[i].x = parray[i].x;
    points[i].y = parray[i].y;
  }

  bound();
}


double geom::Polygon::signed_area() const{
  uint32_t i;
  double sum = 0;

  for(i=0; i<num_points-1; i++)
    sum += points[i].x*points[i+1].y - points[i+1].x*points[i].y;

  sum += points[i].x*points[0].y - points[0].x*points[i].y;
  return sum/2;
}


geom::Polygon::Polygon(const geom::Point parray[], uint32_t point_count){
  init(parray, point_count);
}


geom::Polygon::Polygon(const geom::Polygon *p){
  init(p->points, p->num_points);
}


geom::Polygon::~Polygon(){
  delete[] points;
}


double geom::Polygon::area() const{
  return fabs(signed_area());
}


bool geom::Polygon::contains(const geom::Point *p) const{
  return contains(p->x, p->y);
}


bool geom::Polygon::contains(double x, double y) const{

  uint32_t i, inter;
  double slope, x_at_y;

  // quick bounding box check
  if(x < bbox[0].x || y < bbox[0].y || x > bbox[1].x ||
     y > bbox[1].y){
    return false;
  }

  // detailed ray casting check
  inter = 0;
  // for all line segments in perimeter of polygon but the last
  for(i=0; i<num_points-1; i++){
    //horizontal ray check from point to x -> -INFINITY
    if((y <= points[i].y && y >= points[i+1].y) ||
       (y >= points[i].y && y <= points[i+1].y)){
      slope = (points[i+1].y - points[i].y)/(points[i+1].x - points[i].x);
      x_at_y = (y - points[i].y)/slope + points[i].x;
      if(x > x_at_y) inter++;
    }
  }

  //horizontal ray check from point to x -> -INFINITY, for final segment
  if((y <= points[i].y && y >= points[0].y) ||
     (y >= points[i].y && y <= points[0].y)){
    slope = (points[0].y - points[i].y)/(points[0].x - points[i].x);
    x_at_y = (y - points[i].y)/slope + points[i].x;
    if(x > x_at_y) inter++;
  }

  // if the number of interections of perimeter line segments is odd then
  // the point must lie in the polygon
  if(inter%2) return true;
  return false;
}


int8_t geom::Polygon::orientation() const{
  if(signed_area() < 0) return -1;
  return 1;
}


bool geom::Polygon::overlaps(const geom::Polygon *p) const{
  uint32_t i;
  for(i=0; i<num_points; i++){
    if(p->contains(&(points[i]))) return true;
  }
  return false;
}


void geom::Polygon::rotate(const geom::Point *center, double rad){
	rotate(center->x, center->y, rad);
}


void geom::Polygon::rotate(double x, double y, double rad){
  uint32_t i;
  double rx, ry, sine, cosine;

  sine = sin(rad);
  cosine = cos(rad);

  for(i=0; i<num_points; i++){
    rx = cosine*(points[i].x - x) - sine*(points[i].y - y);
    ry = sine*(points[i].x - x) + cosine*(points[i].y - y);
    points[i].x = rx + x;
    points[i].y = ry + y;
  }
  
  bound();
}


void geom::Polygon::translate(double x, double y){
  uint32_t i;
  for(i=0; i<num_points; i++){
    points[i].x += x;
    points[i].y += y;
  }
  bound();
}
