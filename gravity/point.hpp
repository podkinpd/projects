#pragma once
#include <math.h>
#include "constants.h"

class Point {
 private:
    double x;
    double y;
    double z;
 public:
    Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    Point(Point& p) {
        x = p.x;
	y = p.y;
	z = p.z;
    }
    Point(const Point&& p) {
        ///
    }
    void Move(double dx, double dy, double dz) {
	x += dx;
	y += dy;
	z += dz;
    }
    Point& operator=(const Point& p) {
	x = p.x;
	y = p.y;
	z = p.z;
	return *this;
    }
    Point&& operator=(Point&& p) {
        ///
    }
    bool operator==(const Point& p) const {
	return Distance(*this, p) < EPS;
    }
    friend double Distance(const Point& p1, const Point& p2) {
        return math.sqrt( (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z) );
    }
};
