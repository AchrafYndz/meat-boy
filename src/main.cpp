#include "controller/Game.h"
#include <iostream>
#include <system_error>

int main() {
    try {
        Controller::Game game;
        game.run();
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}