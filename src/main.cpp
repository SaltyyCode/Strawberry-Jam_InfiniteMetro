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
        }

        game.update();
        game.updateStations();
        window.clear(sf::Color::White);
        ui.render(window, game.getStations());
        window.display();
    }

    return 0;
}
