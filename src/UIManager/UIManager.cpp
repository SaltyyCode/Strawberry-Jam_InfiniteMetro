#include "UIManager.hpp"

void UIManager::render(sf::RenderWindow& window, const std::vector<Station>& stations)
{
    for (const auto& station : stations) {
        station.render(window);
    }
}
