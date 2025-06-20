#include "ListWarnedCashiersCommand.h"

ListWarnedCashiersCommand::ListWarnedCashiersCommand(ManagerService& managerService) : managerService(managerService)
{
}

void ListWarnedCashiersCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 2)
	{
		showHelp();
		return;
	}

	size_t points = args[1].toSizeT();
	managerService.listWarnedCashiers(std::cout, points);
}

const String ListWarnedCashiersCommand::getName() const
{
	return String("list-warned-cashiers");
}

bool ListWarnedCashiersCommand::canExecute(Role role, bool isAuthenticated) const
{
	return role == Role::Manager && isAuthenticated;
}

void ListWarnedCashiersCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "<points>");
}
