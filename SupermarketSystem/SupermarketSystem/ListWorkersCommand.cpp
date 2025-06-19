#include "ListWorkersCommand.h"

ListWorkersCommand::ListWorkersCommand(EmployeeService& employeeService) : employeeService(employeeService)
{
}

void ListWorkersCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 1)
	{
		showHelp();
		return;
	}

	employeeService.listWorkers(std::cout);
}

const String ListWorkersCommand::getName() const
{
	return String("list-workers");
}

bool ListWorkersCommand::canExecute(Role role, bool isAuthenticated) const
{
	return isAuthenticated;
}

void ListWorkersCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "");
}
