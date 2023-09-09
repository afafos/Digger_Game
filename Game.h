#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Counter.h"
#include <map>
#include <vector>

// Состояние игры
enum GameState { Play, Win, Fail };

// Основной класс игры
class Game
{
private:
	// Ресурсы игры
	sf::Font font;
	sf::Sprite digger;
	sf::Sprite ground;
	sf::Sprite emerald;
	sf::Sprite gold;
	sf::Sprite goldbag;
	sf::Sprite fireball;
	sf::RectangleShape border;
	// Карта спрайтов для получения их по кодам
	std::map<std::string, sf::Sprite> sprites;
	// Объект игрока
	Player player;
	// Все игровые объекты
	std::vector<GameObject*> objects;
	// Состояние игры
	GameState gamestate;
	// Загрузчик и рисователь спрайтов
	void loadFileTo(sf::Sprite& sprite, const std::string& filename);
	void drawSprite(sf::RenderTarget& target, sf::Sprite& sprite, int x, int y);
	// Карта игры
	Map map;
	// Счетчик для генерации новых врагов
	Counter counter_enemy;
	// Остаток жизней
	int lifecount;
	// Получение объекта по коду
	int getCountTreasures() const;
	int getCountEnemys() const;
	// Вывод текста
	void drawLabelW(sf::RenderTarget& target, const std::wstring& wstr, int x, int y, const sf::Font& font, int size,
		sf::Color color = sf::Color::White);
public:
	Game();
	// Процедура обновления игры
	void Update(sf::RenderWindow& window, float dt);
	// Процедура вывода игры на экран
	void Render(sf::RenderWindow& window);
};

