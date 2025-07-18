#include "FireCashierCommand.h"

FireCashierCommand::FireCashierCommand(ManagerService& managerService, LogService& logService) : managerService(managerService), logService(logService)
{
}

void FireCashierCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 3)
	{
		showHelp();
		return;
	}

	size_t cashierId = args[1].toSizeT();
	String specialCode = args[2];
	if (managerService.fireCashier(employeeId, cashierId, specialCode))
	{
		logService.log(employeeId, "Fired cashier with id: " + String::parseFrom(cashierId));
		std::cout << SUCCESS << "Cashier fired successfully." << RESET << std::endl;
	}
}

const String FireCashierCommand::getName() const
{
	return String("fire-cashier");
}

bool FireCashierCommand::canExecute(Role role, bool isAuthenticated) const
{
	return role == Role::Manager && isAuthenticated;
}

void FireCashierCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "<cashier_id> <special_code>");
}
