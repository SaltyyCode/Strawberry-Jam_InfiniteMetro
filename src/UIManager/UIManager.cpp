#include "UIManager.hpp"
#include <ctime>
#include <cstdlib>
#include <algorithm>

UIManager::UIManager(int stationCount) {
    std::srand(std::time(nullptr));
    generateInitialStations(stationCount);
}

void UIManager::generateInitialStations(int count)
{
    std::vector<Station::StationColor> usedColors;

    for (int i = 0; i < count; ++i) {
        float x = static_cast<float>(100 + rand() % 1000);
        float y = static_cast<float>(100 + rand() % 500);
        auto type = static_cast<Station::StationType>(rand() % 3);

        Station::StationColor color;

        do {
            color = static_cast<Station::StationColor>(rand() % 6);
        } while (
            usedColors.size() == 1 && std::find(usedColors.begin(), usedColors.end(), color) != usedColors.end()
        );

        if (std::find(usedColors.begin(), usedColors.end(), color) == usedColors.end())
            usedColors.push_back(color);

        _stations.emplace_back(type, sf::Vector2f(x, y), color);
    }
}

void UIManager::render(sf::RenderWindow& window)
{
    for (const auto& station : _stations) {
        station.render(window);
    }
}
