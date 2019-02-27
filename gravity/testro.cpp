#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <fstream>
#include <time.h> 

#include "star.hpp"

int main() {
    
    std::srand(unsigned(std::time(0)));
    
    std::vector<std::vector<double>> field;
    std::size_t n = 300, m = 400;
    field.resize(n);
    for(std::size_t i = 0; i < n; i++) {
        field[i].resize(m);
        for(std::size_t j = 0; j < m; j++) {
            field[i][j] = std::rand() * 1. / RAND_MAX;
        }
    }
    for(int i = 0; i < 20; i++) {
        std::cout << field[0][i] << ' ';
    }
    std::ofstream ofs;
    ofs.open("./pic.ppm");
    ofs << "P6\n" << n << ' ' << m << "\n255\n";
    for(std::size_t i = 0; i < n; i++) {
        for(std::size_t j = 0; j < m; j++) {
            ofs << char(field[i][j] * 255) << char(50) << char(50);
        }
    }
    ofs.close();
/*
    sf::RenderWindow window(sf::VideoMode(1400,800), "zdfsdzf");
    std::vector<sf::Vertex> wind(n*m);
    for(size_t i = 0; i < n; i++) {
        for(size_t j = 0; j < m; j++) {
            wind[i*m+j].color = sf::Color(std::round(field[i][j]*255), 0, 0);
            wind[i*m+j].position = sf::Vector2f(600+i, 300+j);
            window.draw(wind[i*m+j]);
        }
    }
    window.display();
*/

    return 0;

}
