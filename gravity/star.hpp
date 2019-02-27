#include "Object.hpp"
#include "Vector.hpp"

#include <utility>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>

class Star {
 public:
    Star(const Vector& r, const Vector& v, double m, double rad, std::size_t n) : parts_(n), mass_(m), radius_(rad) {
    double dm = m / n;
    std::srand(time(NULL));
    for(std::size_t i = 0; i < n; i++) {
        double x = 2 * rad * (double(std::rand()) / RAND_MAX - 0.5);
	double c = rad * rad - x * x;
	double y = 2 * sqrt(c) * (double(std::rand()) / RAND_MAX - 0.5);
	c -= y * y;
	double z = sqrt(c) * (std::rand() % 2 - 1);
	parts_[i] = Object(Vector(x, y, z) + r, v, dm);
    }   
    }
    Star(const Star& s) : parts_(s.parts_), mass_(s.mass_), radius_(s.radius_) {}
    Star(Star&& s) : parts_(std::move(s.parts_)), mass_(s.mass_), radius_(s.radius_) {}
    const std::vector<Object>& getParts() {
	return parts_;
    }
 protected:
    std::vector<Object> parts_;
    double mass_;
    double radius_;
};

class object {
 public:
    object() {}; 
 protected:
    std::vector<std::vector<double>> parts_;
};
