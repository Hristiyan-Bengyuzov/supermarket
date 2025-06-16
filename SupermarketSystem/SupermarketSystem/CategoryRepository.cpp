#include "CategoryRepository.h"
#include "Loader.hpp"

bool CategoryRepository::loadData()
{
	return load<Category>(file, items);
}

CategoryRepository::CategoryRepository() : Repository("categories.bin")
{
	loadData();
}
