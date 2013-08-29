#ifndef GEOM_POLYGON_HPP
#define GEOM_POLYGON_HPP

#include "../stdlibs.hpp"
#include "../base/Meta.hpp"
#include "../geom/Point.hpp"
#include "../geom/Rectangle.hpp"

namespace geom {
  class Polygon;
}

class geom::Polygon: public base::Meta {
  private:
    mutable double area_cached;
    mutable geom::Point center_cached;
    mutable double x_moment_cached;
    mutable double y_moment_cached;
    mutable double polar_moment_cached;

  protected:
    geom::Rectangle bbox;
    geom::Point *verticies;
    geom::Line *sides;
    uint32_t num_verticies;

    // updates the internal bounding box of the polygon
    void bound();

    // sets cached values to impossible states
    void clear_cache();

    // initializes object after creation
    void init(const geom::Point parray[], uint32_t point_count);

    // returns the unsigned area of the polygon
    double signed_area() const;

    // updates the values of the sides in the polygon
    void update_sides();


  public:
    // Constructor, builds polygon from an array of verticies
    Polygon(const geom::Point parray[], uint32_t point_count);

    // Copy Constructor
    Polygon(const geom::Polygon *p);

    // Destructor
    ~Polygon();

    // returns the area captured by the polygon
    double area() const;

    // returns/updates a rectangle to contain the bounding box of the polygon
    geom::Rectangle * bounding_box() const;
    void bounding_box(geom::Rectangle *r) const;

    // returns the center of area for the polygon, or updates the provided
    // point to the center
    geom::Point * center() const;
    void center(geom::Point *p) const;

    // returns true if the Polygon contains the point p (or x, y coordinates)
    bool contains(const geom::Point *p) const;
    bool contains(double x, double y) const;

    // returns true if the polygon and the line intersect, or the polygon
    // contains the line
    bool intersects(const geom::Line *l) const;
    // returns true if the polygon and the rectangle intersect, or the
    // polygon contains the rectangle
    bool intersects(const geom::Rectangle *r) const;
    // returns true if the Polygon and argument Polygon p overlap
    bool intersects(const geom::Polygon *p) const;

    // moment of area about the x and y axis intersecting the centroid of the
    // polygon
    double moment_area_in_x() const;
    double moment_area_in_y() const;

    // moment of area about the polar (z) axis
    double moment_area_polar() const;

    // returns the orientation of the verticies in the polygon, 
    // either positive (counterclockwise, +1) or negative (clockwise, -1)
    int8_t orientation() const;

    // print the polygon to stderr, for debug
    void print() const;

    // rotate about center of area by rad radians
    void rotate(double rad);
    // rotates the polygon about center (or x, y coordinates) by rad radians
    void rotate(const geom::Point *center, double rad);
    void rotate(double x, double y, double rad);

    // scale about the center of area by given factor 
    void scale(double factor);
    // scale about the supplied center by given factor 
    void scale(const geom::Point *center, double factor);
    void scale(double x, double y, double factor);

    // translates the polygon by x and y or value stored in point
    void translate(const geom::Point *shift);
    void translate(double x, double y);
};

#endif
