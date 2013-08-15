#include "../../include/geom/Polygon.hpp"
#include "../../include/geom/Vector.hpp"

void geom::Polygon::bound(){
  
  uint32_t i;

  bbox.bot_left.x = INFINITY;
  bbox.bot_left.y = INFINITY;
  bbox.top_right.x = -INFINITY;
  bbox.top_right.y = -INFINITY;

  for(i=0; i<num_points; i++){
    if(bbox.bot_left.x > points[i].x) bbox.bot_left.x = points[i].x;
    if(bbox.bot_left.y > points[i].y) bbox.bot_left.y = points[i].y;
    if(bbox.top_right.x < points[i].x) bbox.top_right.x = points[i].x;
    if(bbox.top_right.y < points[i].y) bbox.top_right.y = points[i].y;
  }
}


void geom::Polygon::clear_cache(){
  area_cached = INFINITY;
  center_cached.x = INFINITY;
  center_cached.y = INFINITY;
}


void geom::Polygon::init(const geom::Point parray[], uint32_t point_count){

  uint32_t i;

  // initialize cache values by clearing garbage
  clear_cache();

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

  if(area_cached != INFINITY) return area_cached;

  for(i=0; i<num_points-1; i++)
    sum += points[i].x*points[i+1].y - points[i+1].x*points[i].y;

  sum += points[i].x*points[0].y - points[0].x*points[i].y;

  // update cache
  area_cached = sum/2;
  return signed_area();
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


geom::Rectangle * geom::Polygon::bounding_box() const{
  geom::Rectangle *r = new geom::Rectangle();
  bounding_box(r);
  return r;
}


void geom::Polygon::bounding_box(geom::Rectangle *r) const{
  r->bot_left.x = bbox.bot_left.x;
  r->bot_left.y = bbox.bot_left.y;
  r->top_right.x = bbox.top_right.x;
  r->top_right.y = bbox.top_right.y;
}


geom::Point * geom::Polygon::center() const{
  geom::Point *p = new Point();
  center(p);
  return p;
}


void geom::Polygon::center(geom::Point *p) const{
  
  uint32_t i;
  double x_sum = 0;
  double y_sum = 0;
  double intermediate = 0;

  // return cached value if possible
  if(center_cached.x < INFINITY || center_cached.y < INFINITY){
    p->x = center_cached.x;
    p->y = center_cached.y;
    return;
  }

  for(i=0; i<num_points-1; i++){
    intermediate = points[i].x*points[i+1].y - points[i+1].x*points[i].y;
    x_sum += (points[i].x + points[i+1].x)*intermediate;
    y_sum += (points[i].y + points[i+1].y)*intermediate;
  }
  
  intermediate = points[i].x*points[0].y - points[0].x*points[i].y;
  x_sum += (points[i].x + points[0].x)*intermediate;
  y_sum += (points[i].y + points[0].y)*intermediate;

  // update cache
  center_cached.x = x_sum/(6*signed_area());
  center_cached.y = y_sum/(6*signed_area());

  center(p);
}


bool geom::Polygon::contains(const geom::Point *p) const{
  return contains(p->x, p->y);
}


bool geom::Polygon::contains(double x, double y) const{

  uint32_t i, inter;
  double slope, x_at_y;

  // quick bounding box check
  if(x < bbox.bot_left.x || y < bbox.bot_left.y || x > bbox.top_right.x ||
     y > bbox.top_right.y){
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


bool geom::Polygon::intersects(const geom::Polygon *p) const{
  uint32_t i;
  for(i=0; i<num_points; i++){
    if(p->contains(&(points[i]))) return true;
  }
  return false;
}


void geom::Polygon::print() const{
  uint32_t i;
  std::cerr << "Polygon:" << std::endl;
  std::cerr << "    points:" << std::endl;
  for(i=0; i<num_points; i++){
    std::cerr << "    (" << points[i].x << "," << points[i].y << ")";
    std::cerr << std::endl;  
  }
}


void geom::Polygon::rotate(double rad){
  geom::Point p;
  center(&p);
  rotate(p.x, p.y, rad);

  // update cache
  center_cached.x = p.x;
  center_cached.y = p.y;
}


void geom::Polygon::rotate(const geom::Point *center, double rad){
	rotate(center->x, center->y, rad);
}


void geom::Polygon::rotate(double x, double y, double rad){

  uint32_t i;
  double rx, ry, sine, cosine;
  double a = area_cached;

  sine = sin(rad);
  cosine = cos(rad);

  for(i=0; i<num_points; i++){
    rx = cosine*(points[i].x - x) - sine*(points[i].y - y);
    ry = sine*(points[i].x - x) + cosine*(points[i].y - y);
    points[i].x = rx + x;
    points[i].y = ry + y;
  }
  
  bound();
  clear_cache();
  a = area_cached;
}


void geom::Polygon::scale(double factor){
  double a = area_cached;
  geom::Point p;
  center(&p);
  scale(&p, factor);

  // update cache
  area_cached = a*factor*factor;
  center_cached.x = p.x;
  center_cached.y = p.y;
}


void geom::Polygon::scale(const geom::Point *center, double factor){
  scale(center->x, center->y, factor);
}


void geom::Polygon::scale(double x, double y, double factor){
  uint32_t i;
  for(i=0; i<num_points; i++){
    points[i].x = factor*(points[i].x - x) + x;
    points[i].y = factor*(points[i].y - y) + y;
  }
  bound();
  clear_cache();
}


void geom::Polygon::translate(const geom::Point *shift){
  translate(shift->x, shift->y);
}


void geom::Polygon::translate(double x, double y){
  uint32_t i;
  for(i=0; i<num_points; i++){
    points[i].x += x;
    points[i].y += y;
  }

  // translate bounding box
  bbox.bot_left.x += x;
  bbox.top_right.x += x;
  bbox.bot_left.y += y;
  bbox.top_right.y += y;

  // translate cached center, area is unaffected
  center_cached.x += x;
  center_cached.y += y;
}
