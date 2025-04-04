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

        sf::Vertex line[] = {
            sf::Vertex(stations[iA].getPosition(), _color),
            sf::Vertex(stations[iB].getPosition(), _color)
        };
        window.draw(line, 2, sf::Lines);
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
