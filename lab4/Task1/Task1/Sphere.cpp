#include "stdafx.h"
#include "Sphere.h"

double CSphere::GetRadius() const
{
	return m_radius;
}


double CSphere::GetVolume() const
{
	return 4 * m_radius *  m_radius * m_radius * M_PI / 3;
}

CSphere::CSphere(double density, double radius)
	:m_radius(radius)
{
	if (radius <= 0)
	{
		throw std::invalid_argument("Can not to create sphere with negative radius");
	}
	if (density <= 0)
	{
		throw std::invalid_argument("Can not to create sphere with negative density");
	}
	m_density = density;
}

std::string CSphere::NameToString() const
{
	return "Sphere:";
}

std::string CSphere::FieldsToString() const
{
	return ", radius = " + std::to_string(GetRadius());
}

bool CSphere::operator==(const CSphere & arg) const
{
	return (arg.GetDensity() == GetDensity()) &&
		(arg.GetMass() == GetMass()) &&
		(arg.GetVolume() == GetVolume()) &&
		(arg.GetRadius() == GetRadius());
}