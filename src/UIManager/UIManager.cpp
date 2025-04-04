#include "UIManager.hpp"
#include <iostream>

void UIManager::loadBackground(const std::string& path, const sf::RenderWindow& window, const std::string& cityName)
{
    if (!_bgTexture.loadFromFile(path)) {
        std::cerr << "Erreur chargement fond : " << path << std::endl;
        return;
    }

    if (!_font.loadFromFile("assets/fonts/OvercameDemoItalic.ttf")) {
        std::cerr << "Erreur chargement police." << std::endl;
        return;
    }

    _titleText.setFont(_font);
    _titleText.setString("Infinite Metro - " + cityName);
    _titleText.setCharacterSize(24);
    _titleText.setFillColor(sf::Color::White);
    _titleText.setOutlineColor(sf::Color::Black);
    _titleText.setOutlineThickness(1.5f);

    sf::FloatRect bounds = _titleText.getLocalBounds();
    _titleText.setOrigin(bounds.width, 0.f);
    _titleText.setPosition(window.getSize().x - 20.f, 10.f);

    _bgSprite.setTexture(_bgTexture);
    sf::Vector2u texSize = _bgTexture.getSize();
    sf::Vector2u winSize = window.getSize();

    float scaleX = (float)winSize.x / texSize.x;
    float scaleY = (float)winSize.y / texSize.y;
    float scale = std::max(scaleX, scaleY);

    _bgSprite.setScale(scale, scale);
    float offsetX = (winSize.x - texSize.x * scale) / 2.f;
    float offsetY = (winSize.y - texSize.y * scale) / 2.f;
    _bgSprite.setPosition(offsetX, offsetY);
}

void UIManager::render(sf::RenderWindow& window, const std::vector<Station>& stations, const std::vector<Line>& lines, int selectedLineIndex, bool isPaused)
{
    window.draw(_bgSprite);
    window.draw(_titleText);

    for (const auto& line : lines)
        line.render(window, stations);

    for (const auto& station : stations)
        station.render(window);

    for (size_t i = 0; i < lines.size(); ++i) {
        sf::CircleShape circle(20.f);
        circle.setFillColor(lines[i].getColor());
        circle.setPosition(80 + i * 60.f, 680.f);
        circle.setOutlineThickness((int)i == selectedLineIndex ? 4.f : 1.f);
        circle.setOutlineColor(sf::Color::Black);
        window.draw(circle);
    }

    float x = 20.f, y = 20.f;
    for (int i = 0; i < 3; ++i) {
        sf::RectangleShape bar(sf::Vector2f(30.f, 4.f));
        bar.setPosition(x, y + i * 10.f);
        bar.setFillColor(sf::Color::White);
        window.draw(bar);
    }

    if (isPaused) {
        sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(overlay);

        sf::Text pauseText("Pause", _font, 60);
        pauseText.setFillColor(sf::Color::White);
        pauseText.setOutlineColor(sf::Color::Black);
        pauseText.setOutlineThickness(2.f);
        sf::FloatRect tBounds = pauseText.getLocalBounds();
        pauseText.setOrigin(tBounds.width / 2.f, tBounds.height / 2.f);
        pauseText.setPosition(window.getSize().x / 2.f, 80.f);
        window.draw(pauseText);
    }
}

bool UIManager::isClickOnMenu(sf::Vector2f pos) const
{
    return _menuRect.contains(pos);
}
