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

Manager::Manager(size_t id, const String& name, const String& familyName, const String& phoneNumber, unsigned age, const Password& pass)
{
	this->id = id;
	setName(name);
	setFamilyName(familyName);
	setPhoneNumber(phoneNumber);
	setAge(age);
	this->password = pass;
	this->specialCode = generateSpecialCode();
	saveCodeToFile();
}

Role Manager::getRole() const
{
	return Role::Manager;
}

const String& Manager::getSpecialCode() const
{
	return specialCode;
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
	Employee::deserialize(ifs);
	specialCode.deserialize(ifs);
}

void Manager::print(std::ostream& os) const
{
	os << "Role: Manager" << std::endl;
	Employee::print(os);
}
