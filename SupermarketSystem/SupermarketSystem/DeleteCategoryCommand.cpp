#include "DeleteCategoryCommand.h"

DeleteCategoryCommand::DeleteCategoryCommand(ManagerService& managerService) : managerService(managerService)
{
}

void DeleteCategoryCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 2)
	{
		showHelp();
		return;
	}

	size_t categoryId = args[1].toSizeT();
	if (managerService.deleteCategory(categoryId))
	{
		std::cout << SUCCESS << "Category deleted successfully." << RESET << std::endl;
	}
}

const String DeleteCategoryCommand::getName() const
{
	return String("delete-category");
}

bool DeleteCategoryCommand::canExecute(Role role, bool isAuthenticated) const
{
	return role == Role::Manager && isAuthenticated;
}

void DeleteCategoryCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "<category_id>");
}
