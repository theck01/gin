#ifndef GEOM_RECTANGLE_HPP
#define GEOM_RECTANGLE_HPP

#include "../stdlibs.hpp"
#include "../base/Meta.hpp"
#include "Point.hpp"
#include "Line.hpp"

namespace geom {
  class Rectangle;
}

class geom::Rectangle: public base::Meta {
  public:
    geom::Point bot_left;
    geom::Point top_right;

    // returns true if the rectangle contains the given point
    bool contains(const geom::Point *p) const;

    // returns true if the line intersects the perimeter of the rectangle,
    // or is contained completely within the rectangle
    bool intersects(const geom::Line *l) const;

    // returns true if any line in the perimeter of the rectangle and the
    // argument rectangle intersect, or if one of the rectangles is contained
    // completely within the other
    bool intersects(const geom::Rectangle *r) const;

    // convenience set methods for rectangle points
    void set(const geom::Rectangle *r);
    void set(const geom::Point *p, const geom::Point *q);
    void set(double x0, double y0, double x1, double y1);
};

#endif
