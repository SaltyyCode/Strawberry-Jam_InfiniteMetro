#include "Station.hpp"

Station::Station(StationType type, sf::Vector2f position, StationColor color)
    : _type(type), _position(position), _color(color), _alpha(0.f) {}

void Station::update()
{
    if (_alpha < 255.f)
        _alpha += 255.f / 60.f;
    if (_alpha > 255.f)
        _alpha = 255.f;
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
    baseColor.a = static_cast<sf::Uint8>(_alpha); // gestion alpha
    shape.setFillColor(baseColor);

    window.draw(shape);
}
