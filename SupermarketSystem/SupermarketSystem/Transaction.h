#pragma once
#include "TransactionItem.h"
#include "Serializable.h"
#include "Printable.h"

static size_t transactionCounter = 0;
class Transaction : public Serializable, public Printable {
private:
	size_t id = 0;
	size_t cashierId = 0;
	Vector<TransactionItem> items;
	String date = "";
	double totalPrice = 0;

	String getCurrentDate() const;
public:
	Transaction() = default;
	Transaction(size_t cashierId);

	void addItem(const TransactionItem& item);
	const Vector<TransactionItem>& getItems() const;
	void calculateTotalPrice();
	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
	void print(std::ostream& os) const override;
};