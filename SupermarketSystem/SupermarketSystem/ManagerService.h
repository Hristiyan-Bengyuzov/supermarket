#pragma once
#include "EmployeeRepository.h"
#include "ProductRepository.h"
#include "CategoryRepository.h"
#include "RegisterRequestRepository.h"

class ManagerService {
private:
	EmployeeRepository& employeeRepo;
	ProductRepository& productRepo;
	CategoryRepository& categoryRepo;
	RegisterRequestRepository& requestRepo;

public:
	ManagerService(EmployeeRepository& employeeRepo, ProductRepository& productRepo, CategoryRepository& categoryRepo, RegisterRequestRepository& requestRepo);

	void listPending(std::ostream& os) const;
};