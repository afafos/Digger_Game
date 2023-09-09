#pragma once
#include <string>
#include <vector>

// A forward declaration to protect against circular references
class Map;

// Base class for game objects
class GameObject
{
protected:
	// Position
	float x;
	float y;
	// Speed direction (not speed! there are only -1, 0 and 1)
	int dx;
	int dy;
	// Object deletion mark
	bool isremoved;
	// Link to map - object needs to know its surroundings
	Map * map;
	// Link to all objects - you need to interact with them
	std::vector<GameObject*> * objects;
public:
	// Constructor - with reference to map, objects and starting position
	GameObject(Map * map, std::vector<GameObject*> * objects, int x, int y);
	// Basic constructor
	GameObject();
	// Virtual method for getting object sprite code
	virtual std::string getSprite() const = 0;
	// Next come methods that describe the properties of game objects, on the basis of which they interact with each other
    // is the target treasure to collect
	virtual bool isTreasure() const;
	// Is the enemy
	virtual bool isEnemy() const;
	// Is impassable for the player and monsters
	virtual bool isSolid() const;
	// Can be picked up by monsters and the player
	virtual bool isGrabbable() const;
	// Can be moved by the player
	virtual bool isMovable() const;
	// Checking an object's deletion flag
	bool isRemoved() const;
	// Calling to set the object deletion mark
	void Remove();
	// Getting and setting coordinates
	int getX() const;
	int getY() const;
	void setX(float x);
	void setY(float y);
	// Getting the cell index on the map for the current position of the object (closest)
	int getCellI() const;
	int getCellJ() const;
	// Updating an object
	virtual void Update(float dt);
	// Checking for intersection with another object
	bool isIntersectWith(const GameObject * obj) const;
	const static int SIZE = 50; // Fixed game element size
};

