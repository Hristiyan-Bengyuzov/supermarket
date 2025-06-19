#include "RegisterCommand.h"

RegisterCommand::RegisterCommand(AuthService& authService) : authService(authService)
{
}

void RegisterCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 7)
	{
		showHelp();
		return;
	}

	Role role = Employee::getRole(args[1]);
	RegisterDTO dto = { role , args[2], args[3], args[4], args[5].toSizeT(), args[6] };

	if (authService.registerEmployee(dto))
	{
		std::cout << SUCCESS << "Registration successful!" << RESET << std::endl;
	}
}

const String RegisterCommand::getName() const
{
	return String("register");
}

bool RegisterCommand::canExecute(Role role, bool isAuthenticated) const
{
	return !isAuthenticated;
}

void RegisterCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "<role> <first_name> <last_name> <phone_number> <age> <password>");
}
