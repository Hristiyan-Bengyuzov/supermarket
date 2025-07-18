#include "DeclineCommand.h"

DeclineCommand::DeclineCommand(ManagerService& managerService, LogService& logService) : managerService(managerService), logService(logService)
{
}

void DeclineCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 3)
	{
		showHelp();
		return;
	}

	if (managerService.decline(employeeId, args[1].toSizeT(), args[2]))
	{
		logService.log(employeeId, "Declined registration request");
		std::cout << SUCCESS << "Request declined successfully." << RESET << std::endl;
	}
}

const String DeclineCommand::getName() const
{
	return String("decline");
}

bool DeclineCommand::canExecute(Role role, bool isAuthenticated) const
{
	return role == Role::Manager && isAuthenticated;
}

void DeclineCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "<request_id> <special_code>");
}
