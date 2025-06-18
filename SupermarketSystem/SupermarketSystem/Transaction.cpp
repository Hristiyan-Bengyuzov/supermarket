#include "Transaction.h"

String Transaction::getCurrentDate() const
{
	time_t now = time(0);
	tm* localTime = localtime(&now);

	char buffer[11];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);

	return String(buffer);
}

Transaction::Transaction(size_t cashierId)
{
	this->id = transactionCounter++;
	this->cashierId = cashierId;
	this->date = getCurrentDate();
	calculateTotalPrice();
}

void Transaction::addItem(const TransactionItem& item)
{
	items.push_back(item);
	calculateTotalPrice();
}

Vector<TransactionItem>& Transaction::getItemsMutable()
{
	return items;
}

void Transaction::calculateTotalPrice()
{
	totalPrice = 0;
	for (size_t i = 0; i < items.getSize(); i++)
	{
		totalPrice += items[i].total;
	}
	print(std::cout);
}

void Transaction::serialize(std::ofstream& ofs) const
{
	ofs.write(reinterpret_cast<const char*>(&id), sizeof(size_t));
	ofs.write(reinterpret_cast<const char*>(&cashierId), sizeof(size_t));
	date.serialize(ofs);
	ofs.write(reinterpret_cast<const char*>(&totalPrice), sizeof(double));
	size_t itemsSize = items.getSize();
	ofs.write(reinterpret_cast<const char*>(&itemsSize), sizeof(size_t));
	for (size_t i = 0; i < itemsSize; i++)
	{
		items[i].serialize(ofs);
	}
}

void Transaction::deserialize(std::ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&id), sizeof(size_t));
	if (id >= transactionCounter)
		transactionCounter = id + 1;
	ifs.read(reinterpret_cast<char*>(&cashierId), sizeof(size_t));
	date.deserialize(ifs);
	ifs.read(reinterpret_cast<char*>(&totalPrice), sizeof(double));
	size_t itemsSize = 0;
	ifs.read(reinterpret_cast<char*>(&itemsSize), sizeof(size_t));
	items.clear();
	for (size_t i = 0; i < itemsSize; i++)
	{
		TransactionItem item;
		item.deserialize(ifs);
		items.push_back(item);
	}
}

void Transaction::print(std::ostream& os) const
{
	os << "Transaction ID: " << id << std::endl;
	os << "Price: " << totalPrice << std::endl;
}
