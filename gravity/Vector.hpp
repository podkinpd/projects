#pragma once
#include "constants.hpp"
#include <math.h>
#include <utility>

#include <iostream>

class Vector {
 public:
    Vector() : x_(0), y_(0), z_(0), length_(0) {}
    Vector(double x, double y, double z) : x_(x), y_(y), z_(z) {
        countLength();
    }
    Vector(const Vector& v) : x_(v.x_), y_(v.y_), z_(v.z_), length_(v.length_) {}
    Vector(Vector&& v) : x_(v.x_), y_(v.y_), z_(v.z_), length_(v.length_) {}
    
    Vector& operator=(const Vector& v) {
        x_ = v.x_;
	y_ = v.y_;
	z_ = v.z_;
	length_ = v.length_;
	return *this;
    }
    Vector& operator=(Vector&& v) {
        x_ = v.x_;
	y_ = v.y_;
	z_ = v.z_;
	length_ = v.length_;
	return *this;
    }


    Vector operator+(const Vector& v) const {
        return Vector(x_+v.x_, y_+v.y_, z_+v.z_);
    }
/*    Vector operator+(Vector&& v) const {
        return Vector(x+v.x, y+v.y, z+v.z);
    }
 */   
    void operator+=(const Vector& v) {
        x_ += v.x_;
	y_ += v.y_;
	z_ += v.z_;
	countLength();
    }
/*    void operator+=(Vector&& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	countLength();
    }*/


    Vector operator-(const Vector& v) const {
        return Vector(x_-v.x_, y_-v.y_, z_-v.z_);
    }
/*    Vector operator-(Vector&& v) const {
        return Vector(x-v.x, y-v.y, z-v.z);
    }*/
    
    Vector operator*(double a) const {
        return Vector(x_*a, y_*a, z_*a);
    }
    Vector operator/(double a) const {
	return Vector(x_/a, y_/a, z_/a);
    }	

    double getABS() const {
        return length_;
    }
    double getX() const {
	return x_;
    }
    double getY() const {
	return y_;
    }
    double getZ() const {
	return z_;
    }

    friend std::ostream& operator<<(std::ostream& out, const Vector& v) {
	out << v.x_ << ' ' << v.y_ << ' ' << v.z_ << ' ';
	return out;
    }
    friend std::istream& operator>>(std::istream& in, Vector& v) {
	in >> v.x_ >> v.y_ >> v.z_;
	return in;
    }
 private:
    void countLength() {
        length_ = sqrt(x_*x_ + y_*y_ + z_*z_);
	return;
    }
 protected:
    double x_;
    double y_;
    double z_;
    double length_;
};
