#include "ApproveCommand.h"

ApproveCommand::ApproveCommand(ManagerService& managerService, LogService& logService) : managerService(managerService), logService(logService)
{
}

void ApproveCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 3)
	{
		showHelp();
		return;
	}

	if (managerService.approve(employeeId, args[1].toSizeT(), args[2]))
	{
		logService.log(employeeId, "Approved registration request");
		std::cout << SUCCESS << "Request approved successfully." << RESET << std::endl;
	}
}

const String ApproveCommand::getName() const
{
	return String("approve");
}

bool ApproveCommand::canExecute(Role role, bool isAuthenticated) const
{
	return role == Role::Manager && isAuthenticated;
}

void ApproveCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "<request_id> <special_code>");
}
