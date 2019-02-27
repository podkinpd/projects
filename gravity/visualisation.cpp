#include "Vector.hpp"

#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>

const int particleRadius = 1;
const int t0 = 100;

int main(int argc, char* argv[]) {
    if(argc != 2 )
	return -1;
    std::ifstream in;
    in.open(argv[1]);
    std::size_t n, k;
    in >> n >> k;
    sf::RenderWindow window(sf::VideoMode(1400,800), "visualisation");
    std::vector<sf::CircleShape> shapes(n);
    for(auto it = shapes.begin(); it != shapes.end(); it++) {
	it->setFillColor(sf::Color::Yellow);
	it->setRadius(particleRadius);
    }
    sf::Clock clock;
    Vector r;
    std::vector<std::vector<Vector>> dat(k);
    for(size_t i = 0; i < k; i++ ) {
        dat[i].resize(n);
	for(size_t j = 0; j < n; j++) {
            in >> dat[i][j] >> r;
	    dat[i][j] = dat[i][j] * 1e-9;
	}
    }

    for(size_t i = 0; i < k; i++) {
	clock.restart();
	window.clear();
        for(size_t j = 0; j < n; j++) {
	    sf::Event event;
	    window.pollEvent(event);
	    if(event.type == sf::Event::Closed)
		window.close();
	    shapes[j].setPosition(700+dat[i][j].getX(), 400+dat[i][j].getY());
	    window.draw(shapes[j]);

	}
	std::cout << clock.getElapsedTime().asMilliseconds() <<std::endl;
	while(clock.getElapsedTime().asMilliseconds() < t0) {
		sf::Event event;
	    window.pollEvent(event);
	    if(event.type == sf::Event::Closed)
		    window.close();
	}
	window.display();
    }
    in.close();
    return 0;
}
