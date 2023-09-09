#pragma once

// Класс счетчика - позволяет отсчитывать заданное время, через вызовы update
class Counter
{
private:
	float left ;
	bool oncereach ;
public:
	Counter();
	// Установка счетчика
	void upset(float interval) ;
	// Обновление счетчика
	void update(float dt) ;
	// Проверка, идет ли еще заданный отсчет
	bool isActive() ;
	// Проверка достижения времени
	bool onceReachNol() ;
	void reset() ;	
};



