#include "AddProductCommand.h"

AddProductCommand::AddProductCommand(ManagerService& managerService) : managerService(managerService)
{
}

void AddProductCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() != 2)
	{
		showHelp();
		return;
	}

	ProductType productType = Product::getType(args[1]);
	String productName = String::readLineNotEmpty("Enter product name: ");
	String category = String::readLineNotEmpty("Enter product category: ");
	double price = String::readLineNotEmpty("Enter product price: ").toDouble();
	const char* message = (productType == ProductType::ByUnit) ? "Enter quantity (units): " : "Enter quantity (kg): ";
	double quantity = String::readLineNotEmpty(message).toDouble();
	CreateProductDTO dto = { productType, productName, category, price, quantity };
	if (managerService.addProduct(dto))
	{
		std::cout << SUCCESS << "Successfully added product" << RESET << std::endl;
	}
}

const String AddProductCommand::getName() const
{
	return String("add-product");
}

bool AddProductCommand::canExecute(Role role, bool isAuthenticated) const
{
	return role == Role::Manager && isAuthenticated;
}

void AddProductCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "<product_type>");
}
