#include "ListUserCommand.h"

ListUserCommand::ListUserCommand(AuthService& authService) : authService(authService)
{
}

void ListUserCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 1)
	{
		showHelp();
		return;
	}

	if (!authService.isAuthenticated())
	{
		std::cout << FAILURE << "You must be logged in to see your data." << RESET << std::endl;
		return;
	}

	const SharedPtr<Employee>& currentEmployee = authService.getCurrentEmployee();
	currentEmployee->print(std::cout);
}

const String ListUserCommand::getName() const
{
	return String("list-user-data");
}

bool ListUserCommand::canExecute(Role role, bool isAuthenticated) const
{
	return isAuthenticated;
}

void ListUserCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "");
}
