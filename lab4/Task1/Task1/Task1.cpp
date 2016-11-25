#include "stdafx.h"
#include "Body.h"
#include "Sphere.h"
#include "Parallelepiped.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Compound.h"
#include "body_utils.h"
#include "Menu.h"

void AddSimpleBodyToVecor(std::vector<std::shared_ptr<CBody>> & vector, const std::string & bodyName, const std::string & bodyArguments)
{
	try
	{
		std::cout << bodyName + bodyArguments << std::endl;
		std::shared_ptr<CBody> body = GetSimpleBody(bodyName + bodyArguments);
		if (body == nullptr)
		{
			std::cout << "Incorrect arguments" << std::endl;
		}
		else
		{
			vector.emplace_back(body);
		}
	}
	catch (std::invalid_argument & exeption)
	{
		std::cout << exeption.what() << std::endl;
	}
}

int main()
{
	CMenu menu;
	std::vector<std::shared_ptr<CBody>> bodies;
	menu.AddItem("end", "to stop input body", [&menu](const std::string &) {
		menu.Exit(); 
	});
	menu.AddItem("help", "to know more about inputing body", [&menu](const std::string &) { 
		menu.ShowInstructions(); 
	});
	menu.AddItem("Sphere", "to add sphere.\n Syntux:\n  Sphere: density = <double>, radius = <double>", [&bodies](const std::string & arg) {
		AddSimpleBodyToVecor(bodies, "Sphere", arg);
	});
	menu.AddItem("Cone", "to add cone.\n Syntux:\n  Cone: density = <double>, radius = <double>, height = <double>", [&bodies](const std::string & arg) {
		AddSimpleBodyToVecor(bodies, "Cone", arg);
	});
	menu.AddItem("Cylinder", "to add cylinder.\n Syntux:\n  Cylinder: density = <double>, radius = <double>, height = <double>", [&bodies](const std::string & arg) {
		AddSimpleBodyToVecor(bodies, "Cylinder", arg);
	});
	menu.AddItem("Parallelepiped", "to add parallelepiped.\n Syntux:\n  Parallelepiped: density = <double>, depth = <double>, width = <double>, height = <double>", [&bodies](const std::string & arg) {
		AddSimpleBodyToVecor(bodies, "Parallelepiped", arg);
	});
	menu.AddItem("Compound", "to add ñompound body. .\n Syntux:\n  Compound:\n  <body>\n  <body>\n  ...\n  End compound", [&bodies](const std::string & arg) {
		std::shared_ptr<CBody> compound = GetCompound(std::cin, std::cout);
		if (compound == nullptr)
		{
			std::cout << "Can not add pather or itself to itself";
		}
		else
		{
			bodies.emplace_back(compound);
		}
	});
	menu.Run();
	if (bodies.size() != 0)
	{
		std::cout << "Haviest body is:" << std::endl << GetHeaviestBody(bodies)->ToString() << std::endl;
		std::cout << "Easiest body in water is:" << std::endl << GetEasiestBody(bodies)->ToString() << std::endl;
	}
	return 0;
}