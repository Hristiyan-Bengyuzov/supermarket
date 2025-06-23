#include "CashierService.h"

void CashierService::saveToFile(Transaction& transaction) const
{
	String fileName = "receipt_" + String::parseFrom(transaction.getId()) + ".txt";
	std::ofstream ofs(fileName.c_str());
	if (!ofs.is_open())
		throw std::runtime_error("Could not open file for saving receipt");
	ofs << "Receipt" << std::endl;
	ofs << "Transaction ID: " << transaction.getId() << std::endl;
	ofs << "Cashier ID: " << transaction.getCashierId() << std::endl;
	ofs << "Date: " << transaction.getDate() << std::endl;
	ofs << "------------------------" << std::endl;
	auto items = transaction.getItemsMutable();
	for (size_t i = 0; i < items.getSize(); i++)
	{
		ofs << productRepo.getNameById(items[i].productId) << std::endl;
		ofs << items[i].quantityOrWeight << " * " << items[i].price << " - " << items[i].total << std::endl;
		ofs << "###" << std::endl;
	}

	ofs << "TOTAL: " << transaction.getTotalPrice() << std::endl;
	ofs.close();
}

void CashierService::applyGiftCardDiscount(Transaction& transaction, const String& giftCardCode)
{
	SharedPtr<GiftCard> giftCard = giftCardRepo.findByCode(giftCardCode);
	if (!giftCard)
		throw std::runtime_error("Giftcard not found");

	Vector<TransactionItem>& transactionItems = transaction.getItemsMutable();
	switch (giftCard->getType())
	{
	case GiftCardType::Single:
		applySingleCategoryDiscount(transactionItems, giftCard);
		break;
	case GiftCardType::Multiple:
		applyMultipleCategoryDiscount(transactionItems, giftCard);
		break;
	case GiftCardType::All:
		applyAllProductsDiscount(transactionItems, giftCard);
		break;
	default:
		throw std::runtime_error("Unknown gift card type");
	}

	transaction.calculateTotalPrice();
}

void CashierService::applySingleCategoryDiscount(Vector<TransactionItem>& transactionItems, const SharedPtr<GiftCard>& giftCard)
{
	SharedPtr<SingleCategoryGiftCard> singleCard(giftCard);
	if (!singleCard)
		throw std::runtime_error("Invalid giftcard type");

	for (size_t i = 0; i < transactionItems.getSize(); i++)
	{
		SharedPtr<Product> product = productRepo.findById(transactionItems[i].productId);
		if (!product)
			throw std::runtime_error("Product not found");
		if (product->getCategoryId() == singleCard->getCategoryId())
		{
			transactionItems[i].applyDiscount(singleCard->getPercentage());
		}
	}

}

void CashierService::applyMultipleCategoryDiscount(Vector<TransactionItem>& transactionItems, const SharedPtr<GiftCard>& giftCard)
{
	SharedPtr<MultipleCategoryGiftCard> multipleCard(giftCard);
	if (!multipleCard)
		throw std::runtime_error("Invalid giftcard type");

	const Vector<size_t>& categoryIds = multipleCard->getCategoryIds();

	for (size_t i = 0; i < transactionItems.getSize(); i++)
	{
		SharedPtr<Product> product = productRepo.findById(transactionItems[i].productId);
		if (!product)
			throw std::runtime_error("Product not found");

		for (size_t j = 0; j < categoryIds.getSize(); j++)
		{
			if (product->getCategoryId() == categoryIds[j])
			{
				transactionItems[i].applyDiscount(multipleCard->getPercentage());
				break;
			}
		}
	}
}

void CashierService::applyAllProductsDiscount(Vector<TransactionItem>& transactionItems, const SharedPtr<GiftCard>& giftCard)
{
	SharedPtr<AllProductsGiftCard> allCard(giftCard);
	if (!allCard)
		throw std::runtime_error("Invalid giftcard type");
	for (size_t i = 0; i < transactionItems.getSize(); i++)
	{
		transactionItems[i].applyDiscount(allCard->getPercentage());
	}
}

CashierService::CashierService(EmployeeRepository& employeeRepo, ProductRepository& productRepo, GiftCardRepository& giftCardRepo, TransactionRepository& transactionRepo, WarningRepository& warningRepo) : employeeRepo(employeeRepo), productRepo(productRepo), giftCardRepo(giftCardRepo), transactionRepo(transactionRepo), warningRepo(warningRepo)
{
}

bool CashierService::sell(size_t cashierId, Transaction& transaction, const String& giftCardCode)
{
	SharedPtr<Employee> cashierEmp = employeeRepo.findById(cashierId);
	if (!cashierEmp || cashierEmp->getRole() != Role::Cashier)
		throw std::runtime_error("Invalid cashier");

	SharedPtr<Cashier> cashier = SharedPtr<Cashier>(cashierEmp);

	if (giftCardCode != "")
	{
		applyGiftCardDiscount(transaction, giftCardCode);
	}

	transactionRepo.add(transaction);
	cashier->completeTransaction();
	saveToFile(transaction);
	if (cashier->getTransactionsMade() % 3 == 0)
	{
		int lastId = cashier->removeLastWarning();
		if (lastId != -1)
			warningRepo.removeById(lastId);
	}

	return employeeRepo.saveChanges() && warningRepo.saveChanges() && transactionRepo.saveChanges();
}

