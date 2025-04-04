#include "Station.hpp"

Station::Station(StationType type, sf::Vector2f position, StationColor color)
    : _type(type), _color(color), _position(position), _alpha(0.f) {}

void Station::update()
{
    if (_alpha < 255.f) _alpha += 255.f / 60.f;
    if (_alpha > 255.f) _alpha = 255.f;
}

void Station::render(sf::RenderWindow& window) const
{
    sf::CircleShape shape;
    switch (_type) {
        case ROUND: shape.setRadius(20.f); shape.setPointCount(30); break;
        case SQUARE: shape.setRadius(20.f); shape.setPointCount(4); break;
        case TRIANGLE: shape.setRadius(24.f); shape.setPointCount(3); break;
    }

    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(_position);

    sf::Color baseColor = getSFColorFromStationColor(_color);
    baseColor.a = static_cast<sf::Uint8>(_alpha);

    shape.setFillColor(sf::Color(255, 255, 255, 0));
    shape.setOutlineColor(baseColor);                
    shape.setOutlineThickness(4.f);                  

    window.draw(shape);
}

sf::Vector2f Station::getPosition() const 
{
    return _position;
}

Station::StationType Station::getType() const
{
    return _type;
}

Station::StationColor Station::getColor() const
{
    return _color;
}
void Station::setPosition(sf::Vector2f pos)
{
    _position = pos;
}

sf::Color getSFColorFromStationColor(Station::StationColor color)
{
    switch (color) {
        case Station::StationColor::RED: return sf::Color::Red;
        case Station::StationColor::BLUE: return sf::Color::Blue;
        case Station::StationColor::GREEN: return sf::Color::Green;
        case Station::StationColor::YELLOW: return sf::Color::Yellow;
        case Station::StationColor::MAGENTA: return sf::Color::Magenta;
        case Station::StationColor::CYAN: return sf::Color::Cyan;
        default: return sf::Color::White;
    }
}
