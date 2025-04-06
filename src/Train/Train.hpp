#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Line/Line.hpp"
#include "../Station/Station.hpp"

class Train {
public:
    Train(sf::Color color, sf::Vector2f position, float rotation = 0.f, int maxPassengers = 5);
    void render(sf::RenderWindow& window) const;
    void update(float deltaTime, const std::vector<Station>& stations, const std::vector<Line>& lines);
    sf::FloatRect getGlobalBounds() const;

    static std::vector<Train> createTrain(sf::Color color, sf::Vector2f position, sf::Vector2f direction);
    void recalculatePath();
    std::vector<size_t> getPath() const { return _path; }

private:
    void findPath(const std::vector<Station>& stations, const std::vector<Line>& lines);
    size_t getNextStationIndex() const;

    sf::Color _color;
    sf::RectangleShape _shape;
    int _maxPassengers;
    
    std::vector<size_t> _path;
    size_t _currentPathIndex;
    bool _reversePath;
    float _speed;
    float _progress;
    
    bool _needsPathUpdate;
    int _lastLineCount;
};