#pragma once
#include "Command.h"
#include "EmployeeService.h"

class ListFeedCommand : public Command {
private:
	EmployeeService& employeeService;

public:
	ListFeedCommand(EmployeeService& authService);
	void execute(const Vector<String> args, size_t employeeId) override;
	const String getName() const override;
	bool canExecute(Role role, bool isAuthenticated) const override;
	void showHelp() const override;
};