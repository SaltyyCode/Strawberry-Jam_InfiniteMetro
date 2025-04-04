#include "UIManager.hpp"
#include <iostream>

void UIManager::loadBackground(const std::string& path, const sf::RenderWindow& window)
{
    if (!_bgTexture.loadFromFile(path)) {
        std::cerr << "Erreur chargement fond : " << path << std::endl;
        return;
    }

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

void UIManager::render(sf::RenderWindow& window, const std::vector<Station>& stations, const std::vector<Line>& lines, int selectedLineIndex) //la longueur de la fonction t'as peur
{
    window.draw(_bgSprite);

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
}
