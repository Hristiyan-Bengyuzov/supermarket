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
#include "GiftCardRepository.h"
#include "CommandRegistry.h"
#include "LogService.h"

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	EmployeeRepository repo;
	ProductRepository repo2;
	CategoryRepository repo3;
	RegisterRequestRepository repo4;
	WarningRepository repo5;
	GiftCardRepository repo6;
	TransactionRepository repo7;
	LogRepository repo8;

	AuthService authService(repo, repo4);
	ManagerService managerService(repo, repo2, repo3, repo4, repo5, repo6);
	ProductService productService(repo2, repo3);
	EmployeeService empService(repo, repo7, repo8);
	CashierService cashierService(repo, repo2, repo6, repo7, repo5);
	LogService logService(repo8);

	//if (repo.count() == 0)
	//{
	//	repo.add(new Manager{ "Hris","Beng","0895556517",19,"password" });
	//	repo.add(new Cashier{ "Hari","Slavkov","0895556517",19,"password" });
	//	repo.saveChanges();
	//}

	//if (repo3.count() == 0)
	//{
	//	repo3.add(new Category{ "Fruit","Fruit are really cool" });
	//	repo3.add(new Category{ "Vegetables", "Vegetables are really cool" });
	//	repo3.saveChanges();
	//}

	CommandRegistry registry(authService, empService, productService, managerService, cashierService, logService);

	while (true)
	{
		String command = String::readLine("Enter command: ");
		registry.executeCommand(command);
	}
}
