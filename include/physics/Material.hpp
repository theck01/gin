#ifndef PHYSICS_MATERIAL_HPP
#define PHYSICS_MATERIAL_HPP

#include "../stdlibs.hpp"
#include "../base/Meta.hpp"

namespace physics {
  class Material;
}

class physics::Material: public base::Meta {
  public:
    double density_2D;  // 2D density in kg/(m^2)
    double mu_k;        // kinetic friction coefficient with standard material
    double mu_s;        // static friction coefficient with standard material
    double restitution; // coefficient of restitution with standard material
};

#endif
