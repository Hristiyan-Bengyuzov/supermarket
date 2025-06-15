#pragma once
#include "EmployeeRepository.h"
#include "Employee.h"
#include "RegisterRequestRepository.h"
#include "RegisterDTO.h"

class AuthService {
private:
	EmployeeRepository& employeeRepo;
	RegisterRequestRepository& requestRepo;
	SharedPtr<Employee> currentEmployee;

public:
	AuthService(EmployeeRepository& employeeRepo, RegisterRequestRepository& registerRepo);

	bool login(size_t employeeId, const String& password);
	bool logout();
	bool registerEmployee(const RegisterDTO& dto);

	bool isAuthenticated() const;
	const SharedPtr<Employee>& getCurrentEmployee() const;
};