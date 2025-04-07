#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Station/Station.hpp"
#include "../Line/Line.hpp"
#include "../Train/Train.hpp"

class UIManager {
public:
    UIManager(); // Default constructor
    UIManager(int stationCount); // New constructor with an argument
    void loadBackground(const std::string& path, const sf::RenderWindow& window, const std::string& cityName);
    bool isClickOnTrainModeButton(sf::Vector2f pos) const;
    void render(sf::RenderWindow& window, const std::vector<Station>& stations, const std::vector<Line>& lines, const std::vector<Train>& trains, int selectedLineIndex, bool isPaused, bool isMuted, bool isTrainMode);
    bool isClickOnMenu(sf::Vector2f pos) const;
    bool isClickOnSettings(sf::Vector2f pos) const;
    bool isClickOnMute(sf::Vector2f pos) const;
    bool isClickOnQuit(sf::Vector2f pos) const;
    void checkKonamiCode(sf::Event event);
    void loadEasterEggImage(const std::string& path);

private:
    sf::Texture _bgTexture;
    sf::Sprite _bgSprite;

    sf::Font _font;
    sf::Text _titleText;

    sf::FloatRect _menuRect = {20.f, 20.f, 30.f, 30.f};
    sf::RectangleShape _trainModeButton;
    sf::FloatRect _settingsRect = {550.f, 150.f, 180.f, 40.f};
    sf::FloatRect _muteRect     = {550.f, 210.f, 180.f, 40.f};
    sf::FloatRect _quitRect     = {550.f, 270.f, 180.f, 40.f};

    std::vector<sf::Keyboard::Key> _konamiCode = {
        sf::Keyboard::Up, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Down,
        sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Left, sf::Keyboard::Right,
        sf::Keyboard::B, sf::Keyboard::A
    };
    std::vector<sf::Keyboard::Key> _inputSequence;
    sf::Texture _easterEggTexture;
    sf::Sprite _easterEggSprite;
    bool _showEasterEgg = false;
};