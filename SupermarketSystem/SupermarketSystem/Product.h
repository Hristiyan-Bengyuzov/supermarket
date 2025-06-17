#pragma once
#include "String.h"
#include "Serializable.h"
#include "Printable.h"

enum ProductType {
	ByUnit,
	ByWeight
};

static size_t productCounter = 0;
class Product : public Serializable, public Printable {
protected:
	size_t id = 0;
	String name = "";
	size_t categoryId = 0;
	double price = 0;

public:
	Product() = default;
	Product(const String& name, size_t categoryId, double price);

	virtual ~Product() = default;

	virtual double getTotalPrice(double amount) const = 0;
	virtual void sell(double amount) = 0;
	virtual ProductType getType() const = 0;
	static ProductType getType(const String& str);
	size_t getId() const;
	size_t getCategoryId() const;
	const String& getName() const;

	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
	void print(std::ostream& os) const override;
};