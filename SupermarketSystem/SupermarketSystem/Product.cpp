#include "Product.h"

Product::Product(const String& name, size_t categoryId, double price)
{
	id = productCounter++;
	this->name = name;
	this->categoryId = categoryId;
	this->price = price;
}

ProductType Product::getType(const String& str)
{
	if (str == "product_by_unit") return ProductType::ByUnit;
	if (str == "product_by_weight") return ProductType::ByWeight;
	throw std::runtime_error("Invalid type");
}

size_t Product::getId() const
{
	return id;
}

size_t Product::getCategoryId() const
{
	return categoryId;
}

const String& Product::getName() const
{
	return name;
}

void Product::serialize(std::ofstream& ofs) const
{
	ofs.write(reinterpret_cast<const char*>(&id), sizeof(size_t));
	name.serialize(ofs);
	ofs.write(reinterpret_cast<const char*>(&categoryId), sizeof(size_t));
	ofs.write(reinterpret_cast<const char*>(&price), sizeof(double));
}

void Product::deserialize(std::ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&id), sizeof(size_t));
	if (id >= productCounter)
		productCounter = id + 1;

	name.deserialize(ifs);
	ifs.read(reinterpret_cast<char*>(&categoryId), sizeof(size_t));
	ifs.read(reinterpret_cast<char*>(&price), sizeof(double));
}

void Product::print(std::ostream& os) const
{
	os << "  " << id << ". " << name << " : " << price;
}
