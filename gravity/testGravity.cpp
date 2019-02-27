#include "Object.hpp"
#include "ObjectLine.hpp"
#include "gravity.hpp"
#include "dmotion.hpp"
#include "star.hpp"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <SFML/Graphics.hpp>



int main() {
    std::size_t n = 1000;
    double rad = 7e+8;
    double m1 = 2.0e+30, m2 = 10000000000000., m3 = 10000000000000., m4 = 10000000.;
    Vector r1(0, 0, 0), r2(50000, 40000, 0), r3(40000, 50000, 0), r4(55000, 55000, 0);
    Vector v1(0, 0, 0), v2(-0.5, 0.3, 0), v3(0.5, 0, 0), v4(-0.7, -1, 0);
    ObjectLine o1(r1, v1, m1, 0), o2(r2, v2, m2, 0), o3(r3, v3, m3, 0), o4(r4, v4, m4, 0);
    std::vector<ObjectLine> beg(n);
/*    beg.push_back(o1);
    beg.push_back(o2);
    beg.push_back(o3);
    beg.push_back(o4);
*/ 
       
    Star sol(r1, v1, m1, rad, n); 
    std::vector<Object> oo = sol.getParts();
    for(std::size_t i = 0; i < n; i++) {
        beg[i] = ObjectLine(oo[i], 0);
    }
    sf::RenderWindow window(sf::VideoMode(1400,800), " asefd ");
    std::vector<sf::CircleShape> shapes(n);
    for(std::size_t i = 0; i < n; i++) {
	shapes[i].setFillColor(sf::Color::Yellow);
	shapes[i].setRadius(2);
    }
    /*    shapes[0].setFillColor(sf::Color::Green);
    shapes[0].setRadius(5);
    shapes[1].setFillColor(sf::Color::Red);
    shapes[1].setRadius(5);
    shapes[2].setFillColor(sf::Color::Blue);
    shapes[2].setRadius(5);
    shapes[3].setFillColor(sf::Color::White);
    shapes[3].setRadius(2);
*/
    //    end = dmotion(beg);
    sf::Clock clock;
 //   int t0 = 10;
    for(std::size_t k = 0; window.isOpen() && (k < 1000); k++) {
        clock.restart();
	sf::Event event;
	window.pollEvent(event);
	if( event.type == sf::Event::Closed )
	    window.close();
	window.clear();
	for(std::size_t i = 0; i < n; i++) {
	    shapes[i].setPosition(beg[i].getR().getX()/1e+7 + 700, beg[i].getR().getY()/1e+7 + 400);
            window.draw(shapes[i]);
	}



	beg = dmotion(beg);
//        while(clock.getElapsedTime().asMilliseconds() < t0) {}
        window.display();
    }
//    sf::Event event;
/*    while (window.pollEvent(event)) {
	if (event.type == sf::Event::Closed)
            window.close();
    }
*/
    window.close();
    return 0;
}
