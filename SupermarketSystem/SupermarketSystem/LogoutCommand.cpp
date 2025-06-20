#include "LogoutCommand.h"

LogoutCommand::LogoutCommand(AuthService& authService) : authService(authService)
{
}

void LogoutCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 1)
	{
		showHelp();
		return;
	}

	if (authService.logout())
	{
		std::cout << SUCCESS << "Successfully logged out." << RESET << std::endl;
	}
}

const String LogoutCommand::getName() const
{
	return String("logout");
}

bool LogoutCommand::canExecute(Role role, bool isAuthenticated) const
{
	return isAuthenticated;
}

void LogoutCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "");
}

