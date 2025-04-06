#include "GameManager.hpp"


static const std::vector<sf::Color> LINE_COLORS = {
    sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Magenta, sf::Color::Cyan, sf::Color::Yellow, sf::Color(255, 165, 0), sf::Color(128, 0, 128)
};

GameManager::GameManager(int maxStations, float spawnDelay, int startLines, int maxLines)
    : _maxStations(maxStations), _spawnDelay(spawnDelay),  _startLines(startLines), _maxLines(maxLines)
{
    std::srand(std::time(nullptr));
    spawnStation();
    _spawnClock.restart();

    for (int i = 0; i < _startLines && i < (int)LINE_COLORS.size(); ++i)
        _metroLines.emplace_back(LINE_COLORS[i]);
}

const std::vector<Station>& GameManager::getStations() const
{
    return _stations;
}

const std::vector<Line>& GameManager::getMetroLines() const
{
    return _metroLines;
}

int GameManager::getSelectedLineIndex() const
{
    return _selectedLineIndex;
}

void GameManager::handleMousePressed(sf::Vector2f mousePos, sf::Vector2u windowSize)
{
    selectLineAt(mousePos, windowSize);

    if (_selectedLineIndex == -1)
        return;

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

void GameManager::selectLineAt(sf::Vector2f pos, sf::Vector2u windowSize)
{
    float totalWidth = _metroLines.size() * 60.f;
    float startX = (windowSize.x - totalWidth) / 2.f;
    float y = windowSize.y - 60.f;

    for (int i = 0; i < (int)_metroLines.size(); ++i) {
        float cx = startX + i * 60.f + 20.f;
        float cy = y + 20.f;

        float dist = std::hypot(pos.x - cx, pos.y - cy);
        if (dist < 20.f) {
            _selectedLineIndex = i;
            break;
        }
    }
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

    int expectedLines = _startLines + static_cast<int>(_stations.size()) / 3;
    expectedLines = std::min(expectedLines, _maxLines);

    if ((int)_metroLines.size() < expectedLines && (int)_metroLines.size() < (int)LINE_COLORS.size()) {
        _metroLines.emplace_back(LINE_COLORS[_metroLines.size()]);
    
    }
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
