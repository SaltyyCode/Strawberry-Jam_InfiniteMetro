#include "GameManager.hpp"

static const std::vector<sf::Color> LINE_COLORS = {
    sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Magenta, sf::Color::Cyan
};

GameManager::GameManager(int maxStations, float spawnDelay, int maxLines, int maxTrains)
    : _spawnDelay(spawnDelay), _maxStations(maxStations), _maxLines(maxLines), _maxTrains(maxTrains)
{
    std::srand(std::time(nullptr));
    spawnStation();
    _spawnClock.restart();

    for (int i = 0; i < maxLines && i < (int)LINE_COLORS.size(); ++i)
        _metroLines.emplace_back(LINE_COLORS[i]);
}

const std::vector<Station>& GameManager::getStations() const
{
    return _stations;
}

void GameManager::removeTrains()
{
    if (_maxTrains <= 0)
        return;
    _maxTrains -= 1;
}

void GameManager::addTrains() {
    if (_maxTrains >= 3)
        return;
    _maxTrains += 1;
}

const std::vector<Line>& GameManager::getMetroLines() const
{
    return _metroLines;
}

int GameManager::getSelectedLineIndex() const
{
    return _selectedLineIndex;
}

void GameManager::toggleTrainMode()
{
    _trainMode = !_trainMode;
}

bool GameManager::isTrainMode() const
{
    return _trainMode;
}

void GameManager::handleMousePressed(sf::Vector2f mousePos)
{
    if (_trainMode) {
        for (auto it = _trains.begin(); it != _trains.end(); ++it) {
            sf::FloatRect trainBounds = it->getGlobalBounds();
            if (trainBounds.contains(mousePos)) {
                _trains.erase(it);
                addTrains();
                return;
            }
        }
        return;
    }

    bool clickedOnLineSelector = false;
    for (int i = 0; i < (int)_metroLines.size(); ++i) {
        float cx = 100 + i * 60.f;
        float cy = 700.f;

        float dist = std::hypot(mousePos.x - cx, mousePos.y - cy);
        if (dist < 20.f) {
            _selectedLineIndex = i;
            clickedOnLineSelector = true;
            break;
        }
    }

    if (!clickedOnLineSelector) {
        bool clickedOnLine = false;
        for (size_t lineIdx = 0; lineIdx < _metroLines.size(); ++lineIdx) {
            const auto& line = _metroLines[lineIdx];

            for (const auto& [iA, iB] : line.getConnections()) {
                if (iA >= _stations.size() || iB >= _stations.size()) continue;

                auto a = _stations[iA].getPosition();
                auto b = _stations[iB].getPosition();

                sf::Vector2f ab = b - a;
                sf::Vector2f ap = mousePos - a;

                float abLenSq = ab.x * ab.x + ab.y * ab.y;
                if (abLenSq == 0) continue;

                float dot = (ap.x * ab.x + ap.y * ab.y) / abLenSq;

                dot = std::clamp(dot, 0.f, 1.f);
                sf::Vector2f closest = a + dot * ab;
                float dx = closest.x - mousePos.x;
                float dy = closest.y - mousePos.y;

                float dist = std::sqrt(dx * dx + dy * dy);
                if (dist < 10.f) {
                    if (_trains.size() < static_cast<size_t>(_maxTrains)) {
                        sf::Vector2f direction = b - a;
                        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                        if (length > 0) {
                            direction /= length;
                        }
                        sf::Vector2f trainPosition = closest;

                        auto newTrains = Train::createTrain(line.getColor(), trainPosition, direction);
                        _trains.insert(_trains.end(), newTrains.begin(), newTrains.end());
                    }
                    clickedOnLine = true;
                    break;
                }
            }

            if (clickedOnLine) break;
        }
        if (!clickedOnLine && _selectedLineIndex != -1) {
            for (auto& station : _stations) {
                float dist = std::hypot(station.getPosition().x - mousePos.x,
                                        station.getPosition().y - mousePos.y);
                if (dist < 30.f) {
                    _selectedStation = &station;
                    _isDragging = true;
                    break;
                }
            }
        }
    }
}

void GameManager::handleMouseReleased(sf::Vector2f mousePos)
{
    if (!_selectedStation || _selectedLineIndex == -1)
        return;

    auto& line = _metroLines[_selectedLineIndex];

    for (auto& station : _stations) {
        if (&station == _selectedStation)
            continue;

        float dist = std::hypot(station.getPosition().x - mousePos.x,
                                station.getPosition().y - mousePos.y);
        if (dist < 30.f) {
            size_t iA = std::distance(_stations.begin(), std::find(_stations.begin(), _stations.end(), *_selectedStation));
            size_t iB = std::distance(_stations.begin(), std::find(_stations.begin(), _stations.end(), station));

            if (!line.hasConnection(iA, iB) && line.canAddConnection(4)) {
                line.addConnection(iA, iB);
            }
            break;
        }
    }

    _selectedStation = nullptr;
    _isDragging = false;
}

void GameManager::renderLinePreview(sf::RenderWindow& window, sf::Vector2f currentMousePos) const
{
    if (!_selectedStation || !_isDragging || _selectedLineIndex == -1)
        return;

    sf::Color color = _metroLines[_selectedLineIndex].getColor();
    color.a = 128;

    sf::Vertex line[] = {
        sf::Vertex(_selectedStation->getPosition(), color),
        sf::Vertex(currentMousePos, color)
    };

    window.draw(line, 2, sf::Lines);
}

void GameManager::update()
{
    if (_stations.size() < static_cast<size_t>(_maxStations) &&
        _spawnClock.getElapsedTime().asSeconds() >= _spawnDelay) {
        spawnStation();
        _spawnClock.restart();
    }
}

void GameManager::updateStations()
{
    for (auto& station : _stations)
        station.update();
}

void GameManager::spawnStation()
{
    sf::Vector2f pos;

    do {
        pos = sf::Vector2f(100 + rand() % 1000, 100 + rand() % 500);
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

bool GameManager::isTooCloseToLine(sf::Vector2f pos) const
{
    for (const auto& line : _metroLines) {
        for (const auto& [iA, iB] : line.getConnections()) {
            auto a = _stations[iA].getPosition();
            auto b = _stations[iB].getPosition();

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
    }
    return false;
}

void GameManager::render(sf::RenderWindow& window)
{
    for (const auto& train : _trains) {
        train.render(window);
    }
}