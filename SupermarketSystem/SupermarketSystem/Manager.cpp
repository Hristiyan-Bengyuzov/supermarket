#include "Manager.h"
#include "GenUtils.h"
#include <fstream>

String Manager::generateSpecialCode() const
{
	String res;
	res += GenUtils::genDigit();
	for (size_t i = 0; i < 2; i++)
		res += GenUtils::genUpper();
	for (size_t i = 0; i < 3; i++)
		res += GenUtils::genDigit();
	res += GenUtils::genLower();
	return res;
}

void Manager::saveCodeToFile() const
{
	if (specialCode.getSize() == 0)
		return;

	String filePath;
	filePath += String::parseFrom(id);
	filePath += "_special_code.txt";
	std::ofstream ofs(filePath.c_str());

	if (!ofs.is_open())
		return;

	ofs << specialCode.c_str();
	ofs.close();
}

Manager::Manager(const String& name, const String& familyName, const String& phoneNumber, unsigned age, const String& plainPass) : Employee(name, familyName, phoneNumber, age, plainPass)
{
	this->specialCode = generateSpecialCode();
	saveCodeToFile();
}

Role Manager::getRole() const
{
	return Role::Manager;
}

void Manager::serialize(std::ofstream& ofs) const
{
	Role role = getRole();
	ofs.write(reinterpret_cast<const char*>(&role), sizeof(Role));

	Employee::serialize(ofs);
	specialCode.serialize(ofs);
}

void Manager::deserialize(std::ifstream& ifs)
{
	Role role;
	ifs.read(reinterpret_cast<char*>(&role), sizeof(Role));
	if (role != Role::Manager)
		throw std::runtime_error("Data corruption: Expected Manager role");

	Employee::deserialize(ifs);
	specialCode.deserialize(ifs);
}
