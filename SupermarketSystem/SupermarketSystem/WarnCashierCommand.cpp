#include "WarnCashierCommand.h"
#include "CreateWarningDTO.h"

WarnCashierCommand::WarnCashierCommand(ManagerService& managerService) : managerService(managerService)
{
}

void WarnCashierCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 4)
	{
		showHelp();
		return;
	}

	size_t cashierId = args[1].toSizeT();
	size_t points = args[2].toSizeT();
	String description = args[3];
	CreateWarningDTO warningDTO{ employeeId, cashierId, points, description };
	if (managerService.warnCashier(warningDTO))
	{
		std::cout << SUCCESS << "Cashier warned successfully." << RESET << std::endl;
	}
}

const String WarnCashierCommand::getName() const
{
	return String("warn-cashier");
}

bool WarnCashierCommand::canExecute(Role role, bool isAuthenticated) const
{
	return role == Role::Manager && isAuthenticated;
}

void WarnCashierCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "<cashier_id> <points> <description>");
}
