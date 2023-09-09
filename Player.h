#pragma once
#include "GameObject.h"
#include "Map.h"
#include "Counter.h"

// Player commands - move and stop
enum Command { cmdNone, cmdLeft, cmdRight, cmdUp, cmdDown, cmdStop };
// Player direction - saved even when stopped, indicating last movement
enum Direction { dirLeft, dirRight, dirUp, dirDown };

// Player class
class Player :
    public GameObject
{
private:
	// Command
	Command cmd;
	// Direction
	Direction lastdir;
	// Shot readiness counter
	Counter fireprepare;
public:
	Player();
	// Constructor with map and objects
	Player(Map* map, std::vector<GameObject*>* objects, int x, int y);
	virtual std::string getSprite() const;
	virtual void Update(float dt);
	// Getting directions
	Direction getDirection() const;
	// Player commands - move, stop and shoot
	void sendLeft();
	void sendRight();
	void sendUp();
	void sendDown();
	void sendStop();
	void tryFire();
};

