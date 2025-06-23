#include "SellCommand.h"

SellCommand::SellCommand(CashierService& cashierService, ProductService& productService, LogService& logService) : cashierService(cashierService), productService(productService), logService(logService)
{
}

void SellCommand::execute(const Vector<String> args, size_t employeeId)
{
	Transaction transaction(employeeId);
	transaction.print(std::cout);

	while (true) {
		productService.listProducts(std::cout);

		String input = String::readLineNotEmpty("Enter product ID to sell. Enter END to end the transaction: > ");
		if (input == "END") {
			break;
		}

		size_t productId = input.toSizeT();
		double quantity = String::readLineNotEmpty("Enter quantity: > ").toDouble();
		double price = productService.getPriceById(productId);
		TransactionItem item(productId, quantity, price);
		transaction.addItem(item);
		productService.decreaseQuantity(productId, quantity);
		transaction.print(std::cout);
	}

	String voucherResponse = String::readLineNotEmpty("Add voucher: (Y/N)? ");
	String voucher = "";
	if (voucherResponse == "Y")
		voucher = String::readLineNotEmpty("Enter voucher: ");

	if (cashierService.sell(employeeId, transaction, voucher)) {
		logService.log(employeeId, "Cashier with id " + String::parseFrom(employeeId) + " completed a transaction");
		std::cout << "Transaction complete!\n";
		std::cout << "Receipt saved as: receipt_" << transaction.getId() << ".txt\n";
		std::cout << "Total: " << transaction.getTotalPrice() << " lv.\n";
	}
}

const String SellCommand::getName() const
{
	return String("sell");
}

bool SellCommand::canExecute(Role role, bool isAuthenticated) const
{
	return isAuthenticated && role == Role::Cashier;
}

void SellCommand::showHelp() const
{
	CommandUtils::printCommandWithArgs(getName(), "");
}
