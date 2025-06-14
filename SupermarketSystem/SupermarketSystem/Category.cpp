#include "Category.h"

Category::Category(const String& name, const String& description)
{
	this->id = categoryCounter++;
	this->name = name;
	this->description = description;
}
