#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Station/Station.hpp"

class UIManager {
public:
    void render(sf::RenderWindow& window, const std::vector<Station>& stations);
};
