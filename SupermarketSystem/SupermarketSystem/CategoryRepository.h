#pragma once
#include "Repository.hpp"
#include "Category.h"

class CategoryRepository : public Repository<Category> {
	bool loadData();
public:
	CategoryRepository();
};