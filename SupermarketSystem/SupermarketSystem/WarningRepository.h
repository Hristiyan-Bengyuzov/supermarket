#pragma once
#include "Repository.hpp"
#include "Warning.h"

class WarningRepository : public Repository<Warning> {
	bool loadData();
public:
	WarningRepository();

	unsigned getPoints(size_t cashierId) const;
	bool removeByCashierId(size_t cashierId);
};