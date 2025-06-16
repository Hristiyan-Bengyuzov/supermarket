#include "Category.h"

Category::Category(const String& name, const String& description)
{
	this->id = categoryCounter++;
	this->name = name;
	this->description = description;
}

size_t Category::getId() const
{
	return id;
}

void Category::serialize(std::ofstream& ofs) const
{
	ofs.write(reinterpret_cast<const char*>(&id), sizeof(size_t));
	name.serialize(ofs);
	description.serialize(ofs);
}

void Category::deserialize(std::ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&id), sizeof(size_t));
	if (id >= categoryCounter)
		categoryCounter = id + 1;
	name.deserialize(ifs);
	description.deserialize(ifs);
}
