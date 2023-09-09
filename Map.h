#pragma once
#include <string>
#include <vector>
#include "GameObject.h"

// ����� �����
class Map
{
private:
	// �������
	int w; 
	int h;
	// ������ ������
	bool** isfree;
public:
	Map();
	// �������� �� �����
	void loadFromFile(std::string mapfile, std::vector<GameObject*> & objects);
	// �������� ��������� ������
	bool isFree(int i, int j) const;
	// ������� ������
	void clearCell(int i, int j);
	// �������
	int getWidth() const;
	int getHeight() const;
};

