#include "stdafx.h"
#include "Car.h"

const std::string INFO_COMMAND = "Info";
const std::string ENGIN_ON_COMMAND = "EnginOn";
const std::string ENGIN_OFF_COMMAND = "EnginOff";
const std::string SET_GEAR_COMMAND = "SetGear";
const std::string SET_SPEED_COMMAND = "SetSpeed";
const std::string STOP_COMMAND = "...";

void TurnEngineOn(CCar & car)
{
	if (car.TurnEngineOn())
	{
		std::cout << "Engin on" << std::endl;
	}
	else
	{
		std::cout << "You have no oil or same other problems with that car" << std::endl;
	}
}

void TurnEngineOff(CCar & car)
{
	if (car.TurnEngineOn())
	{
		std::cout << "Engin off" << std::endl;
	}
	else
	{
		std::cout << "Error:: May be you have not zero speed or not neutral gear" << std::endl;
	}
}

void SetGear(CCar & car, std::string gear)
{
	if (!car.IsEngineOn())
	{
		std::cout << "Error: Enfine is off" << std::endl;
		return;
	}
	try
	{
		GearBox newGear = StringToGear(gear);
		if (newGear == GearBox::noGear)
		{
			newGear = static_cast<GearBox>(std::stoi(gear, nullptr, 10));
		}
		if (car.SetGear(newGear))
		{
			std::cout << "Gear changed to " << GearToString(newGear) << std::endl;
		}
		else
		{
			std::cout << "Error:: May be new gear not in speed interval or direction is incoreect" << std::endl;
		}
	}
	catch (...)
	{
		std::cout << "Error: Incorrect gear value" << std::endl;
	}
}

void SetSpeed(CCar & car, std::string speed)
{
	if (!car.IsEngineOn())
	{
		std::cout << "Error: Enfine is off" << std::endl;
		return;
	}
	try
	{
		int newSpeed = std::stoi(speed, nullptr, 10);
		if (car.SetSpeed(newSpeed))
		{
			std::cout << "Speed changed to " << newSpeed << std::endl;
		}
		else
		{
			std::cout << "Error:: May be new speed are not include in speed interval of current gear" << std::endl;
		}
	}
	catch (...)
	{
		std::cout << "Error: Incorrect gear value" << std::endl;
	}
}

int main()
{
	CCar car;
	std::string line;
	while (std::getline(std::cin, line) && (line != STOP_COMMAND))
	{
		if (line == INFO_COMMAND)
		{
			car.PrintInfo(std::cout);
		}
		if (line == ENGIN_ON_COMMAND)
		{
			TurnEngineOn(car);
		}
		if (line == ENGIN_OFF_COMMAND)
		{
			TurnEngineOff(car);
		}
		if (line.find(SET_GEAR_COMMAND) != std::string::npos)
		{
			SetGear(car, line.erase(0, SET_GEAR_COMMAND.length() + 1));
		}
		if (line.find(SET_SPEED_COMMAND) != std::string::npos)
		{
			SetSpeed(car, line.erase(0, SET_SPEED_COMMAND.length() + 1));
		}
	}
	return 0;
}

