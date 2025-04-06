#pragma once
#include <string>

struct MapConfig {
    std::string name;
    std::string backgroundPath;
    int maxStations;
    int startLines;
    int maxLines;
    float stationSpawnDelay;
};

class GameApp {
public:
    int run(const std::string& mapName);

private:
    bool _isPaused = false;
    bool _isMuted = false;
};
