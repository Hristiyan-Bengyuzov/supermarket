#include "WarningRepository.h"
#include "Loader.hpp"

bool WarningRepository::loadData()
{
	return load<Warning>(file, items);
}

WarningRepository::WarningRepository() : Repository("warnings.bin")
{
	loadData();
}

unsigned WarningRepository::getPoints(size_t cashierId) const
{
	unsigned res = 0;

	auto warnings = getAll();
	for (size_t i = 0; i < warnings.getSize(); i++)
	{
		if (warnings[i]->getCashierId() == cashierId)
		{
			res += warnings[i]->getSeverityPoints();
		}
	}
	return res;
}

bool WarningRepository::removeByCashierId(size_t cashierId)
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
		if (items[i]->getCashierId() == cashierId)
		{
			items.remove(i);
		}
	}
	return saveChanges();
}
