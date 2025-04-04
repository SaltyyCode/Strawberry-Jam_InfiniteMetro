#pragma once
#include <SFML/Graphics.hpp>

class Station {
public:
    enum StationType {
        SQUARE,
        ROUND,
        TRIANGLE,
    };

    enum class StationColor {
        RED,
        BLUE,
        GREEN,
        YELLOW,
        MAGENTA,
        CYAN
    };

    Station(StationType type, sf::Vector2f position, StationColor color);

    StationType getType() const;
    sf::Vector2f getPosition() const;
    StationColor getColor() const;

    void setPosition(sf::Vector2f pos);
    void render(sf::RenderWindow& window) const;

private:
    StationType _type;
    sf::Vector2f _position;
    StationColor _color;
};
