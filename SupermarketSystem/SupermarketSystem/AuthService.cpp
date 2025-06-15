#include "AuthService.h"

AuthService::AuthService(EmployeeRepository& employeeRepo) : employeeRepo(employeeRepo)
{
}

bool AuthService::login(size_t employeeId, const String& plainPass)
{
	if (isAuthenticated())
		throw std::runtime_error("Already authenticated - please logout first");

	SharedPtr<Employee> employee = employeeRepo.findById(employeeId);
	if (!employee)
		throw std::runtime_error("Employee not found");

	if (employee->checkPass(plainPass))
		throw std::runtime_error("Invalid password");

	currentEmployee = employee;
	return true;
}

bool AuthService::logout()
{
	if (!isAuthenticated())
		throw std::runtime_error("No employee is currently authenticated");

	currentEmployee = SharedPtr<Employee>();
	return true;
}

bool AuthService::isAuthenticated() const
{
	return currentEmployee.get() != nullptr;
}

const SharedPtr<Employee>& AuthService::getCurrentEmployee() const
{
	if (!isAuthenticated())
		throw std::runtime_error("No employee is currently authenticated");
	return currentEmployee;
}
