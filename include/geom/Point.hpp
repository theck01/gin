#ifndef GEOM_POINT_HPP
#define GEOM_POINT_HPP

#include "../stdlibs.hpp"
#include "../base/Meta.hpp"

namespace geom {
  class Point;
}

class geom::Point: public base::Meta  {
  public:
    double x; // x position in the world
    double y; // y position in the world
};

#endif
