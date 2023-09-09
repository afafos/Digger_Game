#pragma once

// Counter class - allows you to count a given time through update calls
class Counter
{
private:
	float left ;
	bool oncereach ;
public:
	Counter();
	// Counter installation
	void upset(float interval) ;
	// Counter update
	void update(float dt) ;
	// Checking whether the specified count is still in progress
	bool isActive() ;
	// Checking the achievement of time
	bool onceReachNol() ;
	void reset() ;	
};



