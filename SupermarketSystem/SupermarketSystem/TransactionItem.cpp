#include "TransactionItem.h"

void TransactionItem::serialize(std::ofstream& ofs) const
{
	productName.serialize(ofs);
	ofs.write(reinterpret_cast<const char*>(&quantityOrWeight), sizeof(double));
	ofs.write(reinterpret_cast<const char*>(&price), sizeof(double));
	ofs.write(reinterpret_cast<const char*>(&total), sizeof(double));
}

void TransactionItem::deserialize(std::ifstream& ifs)
{
	productName.deserialize(ifs);
	ifs.read(reinterpret_cast<char*>(&quantityOrWeight), sizeof(double));
	ifs.read(reinterpret_cast<char*>(&price), sizeof(double));
	ifs.read(reinterpret_cast<char*>(&total), sizeof(double));
}
