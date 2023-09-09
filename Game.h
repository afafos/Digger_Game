#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Counter.h"
#include <map>
#include <vector>

// ��������� ����
enum GameState { Play, Win, Fail };

// �������� ����� ����
class Game
{
private:
	// ������� ����
	sf::Font font;
	sf::Sprite digger;
	sf::Sprite ground;
	sf::Sprite emerald;
	sf::Sprite gold;
	sf::Sprite goldbag;
	sf::Sprite fireball;
	sf::RectangleShape border;
	// ����� �������� ��� ��������� �� �� �����
	std::map<std::string, sf::Sprite> sprites;
	// ������ ������
	Player player;
	// ��� ������� �������
	std::vector<GameObject*> objects;
	// ��������� ����
	GameState gamestate;
	// ��������� � ���������� ��������
	void loadFileTo(sf::Sprite& sprite, const std::string& filename);
	void drawSprite(sf::RenderTarget& target, sf::Sprite& sprite, int x, int y);
	// ����� ����
	Map map;
	// ������� ��� ��������� ����� ������
	Counter counter_enemy;
	// ������� ������
	int lifecount;
	// ��������� ������� �� ����
	int getCountTreasures() const;
	int getCountEnemys() const;
	// ����� ������
	void drawLabelW(sf::RenderTarget& target, const std::wstring& wstr, int x, int y, const sf::Font& font, int size,
		sf::Color color = sf::Color::White);
public:
	Game();
	// ��������� ���������� ����
	void Update(sf::RenderWindow& window, float dt);
	// ��������� ������ ���� �� �����
	void Render(sf::RenderWindow& window);
};

