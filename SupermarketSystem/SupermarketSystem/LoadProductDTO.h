#pragma once
#include "Product.h"

struct LoadProductDTO {
	ProductType type;
	size_t productId;
	double unitsOrWeight;
};