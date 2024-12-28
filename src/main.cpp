#include <engine/GameEngine.h>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdlib.h>

int main() {

    srand(time(0));

    GameEngine engine;

    engine.run();

    return 0;
}
