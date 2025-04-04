#include "GameManager.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>

GameManager::GameManager(int maxStations, float spawnDelay)
    : _spawnDelay(spawnDelay), _maxStations(maxStations)
{
    std::srand(std::time(nullptr));
    spawnStation();
    _spawnClock.restart();
}

void GameManager::update()
{
    if (_stations.size() < static_cast<size_t>(_maxStations) &&
        _spawnClock.getElapsedTime().asSeconds() >= _spawnDelay) {
        spawnStation();
        _spawnClock.restart();
    }
}

void GameManager::spawnStation()
{
    float x = static_cast<float>(100 + rand() % 1000);
    float y = static_cast<float>(100 + rand() % 500);
    auto type = static_cast<Station::StationType>(rand() % 3);

    Station::StationColor color;

    do {
        color = static_cast<Station::StationColor>(rand() % 6);
    } while (
        _usedColors.size() == 1 &&
        std::find(_usedColors.begin(), _usedColors.end(), color) != _usedColors.end()
    );

    if (std::find(_usedColors.begin(), _usedColors.end(), color) == _usedColors.end())
        _usedColors.push_back(color);

    _stations.emplace_back(type, sf::Vector2f(x, y), color);
}

const std::vector<Station>& GameManager::getStations() const
{
    return _stations;
}

void GameManager::updateStations()
{
    for (auto& station : _stations)
        station.update();
}
