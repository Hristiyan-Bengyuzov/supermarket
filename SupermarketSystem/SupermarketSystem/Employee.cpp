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

size_t Employee::getId() const
{
	return id;
}

const String& Employee::getName() const
{
	return name;
}

const String& Employee::getFamilyName() const
{
	return familyName;
}

const String& Employee::getPhoneNumber() const
{
	return phoneNumber;
}

unsigned Employee::getAge() const
{
	return age;
}

const Password& Employee::getPass() const
{
	return password;
}

bool Employee::checkPass(const String& plainPass) const
{
	return password == plainPass;
}

void Employee::serialize(std::ofstream& ofs) const
{
	ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));
	name.serialize(ofs);
	familyName.serialize(ofs);
	phoneNumber.serialize(ofs);
	ofs.write(reinterpret_cast<const char*>(&age), sizeof(age));
	password.serialize(ofs);
}

void Employee::deserialize(std::ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&id), sizeof(id));
	if (id >= counter)
		counter = id + 1;

	name.deserialize(ifs);
	familyName.deserialize(ifs);
	phoneNumber.deserialize(ifs);
	ifs.read(reinterpret_cast<char*>(&age), sizeof(age));
	password.deserialize(ifs);
}

void Employee::print(std::ostream& os) const
{
	os << "Id: " << id << std::endl;
	os << "First name: " << name << std::endl;
	os << "Last name: " << familyName << std::endl;
	os << "Phone number: " << phoneNumber << std::endl;
	os << "Age: " << age << std::endl;
}

Employee::Employee() = default;

Employee::Employee(const String& name, const String& familyName, const String& phoneNumber, unsigned age, const String& plainPass)
{
	id = counter++;
	setName(name);
	setFamilyName(familyName);
	setPhoneNumber(phoneNumber);
	setAge(age);
	password = Password(plainPass);
}