#pragma once
#include <utility>
#include "Vector.hpp"

class Object {
 public:
    Object() : r_(), v_(), mass_(0) {}
    Object(const Vector& r, const Vector& v, double m) : r_(r), v_(v), mass_(m) {}
    Object(Vector&& r, Vector&& v, double m) : r_(std::move(r)), v_(std::move(v)), mass_(m) {} 
    Object(const Object& o) : r_(o.r_), v_(o.v_), mass_(o.mass_) {}
    Object(Object&& o) : r_(std::move(o.r_)), v_(std::move(o.v_)), mass_(o.mass_) {}
    
    Object& operator=(const Object& o) {
	r_ = o.r_;
        v_ = o.v_;
        mass_ = o.mass_;
	return *this;
    }	
    Object& operator=(Object&& o) {
	r_ = std::move(o.r_);
	v_ = std::move(o.v_);
	mass_ = o.mass_;
	return *this;
    }
    const Vector& getR() const {
        return r_;
    }
    const Vector& getV() const {
	return v_;
    }
    double getMass() const {
	return mass_;
    }
 protected:
    Vector r_;
    Vector v_;
    double mass_;
};
