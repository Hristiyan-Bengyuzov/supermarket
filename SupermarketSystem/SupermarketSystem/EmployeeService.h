#pragma once
#include "EmployeeRepository.h"

class EmployeeService {
private:
	EmployeeRepository& employeeRepo;

public:
	EmployeeService(EmployeeRepository& employeeRepo);

	void listWorkers(std::ostream& os) const;
};