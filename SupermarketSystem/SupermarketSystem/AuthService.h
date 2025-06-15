#pragma once
#include "EmployeeRepository.h"
#include "Employee.h"

class AuthService {
private:
	EmployeeRepository& employeeRepo;
	SharedPtr<Employee> currentEmployee;

public:
	AuthService(EmployeeRepository& employeeRepo);

	bool login(size_t employeeId, const String& password);
	bool logout();

	bool isAuthenticated() const;
	const SharedPtr<Employee>& getCurrentEmployee() const;
};