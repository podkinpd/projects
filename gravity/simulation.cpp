#include "Vector.hpp"
#include "star.hpp"
#include "Object.hpp"
#include "ObjectLine.hpp"
#include "dmotion.hpp"

#include <fstream>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>


std::string getTime() {
    std::time_t now = std::time(0);
    std::tm *ltm = std::localtime(&now);
    std::string s;
    s += std::to_string(1900 + ltm->tm_year);
    s += '-';
    s += std::to_string(1 + ltm->tm_mon);
    s += '-';
    s += std::to_string(ltm->tm_mday);
    s += '-';
    s += std::to_string(ltm->tm_hour);
    s += '-';
    s += std::to_string(ltm->tm_min);
    s += '-';
    s += std::to_string(ltm->tm_sec);
    return s;
}

int main() {

    std::string filename = "data/output";
    filename += '-';
    filename += getTime();
    std::ofstream fout;
    fout.open(filename.c_str());


    std::size_t n = 20;
    std::size_t k = 20;
    double radius = 7e+5;
    double m = 2e+30;
    double dist = 2e+10;
    Vector r1(0,0,0), r2(dist,0,0), v1(0,100,0), v2(0,-100,0);
    Star sol1(r1,v1,m,radius,n/2), sol2(r2,v2,m,radius,n/2);
    std::vector<ObjectLine> beg(n);
    std::vector<Object> oo1 = sol1.getParts();
    std::vector<Object> oo2 = sol2.getParts();
    for(std::size_t i = 0; i < n/2; i++ ) {
	beg[i] = ObjectLine(oo1[i],0);
    }
    for(std::size_t i = n/2; i < n; i++) {
	beg[i] = ObjectLine(oo2[i-n/2],0);
    }
    fout << n << ' ' << k << '\n';
    for(auto it = beg.begin(); it != beg.end(); it++) {
	fout << it->getR() << it->getV();
    }
    fout << '\n';
    unsigned int start_time = clock();
    #pragma omp parallel for
    for(std::size_t i = 0; i < k; i++) {
        beg = dmotion(beg);
	for(auto it = beg.begin(); it != beg.end(); it++) {
            fout << it->getR() << it->getV();
	}
	fout << '\n';
	std::cout << i << std::endl;
	unsigned int end_time = clock();
	std::cout << end_time - start_time << std::endl;
    }
    
    fout.close();
    return 0;
}
