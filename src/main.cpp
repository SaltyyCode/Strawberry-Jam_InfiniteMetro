#include <SFML/Graphics.hpp>
#include "UIManager/UIManager.hpp"
#include "UIManager/menu.hpp"
#include <iostream>
#include "GameApp.hpp"

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <map_name>" << std::endl;
        return 1;
    }

    GameApp app;
    return app.run(argv[1]);
}
    