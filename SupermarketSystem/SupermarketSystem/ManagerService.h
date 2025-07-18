#pragma once
#include "EmployeeRepository.h"
#include "ProductRepository.h"
#include "CategoryRepository.h"
#include "RegisterRequestRepository.h"
#include "GiftCardRepository.h"
#include "WarningRepository.h"
#include "CreateWarningDTO.h"
#include "CreateCategoryDTO.h"
#include "CreateProductDTO.h"
#include "LoadProductDTO.h"

class ManagerService {
private:
	EmployeeRepository& employeeRepo;
	ProductRepository& productRepo;
	CategoryRepository& categoryRepo;
	RegisterRequestRepository& requestRepo;
	WarningRepository& warningRepo;
	GiftCardRepository& giftCardRepo;

public:
	ManagerService(EmployeeRepository& employeeRepo, ProductRepository& productRepo, CategoryRepository& categoryRepo, RegisterRequestRepository& requestRepo, WarningRepository& warningRepo, GiftCardRepository& giftCardRepo);

	void listPending(std::ostream& os) const;
	bool approve(size_t managerId, size_t requestId, const String& specialCode);
	bool decline(size_t managerId, size_t requestId, const String& specialCode);
	void listWarnedCashiers(std::ostream& os, unsigned points) const;
	bool warnCashier(const CreateWarningDTO& dto);
	bool promoteCashier(size_t managerId, size_t cashierId, const String& specialCode);
	bool fireCashier(size_t managerId, size_t cashierId, const String& specialCode);
	bool addCategory(const CreateCategoryDTO& dto);
	bool deleteCategory(size_t categoryId);
	bool addProduct(const CreateProductDTO& dto);
	bool loadProduct(const LoadProductDTO& dto);
	bool deleteProduct(size_t productId);
	bool loadProducts(const String& file);
	bool loadGiftCards(const String& file);
};