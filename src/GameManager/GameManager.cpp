#include "GameManager.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

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

bool GameManager::isTooCloseToLine(sf::Vector2f pos) const
{
    for (const auto& line : _lines) {
        if (line.getStartIndex() >= _stations.size() || line.getEndIndex() >= _stations.size())
            continue;

        auto a = _stations[line.getStartIndex()].getPosition();
        auto b = _stations[line.getEndIndex()].getPosition();

        sf::Vector2f ab = b - a;
        sf::Vector2f ap = pos - a;

        float abLenSq = ab.x * ab.x + ab.y * ab.y;
        float dot = (ap.x * ab.x + ap.y * ab.y) / abLenSq;

        dot = std::clamp(dot, 0.f, 1.f);
        sf::Vector2f closest = a + dot * ab;
        float dx = closest.x - pos.x;
        float dy = closest.y - pos.y;

        float dist = std::sqrt(dx * dx + dy * dy);
        if (dist < 40.f)
            return true;
    }
    return false;
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


const std::vector<Line>& GameManager::getLines() const
{
    return _lines;
}

void GameManager::handleMousePressed(sf::Vector2f mousePos)
{
    for (auto& station : _stations) {
        float dist = std::hypot(station.getPosition().x - mousePos.x,
                                station.getPosition().y - mousePos.y);
        if (dist < 30.f) {
            _selectedStation = &station;
            break;
        }
    }
}

void GameManager::handleMouseReleased(sf::Vector2f mousePos)
{
    if (_selectedStation == nullptr)
        return;

    for (auto& station : _stations) {
        if (&station == _selectedStation)
            continue;

        float dist = std::hypot(station.getPosition().x - mousePos.x,
                                station.getPosition().y - mousePos.y);
        if (dist < 30.f) {
            addLineBetween(*_selectedStation, station, sf::Color::Black);
            break;
        }
    }

    _selectedStation = nullptr;
}


void GameManager::spawnStation()
{
    sf::Vector2f pos;
    do {
        pos = sf::Vector2f(
            static_cast<float>(100 + rand() % 1000),
            static_cast<float>(100 + rand() % 500)
        );
    } while (isTooCloseToLine(pos));

    auto type = static_cast<Station::StationType>(rand() % 3);
    Station::StationColor color;

    do {
        color = static_cast<Station::StationColor>(rand() % 6);
    } while (_usedColors.size() == 1 &&
             std::find(_usedColors.begin(), _usedColors.end(), color) != _usedColors.end());

    if (std::find(_usedColors.begin(), _usedColors.end(), color) == _usedColors.end())
        _usedColors.push_back(color);

    _stations.emplace_back(type, pos, color);
}

void GameManager::addLineBetween(Station& a, Station& b, sf::Color color)
{
    size_t indexA = std::distance(_stations.begin(), std::find_if(_stations.begin(), _stations.end(),
                            [&](const Station& s) { return &s == &a; }));

    size_t indexB = std::distance(_stations.begin(), std::find_if(_stations.begin(), _stations.end(),
                            [&](const Station& s) { return &s == &b; }));

    if (indexA < _stations.size() && indexB < _stations.size()) {
        _lines.emplace_back(indexA, indexB, color);
    }
}

void GameManager::renderLinePreview(sf::RenderWindow& window, sf::Vector2f currentMousePos) const
{
    if (!_selectedStation)
        return;

    sf::Vertex line[] = {
        sf::Vertex(_selectedStation->getPosition(), sf::Color(0, 0, 0, 128)),
        sf::Vertex(currentMousePos, sf::Color(0, 0, 0, 128))
    };

    window.draw(line, 2, sf::Lines);
}
