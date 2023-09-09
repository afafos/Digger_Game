#include "Counter.h"

const float NOREACH=-1.0f ;

Counter::Counter()
{
	left=NOREACH ;
	oncereach=false ;
}

void Counter::upset(float interval)
{
	left=interval ;
	oncereach = false ;
}

void Counter::update(float dt)
{
	if (!isActive()) return ;
	left-=dt ;
	if (!isActive()) oncereach=true ;	
}

bool Counter::isActive()
{
	return left>0 ;
}

bool Counter::onceReachNol()
{
	if (oncereach) 
	{
		oncereach=false ;
		return true ;
	}
	return false ;
}

void Counter::reset()
{
	left=NOREACH ;
	oncereach=false ;
}
