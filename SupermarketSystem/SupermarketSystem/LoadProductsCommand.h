#pragma once
#include "Command.h"
#include "ManagerService.h"
#include "LogService.h"

class LoadProductsCommand : public Command {
private:
	ManagerService& managerService;
	LogService& logService;

public:
	LoadProductsCommand(ManagerService& managerService, LogService& logService);
	void execute(const Vector<String> args, size_t employeeId) override;
	const String getName() const override;
	bool canExecute(Role role, bool isAuthenticated) const override;
	void showHelp() const override;
};