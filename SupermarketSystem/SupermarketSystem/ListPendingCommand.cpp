#include "ListPendingCommand.h"

ListPendingCommand::ListPendingCommand(ManagerService& managerService) : managerService(managerService)
{
}

void ListPendingCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 1)
	{
		showHelp();
		return;
	}
	
	managerService.listPending(std::cout);
}

const String ListPendingCommand::getName() const
{
	return String("list-pending");
}

bool ListPendingCommand::canExecute(Role role, bool isAuthenticated) const
{
	return role == Role::Manager && isAuthenticated;
}

void ListPendingCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "");
}
