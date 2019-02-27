#pragma once
#include "Vector.hpp"
#include "constants.hpp"

#include <iostream>
std::size_t fuck = 0;

template <typename Obj>
Vector TerribbleForce( const Obj& o1, const Obj& o2 ) {
    Vector v12 = o2.getR() - o1.getR();
    double dist = v12.getABS();
 //   dist = dist * dist * dist;
    
    fuck++;
    if(dist == 0) {
	std::cout << "div_b_zero_gravity in "<< fuck << ' ' << o1.getR() << o2.getR() << std::endl;
        fuck--;
    }
    
    return v12 * (GravConst*o1.getMass()*o2.getMass()/*/(dist)*/);
}	
