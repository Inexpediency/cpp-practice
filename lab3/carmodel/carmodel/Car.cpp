#include "stdafx.h"
#include "Car.h"

bool IsSpeedInGearInterval(GearBox gear, int speed)
{
	return (speed >= 0) && ((gear == GearBox::neutral) ||
		(speed >=  0) && (speed <=  20) && (gear == GearBox::reverse) ||
		(speed >=  0) && (speed <=  30) && (gear ==  GearBox::low) ||
		(speed >= 20) && (speed <=  50) && (gear ==  GearBox::second) ||
		(speed >= 30) && (speed <=  60) && (gear ==  GearBox::third) ||
		(speed >= 40) && (speed <=  90) && (gear ==  GearBox::fourth) ||
		(speed >= 50) && (speed <= 150) && (gear ==  GearBox::fifth));
}

bool CCar::IsEngineOn()
{
	return m_enginOn;
}

GearBox CCar::GetGear()
{
	return m_gear;
}

int CCar::GetSpeed()
{
	return m_speed;
}

bool CCar::TurnEngineOn()
{
	bool isSuccess = !m_enginOn;
	if (isSuccess)
	{
		m_enginOn = true;
	}
	return isSuccess;
}

bool CCar::TurnEngineOff()
{
	bool isSuccess = m_enginOn && (m_speed == 0) && (m_gear == GearBox::neutral);
	if (isSuccess)
	{
		m_enginOn = false;
	}
	return isSuccess;
}

bool CCar::SetGear(GearBox gear)
{
	bool isSuccess = IsSpeedInGearInterval(gear, m_speed);
	isSuccess = isSuccess && 
		((static_cast<int>(gear) > 0) && (m_direction >= 0) ||
		(static_cast<int>(gear) < 0) && (m_direction <= 0) || (gear == GearBox::neutral));
	isSuccess = isSuccess && m_enginOn;
	if (isSuccess)
	{
		m_gear = gear;
	}
	return isSuccess;
}

bool CCar::SetSpeed(int speed)
{
	bool isSuccess = IsSpeedInGearInterval(m_gear, speed);
	isSuccess = isSuccess && ((m_gear == GearBox::neutral) && (speed < m_speed) || (m_gear != GearBox::neutral));
	isSuccess = isSuccess  && m_enginOn;
	if (isSuccess)
	{
		if (speed == 0)
		{
			m_direction = 0;
		}
		else
		{
			m_direction = static_cast<int>(m_gear);
		}
		m_speed = speed;
	}
	return isSuccess;
}

std::string GetDirectionString(int direction)
{
	if (direction == -1)
		return "Back";
	else if (direction == 0)
		return "None";
	else return "Forward";
}

std::string GearToString(GearBox gear)
{
	if (gear == GearBox::reverse)
		return "reverse";
	else if (gear == GearBox::neutral)
		return "neutral";
	else if (gear == GearBox::low)
		return "low";
	else if (gear == GearBox::second)
		return "second";
	else if (gear == GearBox::third)
		return "third";
	else if (gear == GearBox::fourth)
		return "fourth";
	else if (gear == GearBox::fifth)
		return "fifth";
	else return "";
}

GearBox StringToGear(std::string gear)
{
	if (gear == "reverse")
		return GearBox::reverse;
	else if (gear == "neutral")
		return GearBox::neutral;
	else if (gear == "low")
		return GearBox::low;
	else if (gear == "second")
		return GearBox::second;
	else if (gear == "third")
		return GearBox::third;
	else if (gear == "fourth")
		return GearBox::fourth;
	else if (gear == "fifth")
		return GearBox::fifth;
	else return GearBox::noGear;
}

void CCar::PrintInfo(std::ostream & output)
{
	output << "**** Engin info ****" << std::endl;
	output << "Engin: " << (m_enginOn ? "On" : "Off") << std::endl;
	output << "Direction: " << GetDirectionString(m_direction) << std::endl;
	output << "Gear: " << GearToString(m_gear) << std::endl;
	output << "Speed: " << m_speed << std::endl;
}
