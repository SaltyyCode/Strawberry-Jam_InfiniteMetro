#include "UIManager.hpp"
#include <iostream>

UIManager::UIManager() {
}

UIManager::UIManager(int stationCount) {
    (void)stationCount;
}

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

    // Initialize the train mode button
    _trainModeButton.setSize(sf::Vector2f(50.f, 50.f));
    _trainModeButton.setFillColor(sf::Color::Yellow);
    _trainModeButton.setPosition(50.f, 50.f); // Position it appropriately
}

void UIManager::render(sf::RenderWindow& window, const std::vector<Station>& stations, const std::vector<Line>& lines, const std::vector<Train>& trains, int selectedLineIndex, bool isPaused, bool isMuted, bool isTrainMode)
{
    window.draw(_bgSprite);
    window.draw(_titleText);

    for (const auto& line : lines) {
        line.render(window, stations);
    }

    for (const auto& station : stations) {
        station.render(window);
    }

    // Render trains
    for (const auto& train : trains) {
        train.render(window);
    }

    // Render line selectors
    float totalWidth = lines.size() * 60.f;
    float startX = (window.getSize().x - totalWidth) / 2.f;

    for (size_t i = 0; i < lines.size(); ++i) {
        sf::CircleShape circle(20.f);
        circle.setFillColor(lines[i].getColor());
        circle.setPosition(startX + i * 60.f, window.getSize().y - 60.f);
        circle.setOutlineThickness((int)i == selectedLineIndex ? 4.f : 1.f);
        circle.setOutlineColor(sf::Color::Black);
        window.draw(circle);
    }

    // Render menu and buttons
    float x = 20.f, y = 20.f;
    for (int i = 0; i < 3; ++i) {
        sf::RectangleShape bar(sf::Vector2f(30.f, 4.f));
        bar.setPosition(x, y + i * 10.f);
        bar.setFillColor(sf::Color::White);
        window.draw(bar);
    }

    if (isTrainMode) {
        _trainModeButton.setOutlineThickness(4.f);
        _trainModeButton.setOutlineColor(sf::Color::Black);
    } else {
        _trainModeButton.setOutlineThickness(0.f);
    }
    window.draw(_trainModeButton);

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

        auto drawButton = [&](sf::FloatRect rect, const std::string& label) {
            sf::RectangleShape button(sf::Vector2f(rect.width, rect.height));
            button.setPosition(rect.left, rect.top);
            button.setFillColor(sf::Color(100, 100, 100));
            button.setOutlineThickness(2.f);
            button.setOutlineColor(sf::Color::White);
            window.draw(button);

            sf::Text text(label, _font, 20);
            text.setFillColor(sf::Color::White);
            text.setPosition(rect.left + 10.f, rect.top + 5.f);
            window.draw(text);
        };

        drawButton(_settingsRect, "Settings");
        drawButton(_muteRect, isMuted ? "Unmute" : "Mute");
        drawButton(_quitRect, "Quit Game");
    }

    if (_showEasterEgg) {
        window.draw(_easterEggSprite);
    }
}

bool UIManager::isClickOnMenu(sf::Vector2f pos) const {
    return _menuRect.contains(pos);
}

bool UIManager::isClickOnTrainModeButton(sf::Vector2f pos) const {
    return _trainModeButton.getGlobalBounds().contains(pos);
}

bool UIManager::isClickOnSettings(sf::Vector2f pos) const {
    return _settingsRect.contains(pos);
}

bool UIManager::isClickOnMute(sf::Vector2f pos) const {
    return _muteRect.contains(pos);
}

bool UIManager::isClickOnQuit(sf::Vector2f pos) const {
    return _quitRect.contains(pos);
}

void UIManager::checkKonamiCode(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        _inputSequence.push_back(event.key.code);

        if (_inputSequence.size() > _konamiCode.size()) {
            _inputSequence.erase(_inputSequence.begin());
        }

        if (_inputSequence == _konamiCode) {
            _showEasterEgg = true;
        }
    }
}

void UIManager::loadEasterEggImage(const std::string& path) {
    if (!_easterEggTexture.loadFromFile(path)) {
        std::cerr << "Error loading easter egg image: " << path << std::endl;
        return;
    }
    _easterEggSprite.setTexture(_easterEggTexture);
    _easterEggSprite.setPosition(100.f, 100.f);
}