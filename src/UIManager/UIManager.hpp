#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Station/Station.hpp"
#include "../Line/Line.hpp"

class UIManager {
public:
    void loadBackground(const std::string& path, const sf::RenderWindow& window, const std::string& cityName);
    void render(sf::RenderWindow& window, const std::vector<Station>& stations, const std::vector<Line>& lines, int selectedLineIndex, bool isPaused, bool isTrainMode);
    bool isClickOnMenu(sf::Vector2f pos) const;
    bool isClickOnTrainModeButton(sf::Vector2f pos) const;

private:
    sf::Texture _bgTexture;
    sf::Sprite _bgSprite;

    sf::Font _font;
    sf::Text _titleText;
    sf::FloatRect _menuRect = {20.f, 20.f, 30.f, 30.f};
    sf::RectangleShape _trainModeButton;
};