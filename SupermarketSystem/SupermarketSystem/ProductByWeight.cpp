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

void ProductByWeight::serialize(std::ofstream& ofs) const
{
	ProductType type = getType();
	ofs.write(reinterpret_cast<const char*>(&type), sizeof(ProductType));
	Product::serialize(ofs);
	ofs.write(reinterpret_cast<const char*>(&totalKilos), sizeof(double));
}

void ProductByWeight::deserialize(std::ifstream& ifs)
{
	Product::deserialize(ifs);
	ifs.read(reinterpret_cast<char*>(&totalKilos), sizeof(double));
}

void ProductByWeight::print(std::ostream& os) const
{
	Product::print(os);
	os << "/kg : " << totalKilos << std::endl;
}
