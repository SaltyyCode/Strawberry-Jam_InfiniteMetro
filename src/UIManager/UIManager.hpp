#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Station/Station.hpp"
#include "../GameManager/GameManager.hpp"

class UIManager {
public:
    void loadBackground(const std::string& path, const sf::RenderWindow& window);
    void render(sf::RenderWindow& window, const std::vector<Station>& stations, const std::vector<Line>& lines, int selectedLineIndex);

private:
    sf::Texture _bgTexture;
    sf::Sprite _bgSprite;
};
