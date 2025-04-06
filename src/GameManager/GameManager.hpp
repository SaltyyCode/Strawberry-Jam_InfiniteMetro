#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "../Station/Station.hpp"
#include "../Line/Line.hpp"
#include "../Train/Train.hpp"

class GameManager {
public:
    GameManager(int maxStations, float spawnDelay, int startLines, int maxLines, int maxTrains);
    void updateTrains(float deltaTime);

    const std::vector<Station>& getStations() const;
    const std::vector<Line>& getMetroLines() const;
    int getSelectedLineIndex() const;
    void removeTrains();
    void addTrains();
    void toggleTrainMode();
    bool isTrainMode() const;

    void handleMousePressed(sf::Vector2f mousePos, sf::Vector2u windowSize);
    void handleMouseReleased(sf::Vector2f mousePos);
    void renderLinePreview(sf::RenderWindow& window, sf::Vector2f currentMousePos) const;
    void render(sf::RenderWindow& window);

    void update();
    void updateStations();

private:
    bool isTooCloseToLine(sf::Vector2f pos) const;
    void recalculateAllTrainPaths();
    void spawnStation();
    void selectLineAt(sf::Vector2f pos, sf::Vector2u windowSize);

    std::vector<Station> _stations;
    std::vector<Line> _metroLines;
    std::vector<Train> _trains;
    std::vector<Station::StationColor> _usedColors;

    Station* _selectedStation = nullptr;
    int _selectedLineIndex = -1;
    bool _isDragging = false;
    bool _trainMode = false;

    sf::Clock _deltaClock;
    int _maxStations;
    float _spawnDelay;
    int _startLines;
    int _maxLines;
    int _maxTrains;
    sf::Clock _spawnClock;
};
