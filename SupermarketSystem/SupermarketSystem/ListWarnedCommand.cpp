#include "ListWarnedCommand.h"

ListWarnedCommand::ListWarnedCommand(ManagerService& managerService) : managerService(managerService)
{
}

void ListWarnedCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 2)
	{
		showHelp();
		return;
	}

	size_t points = args[1].toSizeT();
	managerService.listWarnedCashiers(std::cout, points);
}

const String ListWarnedCommand::getName() const
{
	return String("list-warned-cashiers");
}

bool ListWarnedCommand::canExecute(Role role, bool isAuthenticated) const
{
	return role == Role::Manager && isAuthenticated;
}

void ListWarnedCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "<points>");
}
