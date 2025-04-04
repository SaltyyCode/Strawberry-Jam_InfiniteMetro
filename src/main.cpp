#include <SFML/Graphics.hpp>
#include "UIManager/UIManager.hpp"
#include "UIManager/menu.hpp"

int main()
{
    Menu menu;
    menu.run_menu();

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Infinite Metro");
    window.setFramerateLimit(60);

    UIManager uiManager(3);
    
    return 0;
}
    