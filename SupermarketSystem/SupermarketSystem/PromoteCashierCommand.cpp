#include "PromoteCashierCommand.h"

PromoteCashierCommand::PromoteCashierCommand(ManagerService& managerService, LogService& logService) : managerService(managerService), logService(logService)
{
}

void PromoteCashierCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 3)
	{
		showHelp();
		return;
	}

	size_t cashierId = args[1].toSizeT();
	String specialCode = args[2];
	if (managerService.promoteCashier(employeeId, cashierId, specialCode))
	{
		logService.log(employeeId, "Promoted cashier with ID: " + String::parseFrom(cashierId));
		std::cout << SUCCESS << "Cashier promoted successfully." << RESET << std::endl;
	}
}

const String PromoteCashierCommand::getName() const
{
	return String("promote-cashier");
}

bool PromoteCashierCommand::canExecute(Role role, bool isAuthenticated) const
{
	return role == Role::Manager && isAuthenticated;
}

void PromoteCashierCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "<cashier_id> <special_code>");
}
