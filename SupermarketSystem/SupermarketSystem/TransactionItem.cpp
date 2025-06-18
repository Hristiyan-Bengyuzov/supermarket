#include "TransactionItem.h"

TransactionItem::TransactionItem(size_t productId, double quantityOrWeight, double price)
{
	this->productId = productId;
	this->quantityOrWeight = quantityOrWeight;
	this->price = price;
	calculateTotal();
}

void TransactionItem::calculateTotal()
{
	total = quantityOrWeight * price;
}

void TransactionItem::applyDiscount(ushort percentage)
{
	price -= (price * percentage / 100.0);
	calculateTotal();
}

void TransactionItem::serialize(std::ofstream& ofs) const
{
	ofs.write(reinterpret_cast<const char*>(&productId), sizeof(size_t));
	ofs.write(reinterpret_cast<const char*>(&quantityOrWeight), sizeof(double));
	ofs.write(reinterpret_cast<const char*>(&price), sizeof(double));
	ofs.write(reinterpret_cast<const char*>(&total), sizeof(double));
}

void TransactionItem::deserialize(std::ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&productId), sizeof(size_t));
	ifs.read(reinterpret_cast<char*>(&quantityOrWeight), sizeof(double));
	ifs.read(reinterpret_cast<char*>(&price), sizeof(double));
	ifs.read(reinterpret_cast<char*>(&total), sizeof(double));
}
