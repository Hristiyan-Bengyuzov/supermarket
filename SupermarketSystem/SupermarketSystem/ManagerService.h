#pragma once
#include "EmployeeRepository.h"
#include "ProductRepository.h"
#include "CategoryRepository.h"
#include "RegisterRequestRepository.h"
#include "WarningRepository.h"
#include "CreateWarningDTO.h"

class ManagerService {
private:
	EmployeeRepository& employeeRepo;
	ProductRepository& productRepo;
	CategoryRepository& categoryRepo;
	RegisterRequestRepository& requestRepo;
	WarningRepository& warningRepo;

public:
	ManagerService(EmployeeRepository& employeeRepo, ProductRepository& productRepo, CategoryRepository& categoryRepo, RegisterRequestRepository& requestRepo, WarningRepository& warningRepo);

	void listPending(std::ostream& os) const;
	bool approve(size_t managerId, size_t requestId, const String& specialCode);
	bool decline(size_t managerId, size_t requestId, const String& specialCode);
	void listWarnedCashiers(std::ostream& os, unsigned points) const;
	bool warnCashier(const CreateWarningDTO& dto);
};