#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Train {
public:
    Train(sf::Color color, sf::Vector2f position, float rotation = 0.f);
    void render(sf::RenderWindow& window) const;
    
    static std::vector<Train> createTrain(sf::Color color, sf::Vector2f position, sf::Vector2f direction);

private:
    sf::Color _color;
    sf::RectangleShape _shape;
};