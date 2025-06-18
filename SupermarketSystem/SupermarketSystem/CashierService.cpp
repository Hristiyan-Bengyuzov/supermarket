#include "CashierService.h"

void CashierService::applyGiftCardDiscount(Transaction& transaction, const String& giftCardCode)
{
	SharedPtr<GiftCard> giftCard = giftCardRepo.findByCode(giftCardCode);
	if (!giftCard)
		throw std::runtime_error("Giftcard not found");

	auto transactionItems = transaction.getItemsMutable();
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

	auto categoryIds = multipleCard->getCategoryIds();

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

	if (giftCardCode!="")
	{
		applyGiftCardDiscount(transaction, giftCardCode);
	}

	transactionRepo.add(transaction);
	cashier->completeTransaction();
	if (cashier->getTransactionsMade() % 3 == 0)
	{
		size_t lastId = (size_t)cashier->removeLastWarning();
		if (lastId != -1)
			warningRepo.removeById(lastId);
	}

	return employeeRepo.saveChanges() && warningRepo.saveChanges() && transactionRepo.saveChanges();
}

