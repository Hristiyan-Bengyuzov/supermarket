#pragma once
#include "Vector.hpp"
#include "SharedPtr.hpp"
#include "Command.h"
#include "AuthService.h"
#include "EmployeeService.h"
#include "ProductService.h"
#include "RegisterCommand.h"
#include "LoginCommand.h"
#include "ListUserCommand.h"
#include "ListWorkersCommand.h"
#include "ListProductsCommand.h"

class CommandRegistry {
private:
	Vector<SharedPtr<Command>> commands;
	AuthService& authService;
	EmployeeService& employeeService;
	ProductService& productService;

public:
	CommandRegistry(AuthService& authService, EmployeeService& employeeService, ProductService& productService);
	void executeCommand(const String& commandLine);
	void showHelp() const;
};