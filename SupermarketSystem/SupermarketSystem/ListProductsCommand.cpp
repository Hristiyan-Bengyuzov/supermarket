#include "ListProductsCommand.h"

ListProductsCommand::ListProductsCommand(ProductService& productService) : productService(productService)
{
}

void ListProductsCommand::execute(const Vector<String> args, size_t employeeId)
{
	if (args.getSize() > 2)
	{
		showHelp();
		return;
	}

	if (args.getSize() == 1)
	{
		productService.listProducts(std::cout);
	}
	else if (args.getSize() == 2)
	{
		size_t categoryId = args[1].toSizeT();
		productService.listProductByCategory(std::cout, categoryId);
	}
}

const String ListProductsCommand::getName() const
{
	return String("list-products");
}

bool ListProductsCommand::canExecute(Role role, bool isAuthenticated) const
{
	return isAuthenticated;
}

void ListProductsCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "[category_id]");
}

