#include "Employee.h"
#include "ValidationUtils.h"


void Employee::setName(const String& name)
{
	if (!ValidationUtils::isValidName(name))
		throw std::invalid_argument("Invalid name!");
	this->name = name;
}

void Employee::setFamilyName(const String& familyName)
{
	if (!ValidationUtils::isValidName(familyName))
		throw std::invalid_argument("Invalid family name!");
	this->familyName = familyName;
}

void Employee::setPhoneNumber(const String& phoneNumber)
{
	if (!ValidationUtils::isValidPhoneNumber(phoneNumber))
		throw std::invalid_argument("Invalid phone number!");
	this->phoneNumber = phoneNumber;
}

void Employee::setAge(unsigned age)
{
	if (age < 18)
		throw std::invalid_argument("Invalid age!");
	this->age = age;
}

void Employee::serialize(std::ofstream& ofs) const
{
}

void Employee::deserialize(std::ifstream& ifs)
{
}

Employee::Employee() = default;

Employee::Employee(const String& name, const String& familyName, const String& phoneNumber, unsigned age, const String& plainPass)
{
	setName(name);
	setFamilyName(familyName);
	setPhoneNumber(phoneNumber);
	setAge(age);
	password = Password(plainPass);
}