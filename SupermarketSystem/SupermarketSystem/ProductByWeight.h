#pragma once
#include "Product.h"

class ProductByWeight : public Product {
private:
	double totalKilos = 0;

public:
	ProductByWeight() = default;
	ProductByWeight(const String& name, size_t categoryId, double price, double totalKilos);

	virtual double getTotalPrice(double kilos) const override;
	virtual void sell(double kilos) override;
	virtual ProductType getType() const override;
	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
	void print(std::ostream& os) const override;
};