#include "Log.h"

Log::Log(size_t employeeId, const String& message) : employeeId(employeeId), message(message)
{
}

void Log::serialize(std::ofstream& ofs) const
{
	ofs.write(reinterpret_cast<const char*>(&id), sizeof(size_t));
	ofs.write(reinterpret_cast<const char*>(&employeeId), sizeof(size_t));
	dateTime.serialize(ofs);
	message.serialize(ofs);
}

void Log::deserialize(std::ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&id), sizeof(size_t));
	if (id >= logCounter)
		logCounter = id + 1;
	ifs.read(reinterpret_cast<char*>(&employeeId), sizeof(size_t));
	dateTime.deserialize(ifs);
	message.deserialize(ifs);
}

void Log::print(std::ostream& os) const
{
	os << PINK << "  Employee ID: " << RESET << employeeId << std::endl;
	os << PINK << "  Date: " << RESET << dateTime.toString() << std::endl;
	os << PINK << "  Message: " << RESET << message << std::endl;
}
