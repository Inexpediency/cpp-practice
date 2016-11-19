// tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Task1/Body.h"
#include "../Task1/Sphere.h"
#include "../Task1/Parallelepiped.h"
#include "../Task1/Cone.h"
#include "../Task1/Cylinder.h"
#include "../Task1/Compound.h"

class CBodyChild : public CBody
{
public:
	CBodyChild() = delete;
	CBodyChild(double density, double volume)
	{
		m_density = density;
		m_volume = volume;
	};
	double GetVolume() const
	{
		return m_volume;
	}
private:
	double m_volume = NAN;
};

struct  BodyFixture
{
	CBodyChild body = CBodyChild(1, 10);
};

BOOST_FIXTURE_TEST_SUITE(Body_child_on_create, BodyFixture)
	BOOST_AUTO_TEST_CASE(know_its_volume)
	{
		BOOST_CHECK_EQUAL(body.GetVolume(), 10);
	}
	BOOST_AUTO_TEST_CASE(know_its_mass)
	{
		BOOST_CHECK_EQUAL(body.GetMass(), 10);
	}
	BOOST_AUTO_TEST_CASE(know_its_density)
	{
		BOOST_CHECK_EQUAL(body.GetDensity(), 1);
	}
	BOOST_AUTO_TEST_CASE(can_convert_to_string)
	{
		BOOST_CHECK_EQUAL(body.ToString(), "Body: mass = 10.000000, density = 1.000000, volume = 10.000000");
	}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(Sphere)
	BOOST_AUTO_TEST_CASE(can_not_create_with_negative_radius)
	{
		BOOST_CHECK_THROW(CSphere(1, -1), std::invalid_argument);
		BOOST_CHECK_THROW(CSphere(1, 0), std::invalid_argument);
	}
	BOOST_AUTO_TEST_CASE(can_not_create_with_negative_mass)
	{
		BOOST_CHECK_THROW(CSphere(-1, 1), std::invalid_argument);
		BOOST_CHECK_THROW(CSphere(0, 1), std::invalid_argument);
	}
	struct SphereFixture
	{
		CSphere sphere = CSphere(1, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(on_create, SphereFixture)
		BOOST_AUTO_TEST_CASE(know_its_radius)
		{
			BOOST_CHECK_EQUAL(sphere.GetRadius(), 2);
		}
		BOOST_AUTO_TEST_CASE(can_calc_volume)
		{
			BOOST_CHECK_EQUAL(sphere.GetVolume(), 33.510321638291124);
		}
		BOOST_AUTO_TEST_CASE(can_convert_to_string)
		{
			BOOST_CHECK_EQUAL(sphere.ToString(), "Sphere: mass = 33.510322, density = 1.000000, volume = 33.510322, radius = 2.000000");
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Parallelepiped)
	BOOST_AUTO_TEST_CASE(can_not_create_with_negative_width)
	{
		BOOST_CHECK_THROW(CParallelepiped(1, -1, 1, 1), std::invalid_argument);
		BOOST_CHECK_THROW(CParallelepiped(1, 0, 1, 1), std::invalid_argument);
	}
	BOOST_AUTO_TEST_CASE(can_not_create_with_negative_height)
	{
		BOOST_CHECK_THROW(CParallelepiped(1, 1, -1, 1), std::invalid_argument);
		BOOST_CHECK_THROW(CParallelepiped(1, 1, 0, 1), std::invalid_argument);
	}
	BOOST_AUTO_TEST_CASE(can_not_create_with_negative_depth)
	{
		BOOST_CHECK_THROW(CParallelepiped(1, 1, 1, -1), std::invalid_argument);
		BOOST_CHECK_THROW(CParallelepiped(1, 1, 1, 0), std::invalid_argument);
	}
	BOOST_AUTO_TEST_CASE(can_not_create_with_negative_mass)
	{
		BOOST_CHECK_THROW(CParallelepiped(-1, 1, 1, 1), std::invalid_argument);
		BOOST_CHECK_THROW(CParallelepiped(0, 1, 1, 1), std::invalid_argument);
	}
	struct ParallelepipedFixture
	{
		CParallelepiped parallelepiped = CParallelepiped(1, 1, 1, 1);
	};
	BOOST_FIXTURE_TEST_SUITE(on_create, ParallelepipedFixture)
		BOOST_AUTO_TEST_CASE(know_its_width)
		{
			BOOST_CHECK_EQUAL(parallelepiped.GetWidth(), 1);
		}
		BOOST_AUTO_TEST_CASE(know_its_height)
		{
			BOOST_CHECK_EQUAL(parallelepiped.GetHeight(), 1);
		}
		BOOST_AUTO_TEST_CASE(know_its_depth)
		{
			BOOST_CHECK_EQUAL(parallelepiped.GetDepth(), 1);
		}
		BOOST_AUTO_TEST_CASE(can_calc_volume)
		{
			BOOST_CHECK_EQUAL(parallelepiped.GetVolume(), 1);
		}
		BOOST_AUTO_TEST_CASE(can_convert_to_string)
		{
			std::string correct = "Parallelepiped: mass = 1.000000, density = 1.000000, volume = 1.000000, depth = 1.000000, width = 1.000000, height = 1.000000";
			BOOST_CHECK_EQUAL(parallelepiped.ToString(), correct);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Cone)
	BOOST_AUTO_TEST_CASE(can_not_create_with_negative_base_radius)
	{
		BOOST_CHECK_THROW(CCone(1, -1, 1), std::invalid_argument);
		BOOST_CHECK_THROW(CCone(1, 0, 1), std::invalid_argument);
	}
	BOOST_AUTO_TEST_CASE(can_not_create_with_negative_height)
	{
		BOOST_CHECK_THROW(CCone(1, 1, -1), std::invalid_argument);
		BOOST_CHECK_THROW(CCone(1, 1, 0), std::invalid_argument);
	}
	struct ConeFixture
	{
		CCone cone = CCone(1, 2, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(on_create, ConeFixture)
		BOOST_AUTO_TEST_CASE(know_its_base_radius)
		{
			BOOST_CHECK_EQUAL(cone.GetBaseRadius(), 2);
		}
		BOOST_AUTO_TEST_CASE(know_its_height)
		{
			BOOST_CHECK_EQUAL(cone.GetHeight(), 2);
		}
		BOOST_AUTO_TEST_CASE(can_calc_volume)
		{
			BOOST_CHECK_EQUAL(cone.GetVolume(), 8.3775804095727811);
		}
		BOOST_AUTO_TEST_CASE(can_convert_to_string)
		{
			BOOST_CHECK_EQUAL(cone.ToString(), "Cone: mass = 8.377580, density = 1.000000, volume = 8.377580, base radius = 2.000000, height = 2.000000");
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Cylinder)
	BOOST_AUTO_TEST_CASE(can_not_create_with_negative_base_radius)
	{
		BOOST_CHECK_THROW(CCylinder(1, -1, 1), std::invalid_argument);
		BOOST_CHECK_THROW(CCylinder(1, 0, 1), std::invalid_argument);
	}
	BOOST_AUTO_TEST_CASE(can_not_create_with_negative_height)
	{
		BOOST_CHECK_THROW(CCylinder(1, 1, -1), std::invalid_argument);
		BOOST_CHECK_THROW(CCylinder(1, 1, 0), std::invalid_argument);
	}
	struct CylinderFixture
	{
		CCylinder cylinder = CCylinder(1, 2, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(on_create, CylinderFixture)
		BOOST_AUTO_TEST_CASE(know_its_base_radius)
		{
			BOOST_CHECK_EQUAL(cylinder.GetBaseRadius(), 2);
		}
		BOOST_AUTO_TEST_CASE(know_its_height)
		{
			BOOST_CHECK_EQUAL(cylinder.GetHeight(), 2);
		}
		BOOST_AUTO_TEST_CASE(can_calc_volume)
		{
			BOOST_CHECK_EQUAL(cylinder.GetVolume(), 50.26548245743669);
		}
		BOOST_AUTO_TEST_CASE(can_convert_to_string)
		{
			BOOST_CHECK_EQUAL(cylinder.ToString(), "Cylinder: mass = 50.265482, density = 1.000000, volume = 50.265482, base radius = 2.000000, height = 2.000000");
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

struct CompoundFixture
{
	CCompound compound;
};
BOOST_FIXTURE_TEST_SUITE(Compound_on_create, CompoundFixture)
	BOOST_AUTO_TEST_CASE(have_not_children)
	{
		BOOST_CHECK(compound.GetChildren().empty());
	}
	BOOST_AUTO_TEST_CASE(can_add_child)
	{
		CSphere sphere(1, 2);
		BOOST_CHECK(compound.AddChild(std::make_shared<CSphere>(sphere)));
		BOOST_CHECK_EQUAL(compound.GetChildren()[0]->ToString(), "Sphere: mass = 33.510322, density = 1.000000, volume = 33.510322, radius = 2.000000");
	}
	BOOST_AUTO_TEST_CASE(can_not_add_itself)
	{
		BOOST_CHECK(!compound.AddChild(std::shared_ptr<CCompound>(&compound)));
		BOOST_CHECK(compound.GetChildren().empty());
	}
BOOST_AUTO_TEST_SUITE_END()