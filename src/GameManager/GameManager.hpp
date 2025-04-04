#pragma once
#include <vector>
#include <SFML/System/Clock.hpp>
#include "../Station/Station.hpp"
#include "../Line/Line.hpp"

class GameManager {
public:
    GameManager(int maxStations = 10, float spawnDelay = 10.f);

    void update();
    void spawnStation();
    void updateStations();
    const std::vector<Station>& getStations() const;
    void addLineBetween(Station& a, Station& b, sf::Color color);
    const std::vector<Line>& getLines() const;
    void handleMousePressed(sf::Vector2f mousePos);
    void handleMouseReleased(sf::Vector2f mousePos);
    void renderLinePreview(sf::RenderWindow& window, sf::Vector2f currentMousePos) const;


private:
    std::vector<Station> _stations;
    std::vector<Station::StationColor> _usedColors;
    std::vector<Line> _lines;
    Station* _selectedStation = nullptr;

    sf::Clock _spawnClock;
    float _spawnDelay;
    int _maxStations;

    bool isTooCloseToLine(sf::Vector2f pos) const;
};
