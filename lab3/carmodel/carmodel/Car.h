#pragma once
#include "stdafx.h"

enum class GearType
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

std::string GearToString(GearType gear);
GearType StringToGear(std::string gear);

class CCar
{
public:
	GearType GetGear() const;
	int GetSpeed() const;
	bool IsEngineOn() const;
	bool TurnEngineOn();
	bool TurnEngineOff();
	bool SetGear(GearType gear);
	bool SetSpeed(int speed);
	void PrintInfo(std::ostream & output) const;
private:
	GearType m_currentGear = GearType::neutral;
	int m_speed = 0;
	bool m_engineOn = false;
};