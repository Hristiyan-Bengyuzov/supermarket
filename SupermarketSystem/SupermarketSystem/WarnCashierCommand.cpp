#include "WarnCashierCommand.h"
#include "CreateWarningDTO.h"

WarnCashierCommand::WarnCashierCommand(ManagerService& managerService, LogService& logService) : managerService(managerService), logService(logService)
{
}

void WarnCashierCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() < 4)
	{
		showHelp();
		return;
	}

	size_t cashierId = args[1].toSizeT();
	size_t points = args[2].toSizeT();

	String description;
	for (size_t i = 3; i < args.getSize(); i++) {
		if (i > 3) description += " ";
		description += args[i];
	}

	CreateWarningDTO warningDTO{ employeeId, cashierId, points, description };
	if (managerService.warnCashier(warningDTO))
	{
		logService.log(employeeId, "Warned cashier with id " + String::parseFrom(cashierId));
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
