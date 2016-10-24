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
			testCar.SetGear(GearType::low);
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
			BOOST_CHECK(testCar.SetGear(GearType::reverse));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearType::reverse));
			
			testCar.SetSpeed(20);
			BOOST_CHECK(!testCar.SetGear(GearType::low));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearType::reverse));
			BOOST_CHECK(testCar.SetGear(GearType::neutral));
			BOOST_CHECK(!testCar.SetGear(GearType::low));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearType::neutral));
			
			BOOST_CHECK(testCar.SetSpeed(0));
			BOOST_CHECK(testCar.SetGear(GearType::low));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearType::low));

			BOOST_CHECK(testCar.SetGear(GearType::reverse));
			BOOST_CHECK(!testCar.SetGear(GearType::fourth));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearType::reverse));
		}
		BOOST_AUTO_TEST_CASE(Switch_other_gear)
		{
			CCar testCar;
			testCar.TurnEngineOn();

			BOOST_CHECK(testCar.SetGear(GearType::neutral));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearType::neutral));
			BOOST_CHECK(testCar.SetGear(GearType::low));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearType::low));

			testCar.SetSpeed(20);
			BOOST_CHECK(testCar.SetGear(GearType::neutral));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearType::neutral));
			BOOST_CHECK(testCar.SetGear(GearType::second));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearType::second));

			testCar.SetSpeed(30);
			BOOST_CHECK(testCar.SetGear(GearType::neutral));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearType::neutral));
			BOOST_CHECK(testCar.SetGear(GearType::third));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearType::third));

			testCar.SetSpeed(40);
			BOOST_CHECK(testCar.SetGear(GearType::neutral));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearType::neutral));
			BOOST_CHECK(testCar.SetGear(GearType::fourth));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearType::fourth));

			testCar.SetSpeed(50);
			BOOST_CHECK(testCar.SetGear(GearType::neutral));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearType::neutral));
			BOOST_CHECK(testCar.SetGear(GearType::fifth));
			BOOST_CHECK_EQUAL(static_cast<int>(testCar.GetGear()), static_cast<int>(GearType::fifth));

		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Set_speed)

		BOOST_AUTO_TEST_CASE(Switch_on_back_gear)
		{
			CCar testCar;
			testCar.TurnEngineOn();
			testCar.SetGear(GearType::reverse);
			BOOST_CHECK_EQUAL(testCar.GetSpeed(), 0);
			BOOST_CHECK(!testCar.SetSpeed(30));
			BOOST_CHECK(!testCar.SetSpeed(-10));
			BOOST_CHECK(testCar.SetSpeed(20));
			BOOST_CHECK_EQUAL(testCar.GetSpeed(), -20);
		}
		BOOST_AUTO_TEST_CASE(Switch_on_other_gear)
		{
			CCar testCar;
			testCar.TurnEngineOn();
			testCar.SetGear(GearType::reverse);
			testCar.SetSpeed(20);
			testCar.SetGear(GearType::neutral);
			BOOST_CHECK(!testCar.SetSpeed(30));
			BOOST_CHECK_EQUAL(testCar.GetSpeed(), -20);
			BOOST_CHECK(testCar.SetSpeed(10));
			BOOST_CHECK_EQUAL(testCar.GetSpeed(), 10);
			BOOST_CHECK(testCar.SetSpeed(0));
			BOOST_CHECK_EQUAL(testCar.GetSpeed(), 0);
			BOOST_CHECK(!testCar.SetSpeed(-1));
			BOOST_CHECK_EQUAL(testCar.GetSpeed(), 0);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()