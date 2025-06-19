#pragma once
#include "String.h"
#include "Vector.hpp"
#include "Employee.h"
#include "CommandUtils.h"
#include "Constants.h"

using namespace Constants;

class Command {
public:
	virtual void execute(const Vector<String> args, size_t employeeId = 0) = 0;
	virtual const String getName() const = 0;
	virtual bool canExecute(Role role, bool isAuthenticated) const = 0;
	virtual void showHelp() const = 0;
	virtual ~Command() = default;
};