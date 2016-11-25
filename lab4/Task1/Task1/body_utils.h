#pragma once
#include <memory>
#include <vector>
#include "Body.h"
#include "Compound.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Parallelepiped.h"
#include "Sphere.h"

const std::string DOUBLE_PATTERN = "(\\d+(\\.\\d+)?)";
const std::string END_COMPOUND_STR = "End compound";

std::shared_ptr<CBody> GetSimpleBody(std::string body);
std::shared_ptr<CCone> GetCone(const std::string & cone);
std::shared_ptr<CCylinder> GetCylinder(const std::string & cylinder);
std::shared_ptr<CParallelepiped> GetParallelepiped(const std::string & parallelepiped);
std::shared_ptr<CSphere> GetSphere(const std::string & sphere);
std::shared_ptr<CCompound> GetCompound(std::istream & compound, std::ostream & errorStream);

std::shared_ptr<CBody> GetHeaviestBody(const std::vector<std::shared_ptr<CBody>> & bodyVector);
std::shared_ptr<CBody> GetEasiestBody(const std::vector<std::shared_ptr<CBody>> & bodyVector);