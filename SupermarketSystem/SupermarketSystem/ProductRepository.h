#pragma once
#include "Repository.hpp"
#include "Product.h"
#include "ProductByUnit.h"
#include "ProductByWeight.h"

class ProductRepository : public Repository<Product> {
	bool loadData();
public:
	ProductRepository();

	bool hasProductWithCategory(size_t categoryId) const;
	const String& getNameById(size_t id) const;
};