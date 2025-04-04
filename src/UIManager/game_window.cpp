#include <SFML/Graphics.hpp>
#include "UIManager.hpp"
#include "menu.hpp"

int game_window()
{ 
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Infinite Metro");
    window.setFramerateLimit(60);

    UIManager uiManager(3);

    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                    window.close();
                }
            }
            window.clear(sf::Color::White);
            uiManager.render(window);
            window.display();
        }
        return 0;
}