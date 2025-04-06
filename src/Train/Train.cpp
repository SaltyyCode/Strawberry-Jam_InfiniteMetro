#include "Train.hpp"
#include <cmath>
#include <functional>
#include <set>
#include <algorithm>
#include <queue>

Train::Train(sf::Color color, sf::Vector2f position, float rotation, int maxPassengers)
    : _color(color), _maxPassengers(maxPassengers), _currentPathIndex(0), 
      _reversePath(false), _speed(100.f), _progress(0.f), _needsPathUpdate(true), _lastLineCount(0)
{
    _shape.setSize(sf::Vector2f(50.f, 30.f));
    _shape.setFillColor(color);
    _shape.setPosition(position);
    _shape.setOrigin(_shape.getSize() / 2.f);
    _shape.setRotation(rotation);
}

void Train::render(sf::RenderWindow& window) const
{
    window.draw(_shape);
}

void Train::recalculatePath()
{
    _needsPathUpdate = true;
}

void Train::update(float deltaTime, const std::vector<Station>& stations, const std::vector<Line>& lines)
{
    bool hasLinesOfOurColor = false;
    int relevantConnectionCount = 0;
    
    for (const auto& line : lines) {
        if (line.getColor() == _color) {
            hasLinesOfOurColor = true;
            relevantConnectionCount += line.getConnections().size();
        }
    }
    
    if (!hasLinesOfOurColor) {
        return;
    }
    
    if (_needsPathUpdate || relevantConnectionCount != _lastLineCount || _path.empty()) {
        findPath(stations, lines);
        _lastLineCount = relevantConnectionCount;
        _needsPathUpdate = false;
    }
    
    if (_path.size() < 2) {
        return;
    }
    
    if (_currentPathIndex >= _path.size()) {
        _currentPathIndex = 0;
    }
    
    size_t currentStationIndex = _path[_currentPathIndex];
    
    size_t nextStationIndex;
    if (_reversePath) {
        nextStationIndex = (_currentPathIndex > 0) ? _path[_currentPathIndex - 1] : _path[0];
    } else {
        nextStationIndex = (_currentPathIndex < _path.size() - 1) ? _path[_currentPathIndex + 1] : _path[_path.size() - 1];
    }
    
    if (currentStationIndex >= stations.size() || nextStationIndex >= stations.size()) {
        return;
    }
    
    sf::Vector2f currentPos = stations[currentStationIndex].getPosition();
    sf::Vector2f nextPos = stations[nextStationIndex].getPosition();
    
    sf::Vector2f direction = nextPos - currentPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    
    if (distance > 0) {
        direction.x /= distance;
        direction.y /= distance;
        
        _progress += (_speed * deltaTime) / distance;
        
        if (_progress >= 1.0f) {
            if (_reversePath) {
                _currentPathIndex--;
                
                if (_currentPathIndex == 0) {
                    _reversePath = false;
                }
            } else {
                _currentPathIndex++;
                
                if (_currentPathIndex >= _path.size() - 1) {
                    _currentPathIndex = _path.size() - 1;
                    _reversePath = true;
                }
            }
            
            _progress = 0.0f;
        }
        
        sf::Vector2f newPos = currentPos + direction * distance * _progress;
        _shape.setPosition(newPos);
        
        float angle = std::atan2(direction.y, direction.x) * 180.f / M_PI;
        _shape.setRotation(angle);
    }
}

std::vector<Train> Train::createTrain(sf::Color color, sf::Vector2f position, sf::Vector2f direction)
{
    std::vector<Train> trains;
    float angle = std::atan2(direction.y, direction.x) * 180.f / M_PI;
    trains.emplace_back(color, position, angle);
    return trains;
}

sf::FloatRect Train::getGlobalBounds() const {
    return _shape.getGlobalBounds();
}

void Train::findPath(const std::vector<Station>& stations, const std::vector<Line>& lines)
{
    std::vector<size_t> oldPath = _path;
    size_t oldCurrentPathIndex = _currentPathIndex;
    bool oldReversePath = _reversePath;
    
    _path.clear();
    
    size_t closestStationIndex = 0;
    float minDistance = std::numeric_limits<float>::max();
    
    for (size_t i = 0; i < stations.size(); i++) {
        float dist = std::hypot(_shape.getPosition().x - stations[i].getPosition().x, 
                              _shape.getPosition().y - stations[i].getPosition().y);
        if (dist < minDistance) {
            minDistance = dist;
            closestStationIndex = i;
        }
    }
    
    std::vector<std::vector<size_t>> graph(stations.size());
    
    for (const auto& line : lines) {
        if (line.getColor() == _color) {
            for (const auto& [a, b] : line.getConnections()) {
                if (a < stations.size() && b < stations.size()) {
                    graph[a].push_back(b);
                    graph[b].push_back(a);
                }
            }
        }
    }
    
    bool isClosestConnected = !graph[closestStationIndex].empty();
    
    if (!isClosestConnected) {
        for (size_t i = 0; i < stations.size(); i++) {
            if (!graph[i].empty()) {
                closestStationIndex = i;
                isClosestConnected = true;
                break;
            }
        }
    }
    
    if (!isClosestConnected) {
        return;
    }
    
    std::vector<size_t> endPoints;
    for (size_t i = 0; i < stations.size(); i++) {
        if (graph[i].size() == 1) {
            endPoints.push_back(i);
        }
    }
    
    if (endPoints.empty()) {
        endPoints.push_back(closestStationIndex);
    }
    
    std::vector<size_t> fullPath;
    std::vector<std::pair<size_t, size_t>> visitedEdges;
    
    std::function<void(size_t, std::vector<size_t>&)> dfs = 
        [&](size_t current, std::vector<size_t>& path) {
            path.push_back(current);
            
            for (size_t next : graph[current]) {
                if (std::find(visitedEdges.begin(), visitedEdges.end(), 
                             std::make_pair(current, next)) == visitedEdges.end() &&
                    std::find(visitedEdges.begin(), visitedEdges.end(), 
                             std::make_pair(next, current)) == visitedEdges.end()) {
                    
                    visitedEdges.push_back(std::make_pair(current, next));
                    
                    dfs(next, path);
                    
                    path.push_back(current);
                }
            }
        };
    
    dfs(endPoints[0], fullPath);
    
    if (fullPath.size() >= 2) {
        _path = fullPath;
        
        size_t closestInPath = 0;
        minDistance = std::numeric_limits<float>::max();
        
        for (size_t i = 0; i < _path.size(); i++) {
            float dist = std::hypot(_shape.getPosition().x - stations[_path[i]].getPosition().x, 
                                   _shape.getPosition().y - stations[_path[i]].getPosition().y);
            if (dist < minDistance) {
                minDistance = dist;
                closestInPath = i;
            }
        }
        
        _currentPathIndex = closestInPath;
        _reversePath = false;
        
        if (_currentPathIndex >= _path.size() - 1) {
            _reversePath = true;
        }
    } else {
        if (oldPath.size() >= 2) {
            _path = oldPath;
            _currentPathIndex = oldCurrentPathIndex;
            _reversePath = oldReversePath;
        }
    }
}

size_t Train::getNextStationIndex() const
{
    if (_path.empty() || _currentPathIndex >= _path.size()) {
        return 0;
    }
    
    if (_reversePath) {
        return (_currentPathIndex > 0) ? _currentPathIndex - 1 : 0;
    } else {
        return (_currentPathIndex < _path.size() - 1) ? _currentPathIndex + 1 : _path.size() - 1;
    }
}