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

size_t CategoryRepository::getCategoryIdByName(const String& name) const
{
	SharedPtr<Category> category = findByName(name);
	if (!category)
		throw std::runtime_error("Category not found");
	return category->getId();
}
