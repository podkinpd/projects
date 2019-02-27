#pragma once
#include "Vector.hpp"
#include "gravity.hpp"
#include "constants.hpp"

#include <vector>

template <typename Obj>
std::vector<Obj> dmotion(std::vector<Obj>& objects) {
    std::size_t n = objects.size();
    std::vector<Obj> res(n);
    for(std::size_t i = 0; i < n; i++) {
        Vector ai(0,0,0);
        #pragma omp parallel for
	for(std::size_t j = 0; j < n; j++) {
            if(i != j) {
	        ai += TerribbleForce(objects[i], objects[j]) / objects[i].getMass();
	    }
	}

	res[i] = Obj(objects[i].getR() + objects[i].getV()*dt + ai*(0.5*dt*dt), objects[i].getV() + ai*dt, objects[i].getMass(), objects[i].getTime() + dt);
    }
    return res;
}
