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

Manager::Manager(const String& name, const String& familyName, const String& phoneNumber, unsigned age, const String& plainPass) : Employee(name, familyName, phoneNumber, age, plainPass, Role::Manager)
{
	this->specialCode = generateSpecialCode();
	saveCodeToFile();
}
