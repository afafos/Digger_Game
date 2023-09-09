#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Counter.h"
#include <map>
#include <vector>

// Game state
enum GameState { Play, Win, Fail };

// Main class of the game
class Game
{
private:
	// Game resources
	sf::Font font;
	sf::Sprite digger;
	sf::Sprite ground;
	sf::Sprite emerald;
	sf::Sprite gold;
	sf::Sprite goldbag;
	sf::Sprite fireball;
	sf::RectangleShape border;
	// Sprite map for getting them by codes
	std::map<std::string, sf::Sprite> sprites;
	// Player object
	Player player;
	// All game objects
	std::vector<GameObject*> objects;
	// Game state
	GameState gamestate;
	// Sprite loader and painter
	void loadFileTo(sf::Sprite& sprite, const std::string& filename);
	void drawSprite(sf::RenderTarget& target, sf::Sprite& sprite, int x, int y);
	// Game map
	Map map;
	// Counter for generating new enemies
	Counter counter_enemy;
	// Rest of lives
	int lifecount;
	// Getting an object by code
	int getCountTreasures() const;
	int getCountEnemys() const;
	// Text output
	void drawLabelW(sf::RenderTarget& target, const std::wstring& wstr, int x, int y, const sf::Font& font, int size,
		sf::Color color = sf::Color::White);
public:
	Game();
	// Game update procedure
	void Update(sf::RenderWindow& window, float dt);
	// The procedure for displaying the game on the screen
	void Render(sf::RenderWindow& window);
};

