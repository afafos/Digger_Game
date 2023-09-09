#pragma once
#include <string>
#include <vector>
#include "GameObject.h"

// Класс карты
class Map
{
private:
	// Размеры
	int w; 
	int h;
	// Массив ячееек
	bool** isfree;
public:
	Map();
	// Загрузка из файла
	void loadFromFile(std::string mapfile, std::vector<GameObject*> & objects);
	// Проверка свободной ячейки
	bool isFree(int i, int j) const;
	// Очистка ячейки
	void clearCell(int i, int j);
	// Размеры
	int getWidth() const;
	int getHeight() const;
};

