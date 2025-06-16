// SupermarketSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "String.h"
#include "PasswordUtils.h"
#include "Employee.h"
#include "GenUtils.h"
#include<ctime>
#include<cstdlib>
#include "ManagerService.h"
#include "AuthService.h"
#include "WarningRepository.h"
#include "EmployeeService.h"

int main()
{
	EmployeeRepository repo;
	ProductRepository repo2;
	CategoryRepository repo3;
	RegisterRequestRepository repo4;
	WarningRepository repo5;

	AuthService authService(repo, repo4);
	ManagerService service(repo, repo2, repo3, repo4, repo5);
	EmployeeService empService(repo);

	if (repo.count() == 0)
	{
		repo.add(new Manager{ "Hris","Beng","0895556517",19,"password" });
		repo.add(new Cashier{ "Hari","Slavkov","0895556517",19,"password" });
		repo.saveChanges();
	}

	//service.promoteCashier(0, 1, "5IR614c");
	empService.listWorkers(std::cout);
}
