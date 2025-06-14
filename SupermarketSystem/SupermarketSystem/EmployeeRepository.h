#pragma once
#include "Repository.hpp"
#include "Employee.h"
#include "Manager.h"
#include "Cashier.h"

class EmployeeRepository : public Repository<Employee> {
	bool loadData();
public:
	EmployeeRepository();
};