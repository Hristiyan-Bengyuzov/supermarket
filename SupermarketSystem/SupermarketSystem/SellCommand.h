#pragma once
#include "Command.h"
#include "CashierService.h"
#include "ProductService.h"
#include "LogService.h"

class SellCommand : public Command {
private:
	CashierService& cashierService;
	ProductService& productService;
	LogService& logService;

public:
	SellCommand(CashierService& cashierService, ProductService& productService, LogService& logService);
	void execute(const Vector<String> args, size_t employeeId) override;
	const String getName() const override;
	bool canExecute(Role role, bool isAuthenticated) const override;
	void showHelp() const override;
};