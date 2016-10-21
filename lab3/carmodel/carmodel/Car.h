#pragma once
#include "stdafx.h"

enum class GearBox
{
	noGear = -2,
	reverse = -1,
	neutral,
	low,
	second,
	third,
	fourth,
	fifth
};

std::string GearToString(GearBox gear);
GearBox StringToGear(std::string gear);

class CCar
{
public:
	GearBox GetGear();
	int GetSpeed();
	bool IsEngineOn();
	bool TurnEngineOn();
	bool TurnEngineOff();
	bool SetGear(GearBox gear);
	bool SetSpeed(int speed);
	void PrintInfo(std::ostream & output);
private:
	GearBox m_gear = GearBox::neutral;
	int m_speed = 0;
	bool m_enginOn = false;
	int m_direction = false;
};