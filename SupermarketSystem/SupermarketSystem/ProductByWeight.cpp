#include "ProductByWeight.h"

ProductByWeight::ProductByWeight(const String& name, size_t categoryId, double price, double totalKilos) : Product(name, categoryId, price)
{
	this->totalKilos = totalKilos;
}

double ProductByWeight::getTotalPrice(double kilos) const
{
	return price * kilos;
}

void ProductByWeight::sell(double kilos)
{
	if (kilos > totalKilos)
		throw std::runtime_error("Not enough weight in stock.");
	totalKilos -= kilos;
}

ProductType ProductByWeight::getType() const
{
	return ProductType::ByWeight;
}
