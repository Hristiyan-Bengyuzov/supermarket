#pragma once
#include "Product.h"

class ProductByUnit : public Product {
private:
	size_t quantity = 0;

public:
	ProductByUnit() = default;
	ProductByUnit(const String& name, size_t categoryId, double price, size_t quantity);

	virtual double getTotalPrice(double units) const override;
	virtual void sell(double units) override;
	virtual ProductType getType() const override;
	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
	void print(std::ostream& os) const override;
};