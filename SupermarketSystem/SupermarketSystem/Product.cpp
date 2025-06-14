#include "Product.h"

Product::Product(const String& name, size_t categoryId, double price)
{
	id = productCounter++;
	this->name = name;
	this->categoryId = categoryId;
	this->price = price;
}
