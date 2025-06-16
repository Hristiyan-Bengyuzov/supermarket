#include "Warning.h"

Warning::Warning(size_t senderId, size_t cashierId, const String& description, unsigned severityPoints)
{
	id = warningCounter++;
	this->senderId = senderId;
	this->cashierId = cashierId;
	this->description = description;
	this->severityPoints = severityPoints;
}

Severity Warning::getSeverity() const
{
	if (severityPoints <= 100)  return Severity::Low;
	return severityPoints <= 200 ? Severity::Medium : Severity::High;
}

size_t Warning::getCashierId() const
{
	return cashierId;
}

size_t Warning::getId() const
{
	return id;
}

unsigned Warning::getSeverityPoints() const
{
	return severityPoints;
}

void Warning::serialize(std::ofstream& ofs) const
{
	ofs.write(reinterpret_cast<const char*>(&id), sizeof(size_t));
	ofs.write(reinterpret_cast<const char*>(&senderId), sizeof(size_t));
	ofs.write(reinterpret_cast<const char*>(&cashierId), sizeof(size_t));
	description.serialize(ofs);
	ofs.write(reinterpret_cast<const char*>(&severityPoints), sizeof(unsigned));
}

void Warning::deserialize(std::ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&id), sizeof(size_t));
	if (id >= warningCounter)
		warningCounter = id + 1;
	ifs.read(reinterpret_cast<char*>(&senderId), sizeof(size_t));
	ifs.read(reinterpret_cast<char*>(&cashierId), sizeof(size_t));
	description.deserialize(ifs);
	ifs.read(reinterpret_cast<char*>(&severityPoints), sizeof(unsigned));
}
