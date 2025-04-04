#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu();
    ~Menu();
    void run_menu();

private:
    void handle_events();
    void render();

    sf::RenderWindow window;
    sf::Font font;
    sf::Text playButton;
};

#endif // MENU_HPP