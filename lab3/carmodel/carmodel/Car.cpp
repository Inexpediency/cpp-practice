#include "stdafx.h"
#include "Car.h"

bool IsInRange(int number, int start, int end)
{
	return (start <= number) && (number <= end);
}

bool IsSpeedInGearInterval(GearType gear, int speed)
{
	auto IsSpeedInRange = [=](GearType expectedGear, int minSpeed, int maxSpeed) {
		return IsInRange(speed, minSpeed, maxSpeed) && (gear == expectedGear);
	};

	return (speed >= 0) && ((gear == GearType::neutral) ||
		IsSpeedInRange(GearType::reverse, 0, 20) ||
		(IsInRange(speed,   0,  30) && (gear == GearType::low)) ||
		(IsInRange(speed,  20,  50) && (gear == GearType::second)) ||
		(IsInRange(speed,  30,  60) && (gear == GearType::third)) ||
		(IsInRange(speed,  40,  90) && (gear == GearType::fourth)) ||
		(IsInRange(speed,  50, 150) && (gear == GearType::fifth)));
}

bool CCar::IsEngineOn() const
{
	return m_engineOn;
}

GearType CCar::GetGear() const
{
	return m_currentGear;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

bool CCar::TurnEngineOn()
{
	bool isSuccess = !m_engineOn;
	if (isSuccess)
	{
		m_engineOn = true;
	}
	return isSuccess;
}

bool CCar::TurnEngineOff()
{
	bool isSuccess = m_engineOn && (m_speed == 0) && (m_currentGear == GearType::neutral);
	if (isSuccess)
	{
		m_engineOn = false;
	}
	return isSuccess;
}

bool CCar::SetGear(GearType gear)
{
	bool isSuccess = IsSpeedInGearInterval(gear, abs(m_speed));
	isSuccess = isSuccess && 
		((static_cast<int>(gear) > 0) && (m_speed >= 0) ||
		 (static_cast<int>(gear) < 0) && (m_speed == 0) || (gear == GearType::neutral));
	isSuccess = isSuccess && m_engineOn;
	if (isSuccess)
	{
		m_currentGear = gear;
	}
	return isSuccess;
}

bool CCar::SetSpeed(int speed)
{
	bool isSuccess = IsSpeedInGearInterval(m_currentGear, speed);
	isSuccess = isSuccess && ((m_currentGear == GearType::neutral) && (speed < abs(m_speed)) || (m_currentGear != GearType::neutral));
	isSuccess = isSuccess  && m_engineOn;
	if (isSuccess)
	{
		m_speed = static_cast<int>(m_currentGear) >= 0 ? speed : -speed;
	}
	return isSuccess;
}

std::string GetDirectionString(int speed)
{
	if (speed < 0)
		return "Back";
	else if (speed == 0)
		return "None";
	else return "Forward";
}

std::string GearToString(GearType gear)
{
	if (gear == GearType::reverse)
		return "reverse";
	else if (gear == GearType::neutral)
		return "neutral";
	else if (gear == GearType::low)
		return "low";
	else if (gear == GearType::second)
		return "second";
	else if (gear == GearType::third)
		return "third";
	else if (gear == GearType::fourth)
		return "fourth";
	else if (gear == GearType::fifth)
		return "fifth";
	else return "";
}

GearType StringToGear(std::string gear)
{
	if (gear == "reverse")
		return GearType::reverse;
	else if (gear == "neutral")
		return GearType::neutral;
	else if (gear == "low")
		return GearType::low;
	else if (gear == "second")
		return GearType::second;
	else if (gear == "third")
		return GearType::third;
	else if (gear == "fourth")
		return GearType::fourth;
	else if (gear == "fifth")
		return GearType::fifth;
	else return GearType::noGear;
}

void CCar::PrintInfo(std::ostream & output) const
{
	output << "**** Engine info ****" << std::endl;
	output << "Engine: " << (m_engineOn ? "On" : "Off") << std::endl;
	output << "Direction: " << GetDirectionString(m_speed) << std::endl;
	output << "Gear: " << GearToString(m_currentGear) << std::endl;
	output << "Speed: " << abs(m_speed) << std::endl;
}
