#include "ListFeedCommand.h"

ListFeedCommand::ListFeedCommand(EmployeeService& authService) : employeeService(authService)
{
}

void ListFeedCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 1)
	{
		showHelp();
		return;
	}
	employeeService.listFeed(std::cout);
}

const String ListFeedCommand::getName() const
{
	return String("list-feed");
}

bool ListFeedCommand::canExecute(Role role, bool isAuthenticated) const
{
	return isAuthenticated;
}

void ListFeedCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "");
}
