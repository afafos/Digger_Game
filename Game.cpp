#include "Game.h"
#include "GameObject.h"
#include "Enemy.h"

// ����� ��������� ��� ������ �����
const int LEFT = 0;
const int TOP = 100;
// �������� ��������� ������
const int ENEMY_INTERVAL = 10.0f;
// ������������ ����� ������
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

	// ����� ��������
	border.setSize(sf::Vector2f(800-10, 100-10));
	border.setPosition(5, 5);
	border.setFillColor(sf::Color::Black);
	border.setOutlineThickness(5);
	border.setOutlineColor(sf::Color(128,128,128));

	// �������� ��������
	loadFileTo(digger, "data\\digger.png");
	loadFileTo(ground, "data\\ground.png");
	loadFileTo(emerald, "data\\emerald.png");
	loadFileTo(goldbag, "data\\goldbag.png");
	loadFileTo(gold, "data\\gold.png");
	loadFileTo(fireball, "data\\fireball.png");

	sf::Sprite enemy;
	loadFileTo(enemy, "data\\enemy.png");

	// ���������� ����� �������� �� �����, ��� ������������� � �������
	sprites.insert_or_assign(std::string("digger"), digger);
	sprites.insert_or_assign(std::string("enemy"), enemy);
	sprites.insert_or_assign(std::string("emerald"), emerald);
	sprites.insert_or_assign(std::string("goldbag"), goldbag);
	sprites.insert_or_assign(std::string("gold"), gold);
	sprites.insert_or_assign(std::string("fireball"), fireball);

	// ������ �����
	map.loadFromFile("data\\map1.dat",objects);
	
	// ������ ������
	player = Player(&map, &objects, GameObject::SIZE*map.getWidth() / 2, GameObject::SIZE * (map.getHeight() - 1));
	objects.push_back(&player);

	// ������������� ��������� ���� � ������
	gamestate = Play;
	lifecount = 2;
	// ��������� ������ ����� ����� 1 �������
	counter_enemy.upset(1.0);
}

void Game::Update(sf::RenderWindow& window, float dt)
{
	// � ����� ����� �������
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) window.close();
			// ������� 
			if (event.key.code == sf::Keyboard::Space)
				if (gamestate == Play) player.tryFire();
		}
	}

	// ���� ���� �������, ��������� 
	if (gamestate == Play) {
		// ���� ������� ��������, �� ������� ������
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.sendLeft(); else
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.sendRight(); else
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player.sendUp(); else
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player.sendDown(); else
						// ����� ���������� ������ �� ���������
						player.sendStop();

		
		// �������� ��� �������
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Update(dt);

		// ������� ������� � ������ ��������
		int p = 0;
		while (p < objects.size())
			if (objects[p]->isRemoved())
				objects.erase(objects.begin() + p);
			else
				p++;

		// ��������� �������� ������, ��������� �����, ���� ����� � �� ��������� �����
		counter_enemy.update(dt);
		if (counter_enemy.onceReachNol()) {
			if (getCountEnemys() < MAX_ENEMY_COUNT) {
				Enemy* e = new Enemy(&map, &objects, (map.getWidth() - 1) * GameObject::SIZE, 0 * GameObject::SIZE);
				objects.push_back(e);
			}
			counter_enemy.upset(ENEMY_INTERVAL);
		}

		// ������ �� ���� ��������� �� �����
		if (getCountTreasures() == 0) gamestate = Win;
		// ���� ������ ����� ��� ���������, �� ����� ����� � ���� ����� �����������, �� ����� ����
		if (player.isRemoved()) {
			if (lifecount > 0) {
				lifecount--;
				// �� ���� �����, �� ��������� ������ ������
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
	// ����� �����
	for (int i = 0; i < map.getWidth(); i++)
		for (int j = 0; j < map.getHeight(); j++)
			if (!map.isFree(i, j))
				drawSprite(window,ground,LEFT + GameObject::SIZE * i, TOP + GameObject::SIZE * j);

	// ����� �����
	window.draw(border);

	// ����� ������
	digger.setRotation(0);
	digger.setScale(1, 1);
	digger.setOrigin(0, 0);
	for (int i=0; i<lifecount; i++)
		drawSprite(window, digger, 5 + (GameObject::SIZE + 10) * i, 5);

	// ����� ���� ��������, ����� ������
	for (int i = 0; i < objects.size(); i++)
		if (objects[i]!=&player)
			drawSprite(window, sprites[objects[i]->getSprite()], objects[i]->getX() + LEFT, objects[i]->getY() + TOP);

	// ������ ������� �������� � ������ ��� �����������
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

	// ����� ����� ����
	if (gamestate == Win)
		drawLabelW(window, L"������!", 400, 10, font, 28, sf::Color::Green);
	if (gamestate == Fail)
		drawLabelW(window, L"���������!", 400, 50, font, 28, sf::Color::Red);
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
