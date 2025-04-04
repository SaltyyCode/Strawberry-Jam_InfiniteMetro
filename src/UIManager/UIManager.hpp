#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Station/Station.hpp"
#include "../Line/Line.hpp"

class UIManager {
public:
    void render(sf::RenderWindow& window, const std::vector<Station>& stations);
    void render(sf::RenderWindow& window, const std::vector<Station>& stations, const std::vector<Line>& lines);

};
