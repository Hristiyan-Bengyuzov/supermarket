#pragma once
#include "Command.h"
#include "ManagerService.h"

class ListPendingCommand : public Command {
private:
	ManagerService& managerService;

public:
	ListPendingCommand(ManagerService& managerService);
	void execute(const Vector<String> args, size_t employeeId) override;
	const String getName() const override;
	bool canExecute(Role role, bool isAuthenticated) const override;
	void showHelp() const override;
};