#pragma once
#include "TransactionItem.h"
#include "Serializable.h"
#include "Printable.h"
#include "DateTime.h"

static size_t transactionCounter = 0;
class Transaction : public Serializable, public Printable {
private:
	size_t id = 0;
	size_t cashierId = 0;
	Vector<TransactionItem> items;
	DateTime dateTime;
	double totalPrice = 0;

public:
	Transaction() = default;
	Transaction(size_t cashierId);

	size_t getCashierId() const;
	const DateTime& getDate() const;
	double getTotalPrice() const;
	size_t getId() const;
	void addItem(const TransactionItem& item);
	Vector<TransactionItem>& getItemsMutable();
	void calculateTotalPrice();
	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
	void print(std::ostream& os) const override;
};