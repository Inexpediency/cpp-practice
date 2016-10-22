#include "stdafx.h"
#include "../carmodel/Car.h"

BOOST_AUTO_TEST_SUITE(CCar_testing)
	
	BOOST_AUTO_TEST_SUITE(Switch_on)
		BOOST_AUTO_TEST_CASE(Correct_switching)
		{
			CCar testCar;	
			BOOST_CHECK(testCar.TurnEngineOn());
			BOOST_CHECK(testCar.IsEngineOn());
		}
		BOOST_AUTO_TEST_CASE(Incorrect_switching)
		{
			CCar testCar;
			testCar.TurnEngineOn();
			BOOST_CHECK(!testCar.TurnEngineOn());
			BOOST_CHECK(testCar.IsEngineOn());
		}
	BOOST_AUTO_TEST_SUITE_END()
	
	BOOST_AUTO_TEST_SUITE(Switch_off)
		BOOST_AUTO_TEST_CASE(Correct_switching)
		{
			CCar testCar;
			testCar.TurnEngineOn();
			BOOST_CHECK(testCar.TurnEngineOff());
			BOOST_CHECK(!testCar.IsEngineOn());
		}
		BOOST_AUTO_TEST_CASE(Incorrect_switching)
		{
			CCar testCar;
			BOOST_CHECK(!testCar.TurnEngineOff());
			BOOST_CHECK(!testCar.IsEngineOn());
		}
		BOOST_AUTO_TEST_CASE(Turn_off_at_speed)
		{
			CCar testCar;
			testCar.TurnEngineOn();
			testCar.SetGear(GearBox::low);
			testCar.SetSpeed(20);
			BOOST_CHECK(!testCar.TurnEngineOff());
			BOOST_CHECK(testCar.IsEngineOn());
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Set_gear)
		BOOST_AUTO_TEST_CASE(Switch_back_gear)
		{
			CCar testCar;
			testCar.TurnEngineOn();
			BOOST_CHECK(testCar.SetGear(GearBox::reverse));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearBox::reverse));
			
			testCar.SetSpeed(20);
			BOOST_CHECK(!testCar.SetGear(GearBox::low));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearBox::reverse));
			testCar.SetGear(GearBox::neutral);
			BOOST_CHECK(!testCar.SetGear(GearBox::low));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearBox::neutral));
			
			testCar.SetSpeed(0);
			BOOST_CHECK(testCar.SetGear(GearBox::low));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearBox::low));
			//1
			BOOST_CHECK(testCar.SetGear(GearBox::reverse));
			BOOST_CHECK(!testCar.SetGear(GearBox::fourth));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearBox::reverse));
		}
		BOOST_AUTO_TEST_CASE(Switch_other_gear)
		{
			CCar testCar;
			testCar.TurnEngineOn();

			BOOST_CHECK(testCar.SetGear(GearBox::neutral));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearBox::neutral));
			BOOST_CHECK(testCar.SetGear(GearBox::low));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearBox::low));

			testCar.SetSpeed(20);
			BOOST_CHECK(testCar.SetGear(GearBox::neutral));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearBox::neutral));
			BOOST_CHECK(testCar.SetGear(GearBox::second));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearBox::second));

			testCar.SetSpeed(30);
			BOOST_CHECK(testCar.SetGear(GearBox::neutral));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearBox::neutral));
			BOOST_CHECK(testCar.SetGear(GearBox::third));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearBox::third));

			testCar.SetSpeed(40);
			BOOST_CHECK(testCar.SetGear(GearBox::neutral));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearBox::neutral));
			BOOST_CHECK(testCar.SetGear(GearBox::fourth));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearBox::fourth));

			testCar.SetSpeed(50);
			BOOST_CHECK(testCar.SetGear(GearBox::neutral));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearBox::neutral));
			BOOST_CHECK(testCar.SetGear(GearBox::fifth));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearBox::fifth));

		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Set_speed)

		BOOST_AUTO_TEST_CASE(Switch_on_back_gear)
		{
			CCar testCar;
			testCar.TurnEngineOn();
			testCar.SetGear(GearBox::reverse);
			BOOST_CHECK_EQUAL(testCar.GetSpeed(), 0);
			BOOST_CHECK(!testCar.SetSpeed(30));
			BOOST_CHECK(!testCar.SetSpeed(-10));
			BOOST_CHECK(testCar.SetSpeed(20));
			BOOST_CHECK_EQUAL(testCar.GetSpeed(), 20);
		}
		BOOST_AUTO_TEST_CASE(Switch_on_other_gear)
		{
			CCar testCar;
			testCar.TurnEngineOn();
			testCar.SetGear(GearBox::reverse);
			testCar.SetSpeed(20);
			testCar.SetGear(GearBox::neutral);
			BOOST_CHECK(!testCar.SetSpeed(30));
			BOOST_CHECK_EQUAL(testCar.GetSpeed(), 20);
			BOOST_CHECK(testCar.SetSpeed(10));
			BOOST_CHECK_EQUAL(testCar.GetSpeed(), 10);
			BOOST_CHECK(testCar.SetSpeed(0));
			BOOST_CHECK_EQUAL(testCar.GetSpeed(), 0);
			BOOST_CHECK(!testCar.SetSpeed(-1));
			BOOST_CHECK_EQUAL(testCar.GetSpeed(), 0);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()