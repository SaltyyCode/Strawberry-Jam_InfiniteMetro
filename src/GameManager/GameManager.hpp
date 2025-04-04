#pragma once
#include <vector>
#include <SFML/System/Clock.hpp>
#include "../Station/Station.hpp"

class GameManager {
public:
    GameManager(int maxStations = 10, float spawnDelay = 10.f);
    
    void update();
    void spawnStation();
    void updateStations();
    const std::vector<Station>& getStations() const;

private:
    std::vector<Station> _stations;
    std::vector<Station::StationColor> _usedColors;

    sf::Clock _spawnClock;
    float _spawnDelay;
    int _maxStations;
};
