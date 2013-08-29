#include "../../include/geom/Polygon.hpp"

void geom::Polygon::bound(){
  
  uint32_t i;

  bbox.set(INFINITY, INFINITY, -INFINITY, -INFINITY);

  for(i=0; i<num_verticies; i++){
    if(bbox.bot_left.x > verticies[i].x) bbox.bot_left.x = verticies[i].x;
    if(bbox.bot_left.y > verticies[i].y) bbox.bot_left.y = verticies[i].y;
    if(bbox.top_right.x < verticies[i].x) bbox.top_right.x = verticies[i].x;
    if(bbox.top_right.y < verticies[i].y) bbox.top_right.y = verticies[i].y;
  }
}


void geom::Polygon::clear_cache(){
  area_cached = NAN;
  center_cached.x = NAN;
  center_cached.y = NAN;
  x_moment_cached = NAN;
  y_moment_cached = NAN;
  polar_moment_cached = NAN;
}


void geom::Polygon::init(const geom::Point parray[], uint32_t point_count){

  uint32_t i;

  // initialize cache values by clearing garbage
  clear_cache();

  num_verticies = point_count;
  verticies = new geom::Point[num_verticies];
  sides = new geom::Line[num_verticies];
  for(i=0; i<num_verticies; i++){
    verticies[i].x = parray[i].x;
    verticies[i].y = parray[i].y;
  }

  bound();
  update_sides();
}


double geom::Polygon::signed_area() const{

  uint32_t i;
  double sum = 0;

  if(!isnan(area_cached)) return area_cached;

  for(i=0; i<num_verticies-1; i++)
    sum += verticies[i].x*verticies[i+1].y - verticies[i+1].x*verticies[i].y;

  sum += verticies[i].x*verticies[0].y - verticies[0].x*verticies[i].y;

  // update cache
  area_cached = sum/2;
  return area_cached;
}


void geom::Polygon::update_sides(){
  uint32_t i;
  for(i=0; i<num_verticies; i++)
    sides[i].set(&verticies[i], &verticies[(i+1)%num_verticies]);
}


geom::Polygon::Polygon(const geom::Point parray[], uint32_t point_count){
  init(parray, point_count);
}


geom::Polygon::Polygon(const geom::Polygon *p){
  init(p->verticies, p->num_verticies);
}


geom::Polygon::~Polygon(){
  delete[] verticies;
  delete[] sides;
}


double geom::Polygon::area() const{
  return fabs(signed_area());
}


geom::Rectangle * geom::Polygon::bounding_box() const{
  geom::Rectangle *r = new geom::Rectangle(bbox);
  bounding_box(r);
  return r;
}


void geom::Polygon::bounding_box(geom::Rectangle *r) const{
  r->set(&bbox);
}


geom::Point * geom::Polygon::center() const{
  geom::Point *p = new geom::Point();
  center(p);
  return p;
}


void geom::Polygon::center(geom::Point *p) const{
  
  uint32_t i;
  double x_sum = 0;
  double y_sum = 0;
  double intermediate = 0;

  // return cached value if possible
  if(!isnan(center_cached.x) && !isnan(center_cached.y)){
    p->x = center_cached.x;
    p->y = center_cached.y;
    return;
  }

  for(i=0; i<num_verticies-1; i++){
    intermediate = verticies[i].x*verticies[i+1].y - 
                   verticies[i+1].x*verticies[i].y;
    x_sum += (verticies[i].x + verticies[i+1].x)*intermediate;
    y_sum += (verticies[i].y + verticies[i+1].y)*intermediate;
  }
  
  intermediate = verticies[i].x*verticies[0].y - 
                 verticies[0].x*verticies[i].y;
  x_sum += (verticies[i].x + verticies[0].x)*intermediate;
  y_sum += (verticies[i].y + verticies[0].y)*intermediate;

  // update cache
  center_cached.x = x_sum/(6*signed_area());
  center_cached.y = y_sum/(6*signed_area());

  center(p);
}


bool geom::Polygon::contains(const geom::Point *p) const{
  uint32_t i, inter_count;
  geom::Line ray;

  // do quick bounding box check first
  if(!bbox.contains(p)) return false;

  // ray cast, if number of ray intersections is odd then point is inside
  // polygon
  inter_count = 0;
  ray.set(-INFINITY, p->y, p->x, p->y);

  for(i=0; i<num_verticies; i++){
    if(sides[i].intersects(&ray)){
      inter_count++;
      //std::cout << "Side " << i << " intersected by ray" << std::endl;
      //std::cout << sides[i].p1.x << "," << sides[i].p1.y << "  ";
      //std::cout << sides[i].p2.x << "," << sides[i].p2.y << std::endl;
    }
  }
    

  if(inter_count%2) return true;
  return false;
}


bool geom::Polygon::contains(double x, double y) const{
  geom::Point p;
  p.x = x;
  p.y = y;
  return contains(&p);
}


bool geom::Polygon::intersects(const geom::Line *l) const{
  uint32_t i;

  // initial bounding box check
  if(!bbox.intersects(l)) return false;

  if(contains(&l->p1) || contains(&l->p2)) return true;

  for(i=0; i<num_verticies; i++)
    if(sides[i].intersects(l)) return true;

  return false;
}


bool geom::Polygon::intersects(const geom::Rectangle *r) const{
  uint32_t i;

  // initial bounding box check
  if(!bbox.intersects(r)) return false;

  if(contains(&r->bot_left) || contains(&r->top_right)) return true;

  for(i=0; i<num_verticies; i++)
    if(r->intersects(&sides[i])) return true;

  return false;
}


bool geom::Polygon::intersects(const geom::Polygon *p) const{
  uint32_t i;

  // initial bounding box check
  if(!p->intersects(&bbox)) return false;

  // check to see if any verticie is within the polygon
  for(i=0; i<num_verticies; i++)
    if(p->contains(&verticies[i])) return true;

  // check to see if any lines intersect the polygon
  for(i=0; i<num_verticies; i++)
    if(p->intersects(&sides[i])) return true;

  return false;
}


double geom::Polygon::moment_area_in_x() const{

  uint32_t i;
  double sum, tri_area, edge_comp;
  // offset of edge from centroid of shape
  double x1_off, x2_off, y1_off, y2_off; 
  geom::Point c;

  if(!isnan(x_moment_cached)) return x_moment_cached;

  sum = 0;
  center(&c);

  // incrementally compute moment of area sum for x for first n-1 edges
  for(i=0; i<num_verticies-1; i++){
    x1_off = verticies[i].x - c.x;
    x2_off = verticies[i+1].x - c.x;
    y1_off = verticies[i].y - c.y;
    y2_off = verticies[i+1].y - c.y;

    tri_area = x1_off*y2_off - x2_off*y1_off;
    edge_comp = x1_off*x1_off + x1_off*x2_off + x2_off*x2_off;
    sum += tri_area * edge_comp;
  }

  // add final edge to sum
  x1_off = verticies[i].x - c.x;
  x2_off = verticies[0].x - c.x;
  y1_off = verticies[i].y - c.y;
  y2_off = verticies[0].y - c.y;

  tri_area = x1_off*y2_off - x2_off*y1_off;
  edge_comp = x1_off*x1_off + x1_off*x2_off + x2_off*x2_off;
  sum += tri_area * edge_comp;

  x_moment_cached = sum/12;
  return x_moment_cached;
}


double geom::Polygon::moment_area_in_y() const{

  uint32_t i;
  double sum, tri_area, edge_comp;
  // offset of edge from centroid of shape
  double x1_off, x2_off, y1_off, y2_off; 
  geom::Point c;

  if(!isnan(y_moment_cached)) return y_moment_cached;

  sum = 0;
  center(&c);

  // incrementally compute moment of area sum for x for first n-1 edges
  for(i=0; i<num_verticies-1; i++){
    x1_off = verticies[i].x - c.x;
    x2_off = verticies[i+1].x - c.x;
    y1_off = verticies[i].y - c.y;
    y2_off = verticies[i+1].y - c.y;

    tri_area = x1_off*y2_off - x2_off*y1_off;
    edge_comp = y1_off*y1_off + y1_off*y2_off + y2_off*y2_off;
    sum += tri_area * edge_comp;
  }

  // add final edge to sum
  x1_off = verticies[i].x - c.x;
  x2_off = verticies[0].x - c.x;
  y1_off = verticies[i].y - c.y;
  y2_off = verticies[0].y - c.y;

  tri_area = x1_off*y2_off - x2_off*y1_off;
  edge_comp = y1_off*y1_off + y1_off*y2_off + y2_off*y2_off;
  sum += tri_area * edge_comp;

  y_moment_cached = sum/12;
  return y_moment_cached;
}


double geom::Polygon::moment_area_polar() const{
  if(!isnan(polar_moment_cached)) return polar_moment_cached;
  polar_moment_cached = moment_area_in_x() + moment_area_in_y();
  return polar_moment_cached;
}


int8_t geom::Polygon::orientation() const{
  if(signed_area() < 0) return -1;
  return 1;
}


void geom::Polygon::print() const{
  uint32_t i;
  std::cerr << "Polygon:" << std::endl;
  std::cerr << "    verticies:" << std::endl;
  for(i=0; i<num_verticies; i++){
    std::cerr << "    (" << verticies[i].x << "," << verticies[i].y << ")";
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
  double pm = polar_moment_cached;

  sine = sin(rad);
  cosine = cos(rad);

  for(i=0; i<num_verticies; i++){
    rx = cosine*(verticies[i].x - x) - sine*(verticies[i].y - y);
    ry = sine*(verticies[i].x - x) + cosine*(verticies[i].y - y);
    verticies[i].x = rx + x;
    verticies[i].y = ry + y;
  }
  
  bound();
  clear_cache();
  update_sides();
  a = area_cached;
  polar_moment_cached = pm;
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
  for(i=0; i<num_verticies; i++){
    verticies[i].x = factor*(verticies[i].x - x) + x;
    verticies[i].y = factor*(verticies[i].y - y) + y;
  }
  bound();
  clear_cache();
  update_sides();
}


void geom::Polygon::translate(const geom::Point *shift){
  translate(shift->x, shift->y);
}


void geom::Polygon::translate(double x, double y){
  uint32_t i;
  for(i=0; i<num_verticies; i++){
    verticies[i].x += x;
    verticies[i].y += y;
  }

  // translate bounding box
  bbox.bot_left.x += x;
  bbox.top_right.x += x;
  bbox.bot_left.y += y;
  bbox.top_right.y += y;

  update_sides();

  // translate cached center, area is unaffected
  center_cached.x += x;
  center_cached.y += y;
}
