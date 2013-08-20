#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

#include "../stdlibs.hpp"
#include "../geom/Point.hpp"
#include "../geom/Polygon.hpp"
#include "../physics/Constants.hpp"
#include "../physics/Material.hpp"

namespace physics {
  class Object;
}

class physics::Object: public geom::Polygon {

  protected:
    physics::Material mat;  // Material that the given object is made of

    // initialization function
    void init(const physics::Material *m);

  public:

    // constructors 
    Object(const geom::Point parray[], uint32_t point_count,
           const physics::Material *m);
    Object(const geom::Polygon *p, const physics::Material *m);
    Object(const physics::Object *o);

    // compute the mass of the object
    double mass() const;

    // compute the approximate moment of inertia, either about the polygons
    // center or the point specified.
    double moment_inertia() const; 
    double moment_inertia(const geom::Point *p) const;
};


#endif
