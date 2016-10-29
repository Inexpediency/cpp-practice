#include "stdafx.h"
#include "Car.h"
#include "Menu.h"

const std::string INFO_COMMAND = "Info";
const std::string ENGIN_ON_COMMAND = "EngineOn";
const std::string ENGIN_OFF_COMMAND = "EngineOff";
const std::string SET_GEAR_COMMAND = "SetGear";
const std::string SET_SPEED_COMMAND = "SetSpeed";
const std::string STOP_COMMAND = "...";

void TurnEngineOn(CCar & car, const std::string & arguments)
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

void TurnEngineOff(CCar & car, const std::string & arguments)
{
	if (car.TurnEngineOff())
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
		std::cout << "Error: Engine is off" << std::endl;
		return;
	}
	try
	{
		GearType newGear = StringToGear(gear);
		if (newGear == GearType::noGear)
		{
			newGear = static_cast<GearType>(std::stoi(gear, nullptr, 10));
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
		std::cout << "Error: Engine is off" << std::endl;
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
			if (car.GetGear() == GearType::neutral)
			{
				std::cout << "Error:: Can not set bigger speed then current on neutral gear" << std::endl;
			}
			else
			{
				std::cout << "Error:: May be new speed are not include in speed interval of current gear" << std::endl;
			}
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
	CCarMenu menu;
	menu.AddItem("Help", "Give information about command", [&menu](CCar &, const std::string &)
	{
		menu.ShowInstructions();
	});
	menu.AddItem("...", "Exit from programm", [&menu](CCar &, const std::string &) 
	{
		menu.Exit();
	});
	menu.AddItem("Info", "Show car state", [&car](CCar &, const std::string &)
	{
		car.PrintInfo(std::cout);
	});
	menu.AddItem("EngineOn", "Turn engin on", TurnEngineOn);
	menu.AddItem("EngineOff", "Turn engin off", TurnEngineOff);
	menu.AddItem("SetGear", "Set gear value\n	-1/reverse,\n	0/neutral,\n	1/low,\n	2/second,\n	3/third,\n	4/fourth,\n	5/fifth", SetGear);
	menu.AddItem("SetSpeed", "Set speed value\n	reverse(0, 20),\n	neutral(only for lower value),\n	low(0, 30),\n	second(20, 50),\n	third(30, 60),\n	fourth(40, 90),\n	fifth(50, 150)", SetSpeed);
	menu.Run(car);
	return 0;
}

