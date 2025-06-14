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
