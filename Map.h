#pragma once
#include <string>
#include <vector>
#include "GameObject.h"

// Map class
class Map
{
private:
	// Size
	int w; 
	int h;
	// Cell array
	bool** isfree;
public:
	Map();
	// Loading from file
	void loadFromFile(std::string mapfile, std::vector<GameObject*> & objects);
	// Checking a free cell
	bool isFree(int i, int j) const;
	// Cell cleaning
	void clearCell(int i, int j);
	// Size
	int getWidth() const;
	int getHeight() const;
};

