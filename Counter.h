#pragma once

// ����� �������� - ��������� ����������� �������� �����, ����� ������ update
class Counter
{
private:
	float left ;
	bool oncereach ;
public:
	Counter();
	// ��������� ��������
	void upset(float interval) ;
	// ���������� ��������
	void update(float dt) ;
	// ��������, ���� �� ��� �������� ������
	bool isActive() ;
	// �������� ���������� �������
	bool onceReachNol() ;
	void reset() ;	
};



