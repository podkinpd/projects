#pragma once
#include <vector>
#include "point.h"

class GroupOfPoints {
 public:
    GroupOfPoints(const std::vector<Point>& points) : group(points), size(points.size()) {}
    GroupOfPoints(std::vector<Point>&& points) : group(std::move(points)), size(points.size()) {}
    void Move() {} //should be any motion
	    
	
	
	
 private:
    std::vector<Point> group;
    size_t size;
};

//another heir class with it's own motion
//    movement of center and relative movement
//    own center and speeds for each group
