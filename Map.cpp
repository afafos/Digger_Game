#include "Map.h"
#include <fstream>
#include <istream>
#include "Emerald.h"
#include "Goldbag.h"
#include "Gold.h"

// Символы из файла
const char SYMB_FREE = '-';
const char SYMB_EMERALD = '*';
const char SYMB_GOLDBAG = '$';
const char SYMB_GOLD = '%';

Map::Map() {
	this->w = 0;
	this->h = 0;
	isfree = NULL;
}

void Map::loadFromFile(std::string mapfile, std::vector<GameObject*>& objects)
{
	// Чтение карты
	std::ifstream stm;
	stm.open(mapfile);

	// Сначала её размеры
	std::string line;
	getline(stm, line);	
	this->w = std::stoi(line);
	getline(stm, line);
	this->h = std::stoi(line);

	// Потом создание матрицы
	isfree = new bool*[w];
	for (int i = 0; i < w; i++) 
		isfree[i] = new bool[h];

	// Потом создаём карту, наполняя объекты и устанавливая ячейки
	for (int j = 0; j < h; j++) {
		getline(stm, line);
		for (int i = 0; i < w; i++) {
			isfree[i][j] = (line[i] == SYMB_FREE) || (line[i] == SYMB_GOLD) || (line[i] == SYMB_GOLDBAG);
			if (line[i] == SYMB_EMERALD) objects.push_back(
				new Emerald(this,&objects,GameObject::SIZE*i, GameObject::SIZE * j));
			if (line[i] == SYMB_GOLDBAG) objects.push_back(
				new GoldBag(this, &objects, GameObject::SIZE * i, GameObject::SIZE * j));
			if (line[i] == SYMB_GOLD) objects.push_back(
				new Gold(this, &objects, GameObject::SIZE * i, GameObject::SIZE * j));
		}
	}
	stm.close();
}

bool Map::isFree(int i, int j) const
{
	// Проверка выхода за границы
	if (i < 0) return false;
	if (j < 0) return false;
	if (i >= w) return false;
	if (j >= h) return false;
	return isfree[i][j];
}

void Map::clearCell(int i, int j)
{
	// Проверка выхода за границы
	if (i < 0) return;
	if (j < 0) return;
	if (i >= w) return;
	if (j >= h) return;
	isfree[i][j] = true;
}

int Map::getWidth() const
{
	return w;
}

int Map::getHeight() const
{
	return h;
}
