#pragma once
#include "String.h"
#include "Serializable.h"

struct TransactionItem : public Serializable {
	String productName;
	double quantityOrWeight;
	double price;
	double total;
	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
};