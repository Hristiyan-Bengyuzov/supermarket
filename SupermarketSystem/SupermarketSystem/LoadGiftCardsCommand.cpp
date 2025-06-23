#include "LoadGiftCardsCommand.h"

LoadGiftCardsCommand::LoadGiftCardsCommand(ManagerService& managerService, LogService& logService) : managerService(managerService), logService(logService)
{
}

void LoadGiftCardsCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 2)
	{
		showHelp();
		return;
	}
	const String& filePath = args[1];
	if (managerService.loadGiftCards(filePath))
	{
		logService.log(employeeId, "Loaded gift cards from file: " + filePath);
		std::cout << SUCCESS << "Gift cards loaded successfully from " << filePath << "." << RESET << std::endl;
	}
}

const String LoadGiftCardsCommand::getName() const
{
	return String("load-gift-cards");
}

bool LoadGiftCardsCommand::canExecute(Role role, bool isAuthenticated) const
{
	return role == Role::Manager && isAuthenticated;
}

void LoadGiftCardsCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "<filepath>");
}
