#include "AddCategoryCommand.h"

AddCategoryCommand::AddCategoryCommand(ManagerService& managerService, LogService& logService) : managerService(managerService), logService(logService)
{
}

void AddCategoryCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() < 3)
	{
		showHelp();
		return;
	}

	String categoryName = args[1];
	String categoryDescription;
	for (size_t i = 2; i < args.getSize(); i++)
	{
		if (i > 2) categoryDescription += " ";
		categoryDescription += args[i];
	}

	CreateCategoryDTO categoryDTO{ categoryName, categoryDescription };
	if (managerService.addCategory(categoryDTO))
	{
		logService.log(employeeId, "Added category " + categoryName);
		std::cout << SUCCESS << "Category added successfully." << RESET << std::endl;
	}
}

const String AddCategoryCommand::getName() const
{
	return String("add-category");
}

bool AddCategoryCommand::canExecute(Role role, bool isAuthenticated) const
{
	return role == Role::Manager && isAuthenticated;
}

void AddCategoryCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "<category_name> <category_description>");
}
