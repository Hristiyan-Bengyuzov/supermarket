#pragma once
#include "Command.h"
#include "Authservice.h"

class RegisterCommand : public Command {
private:
	AuthService& authService;

public:
	RegisterCommand(AuthService& authService);
	void execute(const Vector<String> args, size_t employeeId) override;
	const String getName() const override;
	bool canExecute(Role role, bool isAuthenticated) const override;
	void showHelp() const override;
};