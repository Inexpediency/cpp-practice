#include "stdafx.h"
#include "../carmodel/Car.h"

void ExpectOperationFailure(CCar car, const std::function<bool(CCar & car)> & operation)
{
	CCar clone(car);
	BOOST_CHECK(!operation(clone));
	BOOST_CHECK_EQUAL(clone.IsEngineOn(), car.IsEngineOn());
	BOOST_CHECK(clone.GetGear() == car.GetGear());
	BOOST_CHECK_EQUAL(clone.GetSpeed(), car.GetSpeed());
}

struct CarFixture
{
	CCar car;
};
BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)
	BOOST_AUTO_TEST_CASE(on_create_engine_turn_off)
	{
		BOOST_CHECK(!car.IsEngineOn());
	}
	BOOST_AUTO_TEST_CASE(on_create_speed_is_0)
	{
		BOOST_CHECK(car.GetSpeed() == 0);
	}
	BOOST_AUTO_TEST_CASE(on_create_gear_is_neutral)
	{
		BOOST_CHECK(car.GetGear() == GearType::neutral);
	}
	BOOST_AUTO_TEST_CASE(engine_can_be_turned_on)
	{
		BOOST_CHECK(car.TurnEngineOn() && car.IsEngineOn());
	}

	struct when_engine_turned_on_ : CarFixture
	{
		when_engine_turned_on_()
		{
			car.TurnEngineOn();
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_engine_turned_on, when_engine_turned_on_)
		BOOST_AUTO_TEST_CASE(can_be_turned_off)
		{
			BOOST_CHECK(car.TurnEngineOff());
		}
		BOOST_AUTO_TEST_CASE(on_engine_on_speed_is_0)
		{
			BOOST_CHECK(car.GetSpeed() == 0);
		}
		BOOST_AUTO_TEST_CASE(on_engine_on_gear_is_neutral)
		{
			BOOST_CHECK(car.GetGear() == GearType::neutral);
		}
		BOOST_AUTO_TEST_CASE(can_set_a_reverse_gear)
		{
			BOOST_CHECK(car.SetGear(GearType::reverse) && (car.GetGear() == GearType::reverse));
		}
		BOOST_AUTO_TEST_CASE(can_set_a_low_gear)
		{
			BOOST_CHECK(car.SetGear(GearType::low) && (car.GetGear() == GearType::low));
		}

		struct when_reverse_gear_set_ : when_engine_turned_on_
		{
			when_reverse_gear_set_()
			{
				car.SetGear(GearType::reverse);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(when_reverse_gear_set, when_reverse_gear_set_)
			BOOST_AUTO_TEST_CASE(can_set_speed_ranged_from_0_to_20)
			{
				car.SetSpeed(20);
				BOOST_CHECK(car.GetSpeed() == -20);
				ExpectOperationFailure(car, [](auto & car)
				{
					return car.SetSpeed(-1);
				});
				ExpectOperationFailure(car, [](auto & car)
				{
					return car.SetSpeed(30);
				});
			}

			struct when_speed_not_0_ : when_reverse_gear_set_
			{
				when_speed_not_0_()
				{
					car.SetSpeed(20);
				}
			};
			BOOST_FIXTURE_TEST_SUITE(when_speed_not_0, when_speed_not_0_)
				BOOST_AUTO_TEST_CASE(can_not_set_low_gear)
				{
					ExpectOperationFailure(car, [](auto & car)
					{
						return car.SetGear(GearType::low);
					});
				}
				BOOST_AUTO_TEST_CASE(can_set_0_speed)
				{
					BOOST_CHECK(car.SetSpeed(0));
				}
			BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE_END()

		struct when_neutral_gear_set_and_speed_not_0_ : when_engine_turned_on_
		{
			when_neutral_gear_set_and_speed_not_0_()
			{
				car.SetGear(GearType::reverse);
				car.SetSpeed(10);
				car.SetGear(GearType::neutral);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(when_neutral_gear_set_and_speed_not_0, when_neutral_gear_set_and_speed_not_0_)
			BOOST_AUTO_TEST_CASE(can_not_set_bigger_speed)
			{
				ExpectOperationFailure(car, [](auto & car)
				{
					return car.SetSpeed(20);
				});
			}
			BOOST_AUTO_TEST_CASE(can_not_set_reverse_gear)
			{
				ExpectOperationFailure(car, [](auto & car)
				{
					return car.SetGear(GearType::reverse);
				});
			}
			BOOST_AUTO_TEST_CASE(can_set_lower_speed)
			{
				BOOST_CHECK(car.SetSpeed(5));
			}
		BOOST_AUTO_TEST_SUITE_END()

		struct when_low_gear_set_ : when_engine_turned_on_
		{
			when_low_gear_set_()
			{
				car.SetGear(GearType::low);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(when_low_gear_set, when_low_gear_set_)
			BOOST_AUTO_TEST_CASE(can_set_speed_ranged_from_0_to_30)
			{
				car.SetSpeed(30);
				BOOST_CHECK(car.GetSpeed() == 30);
				ExpectOperationFailure(car, [](auto & car)
				{
					return car.SetSpeed(-1);
				});
				ExpectOperationFailure(car, [](auto & car)
				{
					return car.SetSpeed(40);
				});
			}
		
			struct when_speed_not_0_ : when_low_gear_set_
			{
				when_speed_not_0_()
				{
					car.SetSpeed(30);
				}
			};
			BOOST_FIXTURE_TEST_SUITE(when_speed_not_0, when_speed_not_0_)
				BOOST_AUTO_TEST_CASE(can_set_next_gear)
				{
					BOOST_CHECK(car.SetGear(GearType::second) && (car.GetGear() == GearType::second));
				}
				BOOST_AUTO_TEST_CASE(can_not_set_reverse_gear)
				{
					ExpectOperationFailure(car, [](auto & car)
					{
						return car.SetGear(GearType::reverse);
					});
				}
			BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()