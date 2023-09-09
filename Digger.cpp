#include <SFML\Graphics.hpp>
#include <SFML\System\Clock.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>
#include "Game.h"

// Connect SFML
#pragma comment (lib, "lib\\sfml-window.lib")
#pragma comment (lib, "lib\\sfml-system.lib")
#pragma comment (lib, "lib\\sfml-graphics.lib")
#pragma comment (lib, "lib\\sfml-main.lib")

int main()
{
    // Creating a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Digger");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    
    srand(time(NULL));
    Game game;
    sf::Clock clock;
    float lasttime = clock.getElapsedTime().asSeconds();
    // Starting the main game loop
    while (window.isOpen()) {
        // Update the game state
        float newtime = clock.getElapsedTime().asSeconds();
        game.Update(window, newtime - lasttime);
        lasttime = newtime;
                        
        // Displaying the game on the screen
        window.clear();
        game.Render(window);
        window.display();
    }
    return 0;
}

