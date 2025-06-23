#pragma once
#include "EmployeeRepository.h"
#include "ProductRepository.h"
#include "GiftCardRepository.h"
#include "TransactionRepository.h"
#include "WarningRepository.h"


class CashierService {
private:
	EmployeeRepository& employeeRepo;
	ProductRepository& productRepo;
	GiftCardRepository& giftCardRepo;
	TransactionRepository& transactionRepo;
	WarningRepository& warningRepo;

	void saveToFile(Transaction& transaction) const;
	void applyGiftCardDiscount(Transaction& transaction, const String& giftCardCode);
	void applySingleCategoryDiscount(Vector<TransactionItem>& transactionItems, const SharedPtr<GiftCard>& giftCard);
	void applyMultipleCategoryDiscount(Vector<TransactionItem>& transactionItems, const SharedPtr<GiftCard>& giftCard);
	void applyAllProductsDiscount(Vector<TransactionItem>& transactionItems, const SharedPtr<GiftCard>& giftCard);
public:
	CashierService(EmployeeRepository& employeeRepo, ProductRepository& productRepo, GiftCardRepository& giftCardRepo, TransactionRepository& transactionRepo, WarningRepository& warningRepo);
	bool sell(size_t cashierId, Transaction& transaction, const String& giftCardCode = "");
};