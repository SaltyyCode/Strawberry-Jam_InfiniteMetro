#include <SFML/Graphics.hpp>
                #include "UIManager.hpp"
                #include "menu.hpp"
                #include <vector>
                #include "../Station/Station.hpp"
                #include "../Line/Line.hpp"
                #include "../Train/Train.hpp"

                int game_window()
                {
                    sf::RenderWindow window(sf::VideoMode(1280, 720), "Infinite Metro");
                    window.setFramerateLimit(60);

                    UIManager uiManager(3);

                    std::vector<Station> stations; // List of stations (empty for now)
                    std::vector<Line> lines;       // List of lines (empty for now)
                    std::vector<Train> trains;     // List of trains (empty for now)
                    int selectedLineIndex = 0;
                    bool isPaused = false;
                    bool isMuted = false;

                    while (window.isOpen()) {
                        sf::Event event;
                        while (window.pollEvent(event)) {
                            if (event.type == sf::Event::Closed ||
                                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                                window.close();
                            }
                        }

                        window.clear(sf::Color::White);
                        uiManager.render(window, stations, lines, trains, selectedLineIndex, isPaused, isMuted, false);
                        window.display();
                    }
                    return 0;
                }