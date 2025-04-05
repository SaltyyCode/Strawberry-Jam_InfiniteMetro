#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "../Station/Station.hpp"
#include "../Line/Line.hpp"

class GameManager {
public:
    GameManager(int maxStations, float spawnDelay, int startLines, int maxLines);

    const std::vector<Station>& getStations() const;
    const std::vector<Line>& getMetroLines() const;
    int getSelectedLineIndex() const;

    void handleMousePressed(sf::Vector2f mousePos, sf::Vector2u windowSize);
    void handleMouseReleased(sf::Vector2f mousePos);
    void renderLinePreview(sf::RenderWindow& window, sf::Vector2f currentMousePos) const;

    void update();
    void updateStations();

private:
    void spawnStation();
    bool isTooCloseToLine(sf::Vector2f pos) const;
    void selectLineAt(sf::Vector2f pos, sf::Vector2u windowSize);

    std::vector<Station> _stations;
    std::vector<Line> _metroLines;
    std::vector<Station::StationColor> _usedColors;

    Station* _selectedStation = nullptr;
    int _selectedLineIndex = -1;
    bool _isDragging = false;

    int _maxStations;
    float _spawnDelay;
    int _startLines;
    int _maxLines;

    sf::Clock _spawnClock;
};
