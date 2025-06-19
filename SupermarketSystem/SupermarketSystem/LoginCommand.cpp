#include "LoginCommand.h"

LoginCommand::LoginCommand(AuthService& authService) : authService(authService)
{
}

void LoginCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 3)
	{
		showHelp();
		return;
	}

	if (authService.login(args[1].toSizeT(), args[2]))
	{
		std::cout << SUCCESS << "Login successful!" << RESET << std::endl;
	}
}

const String LoginCommand::getName() const
{
	return String("login");
}

bool LoginCommand::canExecute(Role role, bool isAuthenticated) const
{
	return !isAuthenticated;
}

void LoginCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "<id> <password>");
}
