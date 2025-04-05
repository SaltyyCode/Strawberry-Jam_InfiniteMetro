#include "Events.hpp"

void handleEvents(sf::RenderWindow& window, GameManager& game, UIManager& ui, bool& isPaused, bool& isMuted)
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (!isPaused) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f pos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                game.handleMousePressed(pos);
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f pos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                game.handleMouseReleased(pos);
            }
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f pos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

            if (ui.isClickOnMenu(pos)) {
                isPaused = !isPaused;
            }

            if (isPaused) {
                if (ui.isClickOnSettings(pos)) {
                    // futur menu
                }
                if (ui.isClickOnMute(pos)) {
                    isMuted = !isMuted;
                }
                if (ui.isClickOnQuit(pos)) {
                    window.close();
                }
            }
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && isPaused) {
            isPaused = false;
        }
    }
}
