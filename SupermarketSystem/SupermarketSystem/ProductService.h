#pragma once
#include "ProductRepository.h"
#include "CategoryRepository.h"

class ProductService {
private:
	ProductRepository& productRepo;
	CategoryRepository& categoryRepo;

public:
	ProductService(ProductRepository& productRepo, CategoryRepository& categoryRepo);

	double getPriceById(size_t productId) const;
	void listProducts(std::ostream& os) const;
	void listProductByCategory(std::ostream& os, size_t categoryId) const;
	void decreaseQuantity(size_t productId, double quantityOrWeight);
};