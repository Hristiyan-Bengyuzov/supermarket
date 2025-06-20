#include "DeleteProductCommand.h"

DeleteProductCommand::DeleteProductCommand(ManagerService& managerService) : managerService(managerService)
{
}

void DeleteProductCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 2)
	{
		showHelp();
		return;
	}

	size_t productId = args[1].toSizeT();
	if (managerService.deleteProduct(productId))
	{
		std::cout << SUCCESS << "Product deleted successfully." << RESET << std::endl;
	}
}

const String DeleteProductCommand::getName() const
{
	return String("delete-product");
}

bool DeleteProductCommand::canExecute(Role role, bool isAuthenticated) const
{
	return role == Role::Manager && isAuthenticated;
}

void DeleteProductCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "<product_id>");
}
