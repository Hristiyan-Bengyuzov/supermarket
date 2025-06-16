#pragma once
#include "String.h"

struct CreateWarningDTO {
	size_t managerId;
	size_t cashierId;
	unsigned points;
	String description;
};