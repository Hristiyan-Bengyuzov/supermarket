#include "ProductByUnit.h"

ProductByUnit::ProductByUnit(const String& name, size_t categoryId, double price, size_t quantity) : Product(name, categoryId, price)
{
	this->quantity = quantity;
}

double ProductByUnit::getTotalPrice(double units) const
{
	if (units != (size_t)units)
		throw std::invalid_argument("Units must be a whole num");
	return price * units;
}

void ProductByUnit::sell(double units)
{
	if (units != (size_t)units)
		throw std::invalid_argument("Units must be a whole num");

	if (units > quantity)
		throw std::runtime_error("Not enough units in stock.");

	quantity -= (size_t)units;
}

ProductType ProductByUnit::getType() const
{
	return ProductType::ByUnit;
}

void ProductByUnit::serialize(std::ofstream& ofs) const
{
	ProductType type = getType();
	ofs.write(reinterpret_cast<const char*>(&type), sizeof(ProductType));
	Product::serialize(ofs);
	ofs.write(reinterpret_cast<const char*>(&quantity), sizeof(size_t));
}

void ProductByUnit::deserialize(std::ifstream& ifs)
{
	Product::deserialize(ifs);
	ifs.read(reinterpret_cast<char*>(&quantity), sizeof(size_t));
}

void ProductByUnit::print(std::ostream& os) const
{
	Product::print(os);
	os << " : " << quantity << std::endl;
}
