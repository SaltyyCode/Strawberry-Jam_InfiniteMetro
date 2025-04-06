#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Station/Station.hpp"
#include "../Line/Line.hpp"

class UIManager {
public:
    UIManager(); // Constructeur par défaut
    UIManager(int stationCount); // Nouveau constructeur avec un argument
    void loadBackground(const std::string& path, const sf::RenderWindow& window, const std::string& cityName);
    void render(sf::RenderWindow& window, const std::vector<Station>& stations, const std::vector<Line>& lines, int selectedLineIndex, bool isPaused, bool isMuted);
    bool isClickOnMenu(sf::Vector2f pos) const;
    bool isClickOnSettings(sf::Vector2f pos) const;
    bool isClickOnMute(sf::Vector2f pos) const;
    bool isClickOnQuit(sf::Vector2f pos) const;

private:
    sf::Texture _bgTexture;
    sf::Sprite _bgSprite;

    sf::Font _font;
    sf::Text _titleText;

    sf::FloatRect _menuRect = {20.f, 20.f, 30.f, 30.f};
    sf::FloatRect _settingsRect = {550.f, 150.f, 180.f, 40.f};
    sf::FloatRect _muteRect     = {550.f, 210.f, 180.f, 40.f};
    sf::FloatRect _quitRect     = {550.f, 270.f, 180.f, 40.f};
};
