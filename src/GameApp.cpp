#include "GameApp.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include "GameManager/GameManager.hpp"
#include "UIManager/UIManager.hpp"

struct MapConfig {
    std::string name;
    std::string backgroundPath;
    int maxStations;
    int maxLines;
    float stationSpawnDelay;
};

int GameApp::run(const std::string& mapName)
{
    std::map<std::string, MapConfig> mapConfigs = {
        {"paris",    {"Paris",    "assets/maps/paris.png",    10, 3, 10.f}},
        {"london",   {"London",   "assets/maps/london.png",   15, 4, 7.f}},
        {"newyork",  {"New York", "assets/maps/newyork.png",  20, 5, 5.f}},
    };

    if (!mapConfigs.count(mapName)) {
        std::cerr << "Map not found: " << mapName << std::endl;
        return 1;
    }

    const MapConfig& config = mapConfigs[mapName];

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Infinite Metro - " + config.name);
    window.setFramerateLimit(60);

    GameManager game(config.maxStations, config.stationSpawnDelay, config.maxLines);
    UIManager ui;
    ui.loadBackground(config.backgroundPath, window);

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

        window.clear(sf::Color::Black);
        ui.render(window, game.getStations(), game.getMetroLines(), game.getSelectedLineIndex());
        window.display();
    }

    return 0;
}
