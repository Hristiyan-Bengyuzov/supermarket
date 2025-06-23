#pragma once
#include "Command.h"
#include "CashierService.h"
#include "ProductService.h"

class SellCommand : public Command {
private:
	CashierService& cashierService;
	ProductService& productService;

public:
	SellCommand(CashierService& cashierService, ProductService& productService);
	void execute(const Vector<String> args, size_t employeeId) override;
	const String getName() const override;
	bool canExecute(Role role, bool isAuthenticated) const override;
	void showHelp() const override;
};