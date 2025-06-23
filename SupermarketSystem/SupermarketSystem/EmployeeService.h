#pragma once
#include "EmployeeRepository.h"
#include "TransactionRepository.h"

class EmployeeService {
private:
	EmployeeRepository& employeeRepo;
	TransactionRepository& transactionRepo;

public:
	EmployeeService(EmployeeRepository& employeeRepo,TransactionRepository& transactionRepo);

	void listWorkers(std::ostream& os) const;
	void listTransactions(std::ostream& os) const;
	bool leave(size_t employeeId);
};