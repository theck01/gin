#ifndef GEOM_RECTANGLE_HPP
#define GEOM_RECTANGLE_HPP

#include "../stdlibs.hpp"
#include "../base/Meta.hpp"
#include "../geom/Point.hpp"

namespace geom {
  class Rectangle;
}

class geom::Rectangle: public base::Meta {
  public:
    geom::Point bot_left;
    geom::Point top_right;
};

#endif
