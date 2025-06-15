#pragma once
#include "Repository.hpp"
#include "Product.h"
#include "ProductByUnit.h"
#include "ProductByWeight.h"

class ProductRepository : public Repository<Product> {
	bool loadData();
public:
	ProductRepository();
};