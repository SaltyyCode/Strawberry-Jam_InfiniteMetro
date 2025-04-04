#pragma once
#include <SFML/Graphics.hpp>
#include "GameManager/GameManager.hpp"
#include "UIManager/UIManager.hpp"

void handleEvents(sf::RenderWindow& window, GameManager& game, UIManager& ui, bool& isPaused);
