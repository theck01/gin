#include "../../include/geom/Rectangle.hpp"

bool geom::Rectangle::contains(const geom::Point *p) const{
  if(p->x < bot_left.x || p->y < bot_left.y) return false;
  if(p->x > top_right.x || p->y > top_right.y) return false;
  return true;
}


bool geom::Rectangle::intersects(const geom::Line *l) const{
  geom::Line redge;

  // left edge intersection check
  redge.set(bot_left.x, bot_left.y, bot_left.x, top_right.y);
  if(redge.intersects(l)) return true;

  // top edge intersection check
  redge.set(bot_left.x, top_right.y, top_right.x, top_right.y);
  if(redge.intersects(l)) return true;

  // right edge intersection check
  redge.set(top_right.x, top_right.y, top_right.x, bot_left.y);
  if(redge.intersects(l)) return true;

  // bottom edge intersection check
  redge.set(top_right.x, bot_left.y, bot_left.x, bot_left.y);
  if(redge.intersects(l)) return true;

  // check to see if line is contained within rect
  if(contains(&l->p1)) return true;

  return false;
}


bool geom::Rectangle::intersects(const geom::Rectangle *r) const{
  geom::Line redge;

  // left edge intersection check
  redge.set(bot_left.x, bot_left.y, bot_left.x, top_right.y);
  if(r->intersects(&redge)) return true;

  // top edge intersection check
  redge.set(bot_left.x, top_right.y, top_right.x, top_right.y);
  if(r->intersects(&redge)) return true;

  // right edge intersection check
  redge.set(top_right.x, top_right.y, top_right.x, bot_left.y);
  if(r->intersects(&redge)) return true;

  // bottom edge intersection check
  redge.set(top_right.x, bot_left.y, bot_left.x, bot_left.y);
  if(r->intersects(&redge)) return true;

  // check to see if one rectangle contains the other
  if(r->contains(&bot_left) || contains(&r->bot_left)) return true;

  return false;
}
                                        

void geom::Rectangle::set(const geom::Rectangle *r){
  set(r->bot_left.x, r->bot_left.y, r->top_right.x, r->top_right.y);
}


void geom::Rectangle::set(const geom::Point *p, const geom::Point *q){
  set(p->x, p->y, q->x, q->y);
}


void geom::Rectangle::set(double x0, double y0, double x1, double y1){
  bot_left.x = x0;
  bot_left.y = y0;
  top_right.x = x1;
  top_right.y = y1;
}
