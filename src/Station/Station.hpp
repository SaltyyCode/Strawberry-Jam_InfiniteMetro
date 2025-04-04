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
        sf::Vector2f getPosition() const;
        StationColor getColor() const;
        void setPosition(sf::Vector2f pos);
    
    private:
        StationType _type;
        sf::Vector2f _position;
        StationColor _color;
    
        float _alpha; // 0 à 255
    };
    