#pragma once
#include "Repository.hpp"
#include "Transaction.h"

class TransactionRepository : public Repository<Transaction> {
	bool loadData();
public:
	TransactionRepository();
};