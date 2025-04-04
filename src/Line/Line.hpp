#pragma once
#include <SFML/Graphics.hpp>
#include "../Station/Station.hpp"

class Line {
    public:
        Line(size_t startIndex, size_t endIndex, sf::Color color);
    
        void render(sf::RenderWindow& window, const std::vector<Station>& stations) const;
    
        size_t getStartIndex() const;
        size_t getEndIndex() const;
        sf::Color getColor() const;
    
    private:
        size_t _startIndex;
        size_t _endIndex;
        sf::Color _color;
    };
    