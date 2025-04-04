#include "UIManager.hpp"

void UIManager::render(sf::RenderWindow& window, const std::vector<Station>& stations)
{
    for (const auto& station : stations) {
        station.render(window);
    }
}

void UIManager::render(sf::RenderWindow& window, const std::vector<Station>& stations, const std::vector<Line>& lines)
{
    for (const auto& line : lines)
        line.render(window, stations);

    for (const auto& station : stations)
        station.render(window);
}
