#ifndef GEOM_POLYGON_HPP
#define GEOM_POLYGON_HPP

#include "../stdlibs.hpp"
#include "../base/Meta.hpp"
#include "../geom/Point.hpp"

namespace geom {
  class Polygon;
}

class geom::Polygon: public base::Meta {
  private:
    geom::Point bbox[2];
    geom::Point *points;
    uint32_t num_points;

    // generates/updates internal bounding box of the polygon
    void bound();

    // initializes object after creation
    void init(const geom::Point parray[], uint32_t point_count);

    // returns the unsigned area of the polygon
    double signed_area() const;


  public:
    // Constructor, builds polygon from an array of points
    Polygon(const geom::Point parray[], uint32_t point_count);

    // Copy Constructor
    Polygon(const geom::Polygon *p);

    // Destructor
    ~Polygon();

    // returns the area captured by the polygon
    double area() const;

    // returns the center of area for the polygon, or updates the provided
    // point to the center
    geom::Point * center() const;
    void center(geom::Point *p) const;

    // returns true if the Polygon contains the point p (or x, y coordinates)
    bool contains(const geom::Point *p) const;
    bool contains(double x, double y) const;

    // returns the orientation of the points in the polygon, either positive
    // (counterclockwise, +1) or negative (clockwise, -1)
    int8_t orientation() const;

    // returns true if the Polygon and argument Polygon p overlap
    bool overlaps(const geom::Polygon *p) const;

    // rotates the polygon about center (or x, y coordinates) by rad radians
    void rotate(const geom::Point *center, double rad);
    void rotate(double x, double y, double rad);

    // translates the polygon by x and y
    void translate(double x, double y);
};

#endif
