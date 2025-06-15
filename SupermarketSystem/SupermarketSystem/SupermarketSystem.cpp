// SupermarketSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "String.h"
#include "PasswordUtils.h"
#include "Employee.h"
#include "GenUtils.h"
#include<ctime>
#include<cstdlib>
#include "Manager.h"
#include "Cashier.h"
#include "EmployeeRepository.h"
#include "EmployeeService.h"

int main()
{
	EmployeeRepository repo;
	if (repo.count() == 0)
	{
		repo.add(new Manager{ "Hristiyan","Bengyuzov", "0895556517", 19, "password" });
		repo.add(new Cashier{ "Haralampi","Slavkov", "0895556517", 19, "password" });
		repo.saveChanges();
	}

	EmployeeService service(repo);
	service.listWorkers(std::cout);
}
