#include "menu.hpp"
#include "game_window.hpp" // Inclure la déclaration de game_window()
#include <iostream>

Menu::Menu() : window(sf::VideoMode(800, 600), "Menu") {
    if (!font.loadFromFile("assets/font/stocky.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    // Configure le bouton "Play"
    playButton.setFont(font);
    playButton.setString("Play");
    playButton.setCharacterSize(50);
    playButton.setFillColor(sf::Color::White);
    playButton.setPosition(300, 250); // Centré dans la fenêtre
}

Menu::~Menu() {}

void Menu::run_menu() {
    while (window.isOpen()) {
        handle_events();
        render();
    }
}

void Menu::handle_events() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::FloatRect playBounds = playButton.getGlobalBounds();

            // Vérifie si le bouton "Play" est cliqué
            if (playBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                window.close(); // Ferme la fenêtre du menu
                game_window();  // Ouvre la fenêtre de jeu
            }
        }
    }
}

void Menu::render() {
    window.clear(sf::Color::Black);
    window.draw(playButton);
    window.display();
}