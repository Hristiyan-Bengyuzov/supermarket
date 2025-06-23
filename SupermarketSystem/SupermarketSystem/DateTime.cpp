#include "DateTime.h"

DateTime::DateTime()
{
	rawTime = time(0);
	timeInfo = localtime(&rawTime);
}

String DateTime::toString() const
{
	char buffer[20];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
	return String(buffer);
}

void DateTime::serialize(std::ofstream& ofs) const
{
	ofs.write(reinterpret_cast<const char*>(&rawTime), sizeof(time_t));
}

void DateTime::deserialize(std::ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&rawTime), sizeof(time_t));
	timeInfo = localtime(&rawTime);
}
