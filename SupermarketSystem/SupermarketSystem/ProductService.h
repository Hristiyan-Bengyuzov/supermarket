#pragma once
#include "ProductRepository.h"
#include "CategoryRepository.h"

class ProductService {
private:
	ProductRepository& productRepo;
	CategoryRepository& categoryRepo;

public:
	ProductService(ProductRepository& productRepo, CategoryRepository& categoryRepo);

	void listProducts(std::ostream& os) const;
	void listProductByCategory(std::ostream& os, size_t categoryId) const;
};