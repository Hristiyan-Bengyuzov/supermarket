#pragma once
#include "EmployeeRepository.h"
#include "TransactionRepository.h"
#include "LogRepository.h"

class EmployeeService {
private:
	EmployeeRepository& employeeRepo;
	TransactionRepository& transactionRepo;
	LogRepository& logRepo;

public:
	EmployeeService(EmployeeRepository& employeeRepo, TransactionRepository& transactionRepo, LogRepository& logRepo);

	void listWorkers(std::ostream& os) const;
	void listTransactions(std::ostream& os) const;
	void listFeed(std::ostream& os) const;
	bool leave(size_t employeeId);
};