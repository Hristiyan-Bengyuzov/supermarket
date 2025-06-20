#pragma once
#include "Command.h"
#include "ManagerService.h"

class DeclineCommand : public Command {
private:
	ManagerService& managerService;

public:
	DeclineCommand(ManagerService& managerService);
	void execute(const Vector<String> args, size_t employeeId) override;
	const String getName() const override;
	bool canExecute(Role role, bool isAuthenticated) const override;
	void showHelp() const override;
};