#include "Line.hpp"
#include "../Station/Station.hpp"
#include <algorithm>

Line::Line(sf::Color color) : _color(color) {}

void Line::addConnection(size_t a, size_t b)
{
    if (!hasConnection(a, b))
        _connections.emplace_back(a, b);
}

bool Line::hasConnection(size_t a, size_t b) const
{
    return std::any_of(_connections.begin(), _connections.end(), [&](const auto& p) {
        return (p.first == a && p.second == b) || (p.first == b && p.second == a);
    });
}

sf::Color Line::getColor() const
{
    return _color;
}

void Line::render(sf::RenderWindow& window, const std::vector<Station>& stations) const
{
    for (auto& [iA, iB] : _connections) {
        if (iA >= stations.size() || iB >= stations.size()) continue;

        sf::Vector2f posA = stations[iA].getPosition();
        sf::Vector2f posB = stations[iB].getPosition();
        sf::Vector2f diff = posB - posA;

        float length = std::hypot(diff.x, diff.y);
        float angle = std::atan2(diff.y, diff.x) * 180.f / 3.14159f;

        sf::RectangleShape line(sf::Vector2f(length, 5.f));
        line.setPosition(posA);
        line.setRotation(angle);
        line.setFillColor(_color);

        window.draw(line);
    }
}


const std::vector<std::pair<size_t, size_t>>& Line::getConnections() const
{
    return _connections;
}

bool Line::canAddConnection(size_t maxStations) const
{
    std::set<size_t> uniqueStations;
    for (auto& [a, b] : _connections) {
        uniqueStations.insert(a);
        uniqueStations.insert(b);
    }
    return uniqueStations.size() < maxStations;
}
