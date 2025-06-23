#pragma once
#include "Command.h"
#include "EmployeeService.h"
#include "LogService.h"

class LeaveCommand : public Command {
private:
	EmployeeService& employeeService;
	LogService& logService;

public:
	LeaveCommand(EmployeeService& employeeService, LogService& logService);
	void execute(const Vector<String> args, size_t employeeId) override;
	const String getName() const override;
	bool canExecute(Role role, bool isAuthenticated) const override;
	void showHelp() const override;
};