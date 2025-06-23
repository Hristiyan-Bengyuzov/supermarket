#pragma once
#include "Vector.hpp"
#include "SharedPtr.hpp"
#include "Command.h"
#include "AuthService.h"
#include "EmployeeService.h"
#include "ProductService.h"
#include "ManagerService.h"
#include "CashierService.h"
#include "RegisterCommand.h"
#include "LoginCommand.h"
#include "ListUserCommand.h"
#include "ListWorkersCommand.h"
#include "ListProductsCommand.h"
#include "LeaveCommand.h"
#include "LogoutCommand.h"
#include "ListPendingCommand.h"
#include "ApproveCommand.h"
#include "DeclineCommand.h"
#include "WarnCashierCommand.h"
#include "PromoteCashierCommand.h"
#include "FireCashierCommand.h"
#include "AddCategoryCommand.h"
#include "DeleteCategoryCommand.h"
#include "AddProductCommand.h"
#include "DeleteProductCommand.h"
#include "LoadProductsCommand.h"
#include "LoadGiftCardsCommand.h"
#include "SellCommand.h"

class CommandRegistry {
private:
	Vector<SharedPtr<Command>> commands;
	AuthService& authService;
	EmployeeService& employeeService;
	ProductService& productService;
	ManagerService& managerService;
	CashierService& cashierService;

public:
	CommandRegistry(AuthService& authService, EmployeeService& employeeService, ProductService& productService, ManagerService& managerService, CashierService& cashierService);
	void executeCommand(const String& commandLine);
	void showHelp() const;
};