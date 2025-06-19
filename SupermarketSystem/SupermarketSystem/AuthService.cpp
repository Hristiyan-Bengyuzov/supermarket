#include "AuthService.h"

AuthService::AuthService(EmployeeRepository& employeeRepo, RegisterRequestRepository& requestRepo) : employeeRepo(employeeRepo), requestRepo(requestRepo)
{
}

bool AuthService::login(size_t employeeId, const String& plainPass)
{
	if (isAuthenticated())
		throw std::runtime_error("Already authenticated - please logout first");

	SharedPtr<Employee> employee = employeeRepo.findById(employeeId);
	if (!employee)
		throw std::runtime_error("Employee not found");

	if (!employee->checkPass(plainPass))
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

bool AuthService::registerEmployee(const RegisterDTO& dto)
{
	switch (dto.role)
	{
		case Role::Cashier: {
			RegisterRequest request(dto.firstName, dto.lastName, dto.phoneNumber, dto.age, dto.plainPass);
			requestRepo.add(request);
			std::cout << "Cashier registration pending approval from a manager" << std::endl;
			return requestRepo.saveChanges();
		}
		case Role::Manager: {
			Manager* manager = new Manager{ dto.firstName, dto.lastName, dto.phoneNumber, dto.age, dto.plainPass };
			employeeRepo.add(manager);
			std::cout << "Special code: " << manager->getSpecialCode() << std::endl;
			std::cout << "Code: " << manager->getId() << "_special_code.txt" << std::endl;
			return employeeRepo.saveChanges();
		}
	}

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
