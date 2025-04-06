#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "../Station/Station.hpp"
#include "../Line/Line.hpp"
#include "../Train/Train.hpp"

class GameManager {
public:
    GameManager(int maxStations = 10, float spawnDelay = 10.f, int maxLines = 3, int maxTrains = 3);

    void update();
    void updateStations();
    void updateTrains(float deltaTime);
    void spawnStation();

    const std::vector<Station>& getStations() const;
    const std::vector<Line>& getMetroLines() const;
    int getSelectedLineIndex() const;
    void removeTrains();
    void addTrains();
    void toggleTrainMode();
    bool isTrainMode() const;

    void handleMousePressed(sf::Vector2f mousePos);
    void handleMouseReleased(sf::Vector2f mousePos);
    void renderLinePreview(sf::RenderWindow& window, sf::Vector2f currentMousePos) const;
    void render(sf::RenderWindow& window);

private:
    bool isTooCloseToLine(sf::Vector2f pos) const;
    void recalculateAllTrainPaths();

    std::vector<Station> _stations;
    std::vector<Station::StationColor> _usedColors;
    std::vector<Line> _metroLines;
    std::vector<Train> _trains;

    int _selectedLineIndex = -1;
    Station* _selectedStation = nullptr;
    bool _isDragging = false;
    bool _trainMode = false;

    sf::Clock _spawnClock;
    sf::Clock _deltaClock;
    float _spawnDelay;
    int _maxStations;
    int _maxLines;
    int _maxTrains;
};
