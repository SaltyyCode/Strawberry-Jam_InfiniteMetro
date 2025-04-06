#include "menu.hpp"
#include "../GameApp.hpp" // Inclure GameApp pour charger les cartes
#include <iostream>

Menu::Menu() : window(sf::VideoMode(1024, 1024), "Infinite Metro - Menu") {
    if (!font.loadFromFile("assets/font/stocky.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    if (!backgroundTexture.loadFromFile("assets/images/background_im.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);


    // Configure le bouton "Paris"
    parisButton.setFont(font);
    parisButton.setString("Paris");
    parisButton.setCharacterSize(40);
    parisButton.setFillColor(sf::Color::Red); // Change la couleur en jaune
    float parisX = (window.getSize().x - parisButton.getLocalBounds().width) / 2.0f;
    parisButton.setPosition(parisX, 300);

    // Configure le bouton "London"
    londonButton.setFont(font);
    londonButton.setString("London");
    londonButton.setCharacterSize(40);
    londonButton.setFillColor(sf::Color::Red); // Change la couleur en jaune
    float londonX = (window.getSize().x - londonButton.getLocalBounds().width) / 2.0f;
    londonButton.setPosition(londonX, 400);

    // Configure le bouton "New York"
    newYorkButton.setFont(font);
    newYorkButton.setString("New York");
    newYorkButton.setCharacterSize(40);
    newYorkButton.setFillColor(sf::Color::Red); // Change la couleur en jaune
    float newYorkX = (window.getSize().x - newYorkButton.getLocalBounds().width) / 2.0f;
    newYorkButton.setPosition(newYorkX, 500);
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

            // Vérifie si le bouton "Paris" est cliqué
            if (parisButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                window.close(); // Ferme la fenêtre du menu
                loadMap("paris");
            }

            // Vérifie si le bouton "London" est cliqué
            if (londonButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                window.close(); // Ferme la fenêtre du menu
                loadMap("london");
            }

            // Vérifie si le bouton "New York" est cliqué
            if (newYorkButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                window.close(); // Ferme la fenêtre du menu
                loadMap("newyork");
            }
        }
    }
}

void Menu::render() {
    window.clear(sf::Color::Black);
    window.draw(backgroundSprite); // Dessine l'image de fond
    window.draw(parisButton);
    window.draw(londonButton);
    window.draw(newYorkButton);
    window.display();
}

void Menu::loadMap(const std::string& mapName) {
    GameApp gameApp;
    gameApp.run(mapName); // Charge la carte spécifiée
}