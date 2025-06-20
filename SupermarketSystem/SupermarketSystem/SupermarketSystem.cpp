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

int main()
{
	EmployeeRepository repo;
	ProductRepository repo2;
	CategoryRepository repo3;
	RegisterRequestRepository repo4;
	WarningRepository repo5;
	GiftCardRepository repo6;

	AuthService authService(repo, repo4);
	ManagerService service(repo, repo2, repo3, repo4, repo5, repo6);
	ProductService productService(repo2, repo3);
	EmployeeService empService(repo);

	if (repo.count() == 0)
	{
		repo.add(new Manager{ "Hris","Beng","0895556517",19,"password" });
		repo.add(new Cashier{ "Hari","Slavkov","0895556517",19,"password" });
		repo.saveChanges();
	}

	if (repo3.count() == 0)
	{
		repo3.add(new Category{ "Fruit","Fruit are really cool" });
		repo3.add(new Category{ "Vegetables", "Vegetables are really cool" });
		repo3.saveChanges();
	}

	CommandRegistry registry(authService, empService, productService, service);

	while (true)
	{
		String command = String::readLine("Enter command: ");
		registry.executeCommand(command);
	}
}
