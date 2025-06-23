#include "ListTransactionsCommand.h"

ListTransactionsCommand::ListTransactionsCommand(EmployeeService& employeeService) : employeeService(employeeService)
{
}

void ListTransactionsCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 1)
	{
		showHelp();
		return;
	}

	employeeService.listTransactions(std::cout);
}

const String ListTransactionsCommand::getName() const
{
	return String("list-transactions");
}

bool ListTransactionsCommand::canExecute(Role role, bool isAuthenticated) const
{
	return isAuthenticated;
}

void ListTransactionsCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "");
}
