#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Station/Station.hpp"

class UIManager {
public:
    UIManager(int stationCount = 3);
    void render(sf::RenderWindow& window);

private:
    void generateInitialStations(int count);

    std::vector<Station> _stations;
};
