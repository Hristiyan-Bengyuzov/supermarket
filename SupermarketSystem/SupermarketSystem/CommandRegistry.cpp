#include "CommandRegistry.h"

CommandRegistry::CommandRegistry(AuthService& authService, EmployeeService& employeeService, ProductService& productService, ManagerService& managerService) : authService(authService), employeeService(employeeService), productService(productService), managerService(managerService)
{
	commands.push_back(SharedPtr<Command>(new RegisterCommand(authService)));
	commands.push_back(SharedPtr<Command>(new LoginCommand(authService)));
	commands.push_back(SharedPtr<Command>(new ListUserCommand(authService)));
	commands.push_back(SharedPtr<Command>(new ListWorkersCommand(employeeService)));
	commands.push_back(SharedPtr<Command>(new ListProductsCommand(productService)));
	commands.push_back(SharedPtr<Command>(new LeaveCommand(employeeService)));
	commands.push_back(SharedPtr<Command>(new LogoutCommand(authService)));
	commands.push_back(SharedPtr<Command>(new ListPendingCommand(managerService)));
	commands.push_back(SharedPtr<Command>(new ApproveCommand(managerService)));
	commands.push_back(SharedPtr<Command>(new DeclineCommand(managerService)));
	commands.push_back(SharedPtr<Command>(new ListWarnedCommand(managerService)));
	commands.push_back(SharedPtr<Command>(new WarnCashierCommand(managerService)));
	commands.push_back(SharedPtr<Command>(new PromoteCashierCommand(managerService)));
	commands.push_back(SharedPtr<Command>(new FireCashierCommand(managerService)));
	commands.push_back(SharedPtr<Command>(new AddCategoryCommand(managerService)));
	commands.push_back(SharedPtr<Command>(new DeleteCategoryCommand(managerService)));
	commands.push_back(SharedPtr<Command>(new AddProductCommand(managerService)));
	commands.push_back(SharedPtr<Command>(new DeleteProductCommand(managerService)));
	commands.push_back(SharedPtr<Command>(new LoadProductsCommand(managerService)));
	commands.push_back(SharedPtr<Command>(new LoadGiftCardsCommand(managerService)));
}

void CommandRegistry::executeCommand(const String& commandLine)
{
	Vector<String> args = commandLine.split(' ');
	if (args.getSize() == 0)
	{
		showHelp();
		return;
	}

	String commandName = args[0];

	if (commandName == "help")
	{
		showHelp();
		return;
	}

	// Get current employee ID (0 if not authenticated)
	int employeeId = 0;
	Role currentRole = Role::None;
	if (authService.isAuthenticated() && authService.getCurrentEmployee())
	{
		employeeId = authService.getCurrentEmployee()->getId();
		currentRole = authService.getCurrentEmployee()->getRole();
	}

	bool found = false;

	for (size_t i = 0; i < commands.getSize(); i++)
	{
		if (commands[i]->getName() == commandName)
		{
			if (!commands[i]->canExecute(currentRole, authService.isAuthenticated()))
			{
				std::cerr << FAILURE << "You do not have permission to execute this command." << RESET << std::endl;
				return;
			}

			try
			{
				found = true;
				commands[i]->execute(args, employeeId);
			}
			catch (const std::exception& e)
			{
				std::cerr << FAILURE << "Error: " << e.what() << RESET << std::endl;
			}
			return;
		}
	}

	if (!found)
	{
		showHelp();
	}
}

void CommandRegistry::showHelp() const
{
	Role currentRole = Role::None;
	bool isAuthenticated = authService.isAuthenticated();

	if (isAuthenticated && authService.getCurrentEmployee()) {
		currentRole = authService.getCurrentEmployee()->getRole();
	}

	std::cout << "Available commands:" << std::endl;

	CommandUtils::printCommandWithArgs("help", "");

	for (size_t i = 0; i < commands.getSize(); i++)
	{
		if (commands[i]->canExecute(currentRole, isAuthenticated))
		{
			commands[i]->showHelp();
		}
	}
}