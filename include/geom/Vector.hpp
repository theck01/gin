#ifndef GEOM_VECTOR_HPP
#define GEOM_VECTOR_HPP

#include "../stdlibs.hpp"
#include "../base/Meta.hpp"
#include "../geom/Point.hpp"

namespace geom {
  class Vector;
}

class geom::Vector: public base::Meta {
  private:
    geom::Point origin;
    geom::Point unit;
    double size;

    // init method, common to all constructors, angle in radians
    void init(double x, double y, double u, double v, double mag);
    void init(double x, double y, double angle, double mag);

    // ensure that the unit is actually a unit vector
    void unitize();

  public:
    // Constructors, angle in radians
    Vector(geom::Point *o, geom::Point *dir, double mag);
    Vector(geom::Point *o, double angle, double mag);
    Vector(double x, double y, double u, double v, double mag);
    Vector(double x, double y, double angle, double mag);
    Vector(geom::Vector *v);

    // return the angle of the vector in radians
    double angle();

    // return the cross product with another vector, the magnitude in the
    // z direction, self x v
    double cross(geom::Vector *v);

    // return the dot product with another vector
    double dot(geom::Vector *v);

    // return the magnitude of the vector
    double magnitude();

    // rotate the vector by rad radians
    void rotate(double rad);

    // scale the vector by the given factor
    void scale(double factor);

    // translate the vector by the given point
    void translate(geom::Point *p);
    void translate(double x, double y);
};

#endif
