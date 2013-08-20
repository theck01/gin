#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

#include "../stdlibs.hpp"
#include "../geom/Vector.hpp"

namespace physics {
  class Force;
}

class physics::Force: public geom::Vector {}

#endif
