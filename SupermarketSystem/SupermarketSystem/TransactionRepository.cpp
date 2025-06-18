#include "TransactionRepository.h"
#include "Loader.hpp"

bool TransactionRepository::loadData()
{
	return load<Transaction>(file, items);
}

TransactionRepository::TransactionRepository() : Repository<Transaction>("transactions.bin")
{
	loadData();
}
