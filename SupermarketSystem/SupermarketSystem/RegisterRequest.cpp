#include "RegisterRequest.h"

RegisterRequest::RegisterRequest(const String& firstName, const String& familyName, const String& phoneNumber, unsigned age, const String& plainPass)
{
	id = requestCounter++;
	this->firstName = firstName;
	this->familyName = familyName;
	this->phoneNumber = phoneNumber;
	this->age = age;
	this->plainPass = plainPass;
}

void RegisterRequest::approve()
{
	if (status != Status::Pending)
		return;
	status = Status::Approved;
}

void RegisterRequest::decline()
{
	if (status != Status::Pending)
		return;
	status = Status::Declined;
}

size_t RegisterRequest::getId() const
{
	return id;
}

Status RegisterRequest::getStatus() const
{
	return status;
}

const String& RegisterRequest::getFirstName() const
{
	return firstName;
}

const String& RegisterRequest::getFamilyName() const
{
	return familyName;
}

const String& RegisterRequest::getPhoneNumber() const
{
	return phoneNumber;
}

unsigned RegisterRequest::getAge() const
{
	return age;
}

const String& RegisterRequest::getPlainPass() const
{
	return plainPass;
}

void RegisterRequest::serialize(std::ofstream& ofs) const
{
	ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));
	ofs.write(reinterpret_cast<const char*>(&status), sizeof(Status));
	firstName.serialize(ofs);
	familyName.serialize(ofs);
	phoneNumber.serialize(ofs);
	ofs.write(reinterpret_cast<const char*>(&age), sizeof(unsigned));
	plainPass.serialize(ofs);
}

void RegisterRequest::deserialize(std::ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&id), sizeof(id));
	if (id >= requestCounter)
		requestCounter = id + 1;

	ifs.read(reinterpret_cast<char*>(&status), sizeof(Status));
	firstName.deserialize(ifs);
	familyName.deserialize(ifs);
	phoneNumber.deserialize(ifs);
	ifs.read(reinterpret_cast<char*>(&age), sizeof(unsigned));
	plainPass.deserialize(ifs);
}

void RegisterRequest::print(std::ostream& os) const
{
	os << "  " << id << ". " << firstName << " " << familyName << " : " << phoneNumber << " : " << age << std::endl;
}
