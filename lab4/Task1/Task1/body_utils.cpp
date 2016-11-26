#include "stdafx.h"
#include "body_utils.h"

std::shared_ptr<CBody> GetSimpleBody(std::string body)
{
	std::string bodyName = body.substr(0, body.find(":"));
	body.erase(0, bodyName.size());
	if (bodyName == "Cone")
	{
		return GetCone(body);
	}
	else if (bodyName == "Cylinder")
	{
		return GetCylinder(body);
	}
	else if (bodyName == "Sphere")
	{
		return GetSphere(body);
	}
	else if (bodyName == "Parallelepiped")
	{
		return GetParallelepiped(body);
	}
	return nullptr;
}

std::vector<double> GetNumbers(const std::string & string)
{
	std::smatch matchResult;
	std::vector<double> result;
	std::string str(string);
	while (std::regex_search(str, matchResult, std::regex("(\\s|$)" + DOUBLE_PATTERN)))
	{
		std::string number = matchResult[0];
		str.erase(str.find(number), number.size());
		if (('0' >= number[0]) || (number[0] >= '9'))
		{
			number.erase(0, 1);
		}
		result.insert(result.cend(), stod(number));
	}
	return result;
}

std::shared_ptr<CCone> GetCone(const std::string & cone)
{
	const std::string coneArgumentsPattern = ": density = " + DOUBLE_PATTERN + 
											", radius = " + DOUBLE_PATTERN + 
											", height = " + DOUBLE_PATTERN;
	if (!std::regex_match(cone, std::regex(coneArgumentsPattern)))
	{
		return nullptr;
	}
	std::vector<double> arguments = GetNumbers(cone);
	return std::make_shared<CCone>(CCone(arguments[0], arguments[1], arguments[2]));
}

std::shared_ptr<CCylinder> GetCylinder(const std::string & cylinder)
{
	const std::string cylinderArgumentsPattern = ": density = " + DOUBLE_PATTERN + 
												", radius = " + DOUBLE_PATTERN + 
												", height = " + DOUBLE_PATTERN;
	if (!std::regex_match(cylinder, std::regex(cylinderArgumentsPattern)))
	{
		return nullptr;
	}
	std::vector<double> arguments = GetNumbers(cylinder);
	return std::make_shared<CCylinder>(CCylinder(arguments[0], arguments[1], arguments[2]));
}

std::shared_ptr<CSphere> GetSphere(const std::string & sphere)
{
	const std::string sphereArgumentsPattern = ": density = " + DOUBLE_PATTERN +
											", radius = " + DOUBLE_PATTERN;
	if (!std::regex_match(sphere, std::regex(sphereArgumentsPattern)))
	{
		return nullptr;
	}
	std::vector<double> arguments = GetNumbers(sphere);
	return std::make_shared<CSphere>(CSphere(arguments[0], arguments[1]));
}

std::shared_ptr<CParallelepiped> GetParallelepiped(const std::string & parallelepiped)
{

	const std::string parallelepipedArgumentsPattern = ": density = " + DOUBLE_PATTERN + 
													", depth = " + DOUBLE_PATTERN + 
													", width = " + DOUBLE_PATTERN + 
													", height = " + DOUBLE_PATTERN;
	if (!std::regex_match(parallelepiped, std::regex(parallelepipedArgumentsPattern)))
	{
		return nullptr;
	}
	std::vector<double> arguments = GetNumbers(parallelepiped);
	return std::make_shared<CParallelepiped>(CParallelepiped(arguments[0], arguments[1], arguments[2], arguments[3]));
}

std::shared_ptr<CCompound> GetCompound(std::istream & compound, std::ostream & errorStream)
{
	std::shared_ptr<CCompound> compoundObj = std::make_shared<CCompound>(CCompound());
	std::shared_ptr<CBody> childBody;
	std::string line;

	while (std::getline(compound, line) && line != END_COMPOUND_STR)
	{
		childBody = GetSimpleBody(line);
		if (childBody == nullptr)
		{
			std::string bodyName = line.substr(0, line.find(":"));
			if (bodyName == "Compound")
			{
				childBody = GetCompound(compound, errorStream);
			}
			else
			{
				errorStream << "Incorrect body" << std::endl;
			}
		}
		compoundObj->AddChild(childBody);
	}
	return compoundObj;
}

std::shared_ptr<CBody> GetHeaviestBody(const std::vector<std::shared_ptr<CBody>> & someBody)
{
	auto max = std::max_element(someBody.cbegin(), someBody.cend(), [](const auto & arg1, const auto & arg2) {
		return arg1->GetMass() < arg2->GetMass();
	});
	return (max == someBody.cend()) ? nullptr : *max;
}

double GetWeightInWater(const std::shared_ptr<CBody> & body)
{
	return body->GetMass() * 10 - body->GetVolume() * 1000 * 10;
}

std::shared_ptr<CBody> GetEasiestBody(const std::vector<std::shared_ptr<CBody>> & someBody)
{
	auto easiest = std::min_element(someBody.cbegin(), someBody.cend(), [](const auto & arg1, const auto & arg2) {
		return GetWeightInWater(arg1) < GetWeightInWater(arg2);
	});
	return (easiest == someBody.cend()) ? nullptr : *easiest;
}