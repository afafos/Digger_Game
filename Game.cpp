#include "Game.h"
#include "GameObject.h"
#include "Enemy.h"

// Shift coordinates for map display
const int LEFT = 0;
const int TOP = 100;
// Enemy generation interval
const int ENEMY_INTERVAL = 10.0f;
// Maximum number of enemies
const int MAX_ENEMY_COUNT = 7;

int Game::getCountTreasures() const
{
	int cnt = 0;
	for (int i = 0; i < objects.size(); i++)
		if (objects[i]->isTreasure()) cnt++;
	return cnt;
}

int Game::getCountEnemys() const
{
	int cnt = 0;
	for (int i = 0; i < objects.size(); i++)
		if (objects[i]->isEnemy()) cnt++;
	return cnt;
}

Game::Game() {
	font.loadFromFile("data\\Arial.ttf");

	// Frame creation
	border.setSize(sf::Vector2f(800-10, 100-10));
	border.setPosition(5, 5);
	border.setFillColor(sf::Color::Black);
	border.setOutlineThickness(5);
	border.setOutlineColor(sf::Color(128,128,128));

	// Loading resources
	loadFileTo(digger, "data\\digger.png");
	loadFileTo(ground, "data\\ground.png");
	loadFileTo(emerald, "data\\emerald.png");
	loadFileTo(goldbag, "data\\goldbag.png");
	loadFileTo(gold, "data\\gold.png");
	loadFileTo(fireball, "data\\fireball.png");

	sf::Sprite enemy;
	loadFileTo(enemy, "data\\enemy.png");

	// Making a sprite map using codes for use in rendering
	sprites.insert_or_assign(std::string("digger"), digger);
	sprites.insert_or_assign(std::string("enemy"), enemy);
	sprites.insert_or_assign(std::string("emerald"), emerald);
	sprites.insert_or_assign(std::string("goldbag"), goldbag);
	sprites.insert_or_assign(std::string("gold"), gold);
	sprites.insert_or_assign(std::string("fireball"), fireball);

	// Loading the map
	map.loadFromFile("data\\map1.dat",objects);
	
	// Creating a player
	player = Player(&map, &objects, GameObject::SIZE*map.getWidth() / 2, GameObject::SIZE * (map.getHeight() - 1));
	objects.push_back(&player);

	// Initializing game state and lives
	gamestate = Play;
	lifecount = 2;
	// Release a new enemy after 1 second
	counter_enemy.upset(1.0);
}

void Game::Update(sf::RenderWindow& window, float dt)
{
	// Event polling in the loop
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) window.close();
			// Shot
			if (event.key.code == sf::Keyboard::Space)
				if (gamestate == Play) player.tryFire();
		}
	}

	// While the game is active, we control 
	if (gamestate == Play) {
		// If the keys are held, then we move the player
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.sendLeft(); else
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.sendRight(); else
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player.sendUp(); else
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player.sendDown(); else
						// Otherwise we send a request to stop
						player.sendStop();

		
		// Update all objects
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Update(dt);

		// Delete objects with a deletion flag
		int p = 0;
		while (p < objects.size())
			if (objects[p]->isRemoved())
				objects.erase(objects.begin() + p);
			else
				p++;

		// Processing the enemy counter, generating new ones if necessary and not exceeding the number
		counter_enemy.update(dt);
		if (counter_enemy.onceReachNol()) {
			if (getCountEnemys() < MAX_ENEMY_COUNT) {
				Enemy* e = new Enemy(&map, &objects, (map.getWidth() - 1) * GameObject::SIZE, 0 * GameObject::SIZE);
				objects.push_back(e);
			}
			counter_enemy.upset(ENEMY_INTERVAL);
		}

		// Victory by zero emeralds on the map
		if (getCountTreasures() == 0) gamestate = Win;
		// If the player is eaten or crushed, then minus life and if the lives are over, then the game is over
		if (player.isRemoved()) {
			if (lifecount > 0) {
				lifecount--;
				// But if possible, then start the player again
				player = Player(&map, &objects, GameObject::SIZE * map.getWidth() / 2, GameObject::SIZE * (map.getHeight() - 1));
				objects.push_back(&player);
			}
			else
				gamestate = Fail;
		}
	}
}

void Game::Render(sf::RenderWindow& window)
{
	// Map output
	for (int i = 0; i < map.getWidth(); i++)
		for (int j = 0; j < map.getHeight(); j++)
			if (!map.isFree(i, j))
				drawSprite(window,ground,LEFT + GameObject::SIZE * i, TOP + GameObject::SIZE * j);

	// Frame output
	window.draw(border);

	// Output of lives
	digger.setRotation(0);
	digger.setScale(1, 1);
	digger.setOrigin(0, 0);
	for (int i=0; i<lifecount; i++)
		drawSprite(window, digger, 5 + (GameObject::SIZE + 10) * i, 5);

	// Output of all objects except the player
	for (int i = 0; i < objects.size(); i++)
		if (objects[i]!=&player)
			drawSprite(window, sprites[objects[i]->getSprite()], objects[i]->getX() + LEFT, objects[i]->getY() + TOP);

	// We display the player separately, taking into account his direction
	if (player.getDirection() == dirLeft) {
		digger.setRotation(0);
		digger.setScale(-1, 1);
		digger.setOrigin(GameObject::SIZE, 0);
	}
	if (player.getDirection() == dirRight) {
		digger.setRotation(0);
		digger.setScale(1, 1);
		digger.setOrigin(0, 0);
	}
	if (player.getDirection() == dirDown) {
		digger.setRotation(90);
		digger.setScale(1, 1);
		digger.setOrigin(0, GameObject::SIZE);
	}
	if (player.getDirection() == dirUp) {
		digger.setRotation(90);
		digger.setScale(-1, 1);
		digger.setOrigin(GameObject::SIZE, GameObject::SIZE);
	}
	if (!player.isRemoved())
		drawSprite(window, digger, player.getX() + LEFT, player.getY() + TOP);

	// Displaying game tags
	if (gamestate == Win)
		drawLabelW(window, L"Victory!", 400, 10, font, 28, sf::Color::Green);
	if (gamestate == Fail)
		drawLabelW(window, L"Defeat!", 400, 50, font, 28, sf::Color::Red);
}

void Game::loadFileTo(sf::Sprite& sprite, const std::string& filename)
{
	sf::Texture* tex = new sf::Texture();
	tex->loadFromFile(filename);
	sprite.setTexture(*tex);	
}

void Game::drawSprite(sf::RenderTarget& target, sf::Sprite& sprite, int x, int y)
{
	sprite.setPosition(x, y);
	target.draw(sprite);
}

void Game::drawLabelW(sf::RenderTarget& target, const std::wstring& wstr, int x, int y, const sf::Font& font, int size,
	sf::Color color)
{
	sf::Text text(wstr, font, size);
	text.setPosition(x, y);
	text.setFillColor(color);
	target.draw(text);
}
