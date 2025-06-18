#pragma once
#include "String.h"
#include "Serializable.h"
#include "GiftCard.h"

struct TransactionItem : public Serializable {
	size_t productId = 0;
	double quantityOrWeight = 0;
	double price = 0;
	double total = 0;

	TransactionItem() = default;
	TransactionItem(size_t productId, double quantityOrWeight, double price);

	void calculateTotal();
	void applyDiscount(ushort percentage);
	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
};