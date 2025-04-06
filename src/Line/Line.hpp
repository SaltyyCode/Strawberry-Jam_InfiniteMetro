#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <tgmath.h>

class Line {
public:
    Line(sf::Color color);
    void addConnection(size_t a, size_t b);
    bool hasConnection(size_t a, size_t b) const;
    void render(sf::RenderWindow& window, const std::vector<class Station>& stations) const;
    const std::vector<std::pair<size_t, size_t>>& getConnections() const;
    bool canAddConnection(size_t maxStations) const;
    sf::Color getColor() const;

private:
    sf::Color _color;
    std::vector<std::pair<size_t, size_t>> _connections;
};
