#include "LoadProductsCommand.h"

LoadProductsCommand::LoadProductsCommand(ManagerService& managerService, LogService& logService) : managerService(managerService), logService(logService)
{
}

void LoadProductsCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 2)
	{
		showHelp();
		return;
	}
	const String& filename = args[1];
	if (managerService.loadProducts(filename))
	{
		logService.log(employeeId, "Loaded products from file: " + filename);
		std::cout << SUCCESS << "Products loaded successfully from " << filename << "." << RESET << std::endl;
	}
}

const String LoadProductsCommand::getName() const
{
	return String("load-products");
}

bool LoadProductsCommand::canExecute(Role role, bool isAuthenticated) const
{
	return role == Role::Manager && isAuthenticated;
}

void LoadProductsCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "<filename>");
}
