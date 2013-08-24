#ifndef GEOM_LINE_HPP
#define GEOM_LINE_HPP

#include "../stdlibs.hpp"
#include "../base/Meta.hpp"
#include "Constants.hpp"
#include "Point.hpp"

namespace geom {
  class Line;
}

class geom::Line: public base::Meta {
  public:
    geom::Point p1;
    geom::Point p2;

    // returns true if the point is on the line, false if not, with
    // margin of error given by GEOM_LINE_ERROR_MARGIN
    bool contains(const geom::Point *p) const;

    // returns true if the two lines intersect
    bool intersects(const geom::Line *l) const;

    // returns the point of intersection (if any) between the new lines
    // If lines do not intersect returns NULL (or false, depending on the
    // method), and argument point is set to (NAN, NAN)
    geom::Point * point_of_intersection(const geom::Line *l) const;
    bool point_of_intersection(const geom::Line *l, geom::Point *p) const;

    // returns the slope of the line
    double slope() const;

    // returns the y intersection of the line, if it were an infinite line
    double y_intersect() const;
};
 
#endif
