#pragma once
#include "Command.h"
#include "ManagerService.h"
#include "LogService.h"

class LoadGiftCardsCommand : public Command {
private:
	ManagerService& managerService;
	LogService& logService;

public:
	LoadGiftCardsCommand(ManagerService& managerService, LogService& logService);
	void execute(const Vector<String> args, size_t employeeId) override;
	const String getName() const override;
	bool canExecute(Role role, bool isAuthenticated) const override;
	void showHelp() const override;
};