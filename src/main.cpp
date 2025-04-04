#include <SFML/Graphics.hpp>
#include "GameManager/GameManager.hpp"
#include "UIManager/UIManager.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Infinite Metro");
    window.setFramerateLimit(60);

    GameManager game(10, 10.f);
    UIManager ui;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f pos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                game.handleMousePressed(pos);
            }
        
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f pos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                game.handleMouseReleased(pos);
            }
        }

        game.update();
        game.updateStations();
        window.clear(sf::Color::White);
        ui.render(window, game.getStations(), game.getLines());
        sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorld = window.mapPixelToCoords(mousePixel);
        game.renderLinePreview(window, mouseWorld);

        window.display();
    }

    return 0;
}
