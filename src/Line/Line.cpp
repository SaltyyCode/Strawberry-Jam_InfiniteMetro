#include "Line.hpp"

Line::Line(size_t startIndex, size_t endIndex, sf::Color color)
    : _startIndex(startIndex), _endIndex(endIndex), _color(color) {}

void Line::render(sf::RenderWindow& window, const std::vector<Station>& stations) const
{
    if (_startIndex >= stations.size() || _endIndex >= stations.size())
        return;

    sf::Vertex line[] = {
        sf::Vertex(stations[_startIndex].getPosition(), _color),
        sf::Vertex(stations[_endIndex].getPosition(), _color)
    };

    window.draw(line, 2, sf::Lines);
}

sf::Color Line::getColor() const
{
    return _color;
}

size_t Line::getStartIndex() const
{
    return _startIndex;
}

size_t Line::getEndIndex() const
{
    return _endIndex;
}
