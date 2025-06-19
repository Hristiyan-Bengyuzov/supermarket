#pragma once
#include "Command.h"
#include "ProductService.h"

class ListProductsCommand : public Command {
private:
	ProductService& productService;

public:
	ListProductsCommand(ProductService& productService);
	void execute(const Vector<String> args, size_t employeeId) override;
	const String getName() const override;
	bool canExecute(Role role, bool isAuthenticated) const override;
	void showHelp() const override;
};