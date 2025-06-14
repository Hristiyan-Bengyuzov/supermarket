#pragma once
#include "String.h"

static size_t categoryCounter = 0;
class Category {
private:
	size_t id = 0;
	String name = "";
	String description = "";
	
public:
	Category() = default;
	Category(const String& name, const String& description);
};