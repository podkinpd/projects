#pragma once
#include "Object.hpp"
#include "constants.hpp"
#include "Vector.hpp"

class ObjectLine : public Object {
 public:
    ObjectLine() : Object(), time_(0) {}
    ObjectLine(const ObjectLine& o) : Object(o.r_, o.v_, o.mass_), time_(o.time_) {}
    ObjectLine(ObjectLine&& o) : Object(std::move(o.r_), std::move(o.v_), o.mass_), time_(o.time_) {}
    ObjectLine(const Vector& r, const Vector& v, double mass, double time) : Object(r, v, mass), time_(time) {}
    ObjectLine(const Object& o, double time = 0) : Object(o), time_(time) {}
    ObjectLine& operator=(const ObjectLine& o) {
	r_ = o.r_;
	v_ = o.v_;
	mass_ = o.mass_;
	time_ = o.time_;
	return *this;
    }
    double getTime() const {
        return time_;
    }
    void addDt() {
	time_ += dt;
    }	
 protected:
    double time_;
};
