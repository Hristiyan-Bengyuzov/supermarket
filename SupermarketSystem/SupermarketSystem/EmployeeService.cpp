#include "EmployeeService.h"

EmployeeService::EmployeeService(EmployeeRepository& employeeRepo) : employeeRepo(employeeRepo)
{
}

void EmployeeService::listWorkers(std::ostream& os) const
{
	if (employeeRepo.count() == 0)
		throw std::runtime_error("No employees in the store");

	auto employees = employeeRepo.getAll();
	os << "Employees: " << employees.getSize() << std::endl;
	for (size_t i = 0; i < employees.getSize(); i++)
	{
		employees[i]->print(os);
		os << std::endl;
	}
}

bool EmployeeService::leave(size_t employeeId)
{
	SharedPtr<Employee> employee = employeeRepo.findById(employeeId);
	if (!employee)
		throw std::runtime_error("Employee not found");

	employeeRepo.removeById(employeeId);
	return employeeRepo.saveChanges();
}
