#pragma once
#include <SFML/Graphics.hpp>

class Station {
    public:
        enum StationType { SQUARE, ROUND, TRIANGLE };
        enum class StationColor { RED, BLUE, GREEN, YELLOW, MAGENTA, CYAN };

        Station(StationType type, sf::Vector2f position, StationColor color);
        void update();
        void render(sf::RenderWindow& window) const;
        StationType getType() const;
        StationColor getColor() const;
        sf::Vector2f getPosition() const;
        void setPosition(sf::Vector2f pos);
        bool operator==(const Station& other) const {
            return _position == other._position && _type == other._type && _color == other._color;
        }

    private:
        StationType _type;
        StationColor _color;
        sf::Vector2f _position;
        float _alpha = 0.f;
    };

sf::Color getSFColorFromStationColor(Station::StationColor color);
