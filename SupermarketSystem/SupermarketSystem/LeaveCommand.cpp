#include "LeaveCommand.h"

LeaveCommand::LeaveCommand(EmployeeService& employeeService) : employeeService(employeeService)
{
}

void LeaveCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 1)
	{
		showHelp();
		return;
	}

	if (employeeService.leave(employeeId))
	{
		std::cout << SUCCESS << "Successfully left." << RESET << std::endl;
	}
}

const String LeaveCommand::getName() const
{
	return String("leave");
}

bool LeaveCommand::canExecute(Role role, bool isAuthenticated) const
{
	return isAuthenticated;
}

void LeaveCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "");
}
