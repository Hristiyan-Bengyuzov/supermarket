#include "Transaction.h"

Transaction::Transaction(size_t cashierId)
{
	this->id = transactionCounter++;
	this->cashierId = cashierId;
	calculateTotalPrice();
}

size_t Transaction::getCashierId() const
{
	return cashierId;
}

const DateTime& Transaction::getDate() const
{
	return dateTime;
}

double Transaction::getTotalPrice() const
{
	return totalPrice;
}

size_t Transaction::getId() const
{
	return id;
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
}

void Transaction::serialize(std::ofstream& ofs) const
{
	ofs.write(reinterpret_cast<const char*>(&id), sizeof(size_t));
	ofs.write(reinterpret_cast<const char*>(&cashierId), sizeof(size_t));
	dateTime.serialize(ofs);
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
	dateTime.deserialize(ifs);
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
