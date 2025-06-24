#include "EmployeeService.h"

EmployeeService::EmployeeService(EmployeeRepository& employeeRepo, TransactionRepository& transactionRepo, LogRepository& logRepo, WarningRepository& warningRepo) : employeeRepo(employeeRepo), transactionRepo(transactionRepo), logRepo(logRepo), warningRepo(warningRepo)
{
}

void EmployeeService::listWorkers(std::ostream& os) const
{
	if (employeeRepo.count() == 0)
		throw std::runtime_error("No employees in the store");

	const Vector<SharedPtr<Employee>>& employees = employeeRepo.getAll();
	os << "Employees: " << employees.getSize() << std::endl;
	for (size_t i = 0; i < employees.getSize(); i++)
	{
		employees[i]->print(os);
		os << std::endl;
	}
}

void EmployeeService::listTransactions(std::ostream& os) const
{
	if (transactionRepo.count() == 0)
		throw std::runtime_error("No transactions");
	const Vector<SharedPtr<Transaction>>& transactions = transactionRepo.getAll();
	os << "Transactions: " << transactions.getSize() << std::endl;
	for (size_t i = 0; i < transactions.getSize(); i++)
	{
		transactions[i]->print(os);
		os << std::endl;
	}
}

void EmployeeService::listFeed(std::ostream& os) const
{
	if (logRepo.count() == 0)
		throw std::runtime_error("No logs in the feed");
	const Vector<SharedPtr<Log>>& logs = logRepo.getAll();
	os << "Feed: " << logs.getSize() << std::endl;
	for (size_t i = 0; i < logs.getSize(); i++)
	{
		logs[i]->print(os);
		os << std::endl;
	}
}

bool EmployeeService::leave(size_t employeeId)
{
	SharedPtr<Employee> employee = employeeRepo.findById(employeeId);
	if (!employee)
		throw std::runtime_error("Employee not found");

	employeeRepo.removeById(employeeId);
	return employeeRepo.saveChanges() && warningRepo.removeByCashierId(employeeId);
}
