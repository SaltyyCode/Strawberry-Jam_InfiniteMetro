#include "Train.hpp"
#include <cmath>

Train::Train(sf::Color color, sf::Vector2f position, float rotation)
    : _color(color)
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

std::vector<Train> Train::createTrain(sf::Color color, sf::Vector2f position, sf::Vector2f direction)
{
    std::vector<Train> trains;
    float angle = std::atan2(direction.y, direction.x) * 180.f / M_PI;
    trains.emplace_back(color, position, angle);
    return trains;
}