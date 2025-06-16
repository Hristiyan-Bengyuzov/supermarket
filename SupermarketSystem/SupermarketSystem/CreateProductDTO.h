#pragma once
#include "Product.h"
#include "String.h"

struct CreateProductDTO {
	ProductType type;
	String name;
	String categoryName;
	double price;
	double unitsOrWeight;
};
