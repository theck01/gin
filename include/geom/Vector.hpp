#ifndef GEOM_VECTOR_HPP
#define GEOM_VECTOR_HPP

#include "../stdlibs.hpp"
#include "../base/Meta.hpp"
#include "../geom/Point.hpp"

namespace geom {
  class Vector;
}

class geom::Vector: public base::Meta {
  protected:
    geom::Point origin;
    geom::Point unit;
    double size;

    // init method, common to all constructors, angle in radians
    void init(double x0, double y0, double x1, double y1);
    void init(const geom::Point *o, double angle, double mag);

    // ensure that the unit is actually a unit vector, returning the sizing
    // factor
    double unitize();

  public:
    // Constructors, angle in radians
    Vector(const geom::Point *o, const geom::Point *endpoint);
    Vector(double x0, double y0, double x1, double y1);
    Vector(const geom::Point *o, double angle, double mag);
    Vector(const geom::Vector *v);

    // add the given vector to self, as if that vector also originated at the
    // origin of this vector 
    geom::Vector * add(const geom::Vector *v) const;
    void add(const geom::Vector *v, geom::Vector *result) const;

    // return the angle of the vector in radians
    double angle() const;

    // return the angle between this vector and the arguement vector, in
    // radians from the horizon of this vector
    double angle_between(const geom::Vector *v) const;

    // return the cross product with another vector, the magnitude in the
    // z direction, assuming both vectors have the same origin
    double cross(const geom::Vector *v) const;

    // return the dot product with another vector, assuming both vectors
    // have the same origin
    double dot(const geom::Vector *v) const;

    // return the endpoint of the vector
    geom::Point * endpoint() const;
    void endpoint(geom::Point * p) const;

    // return the magnitude of the vector
    double magnitude() const;

    // print the vector to stderr, for debug
    void print() const;

    // return the vector projection of self onto v
    geom::Vector * projection(const geom::Vector *v) const;
    void projection(const geom::Vector *v, geom::Vector *result) const;

    // rotate the vector by rad radians
    void rotate(double rad);

    // scale the vector by the given factor
    void scale(double factor);

    // subtract the given vector from self, as if that vector also
    // originated at the origin of this vector
    geom::Vector * sub(const geom::Vector *v) const;
    void sub(const geom::Vector *v, geom::Vector *result) const;

    // translate the vector by the given point
    void translate(const geom::Point *p);
    void translate(double x, double y);
};

#endif
