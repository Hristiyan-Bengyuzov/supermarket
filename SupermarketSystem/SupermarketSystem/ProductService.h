#pragma once
#include "ProductRepository.h"

class ProductService {
private:
	ProductRepository& productRepo;

public:
	ProductService(ProductRepository& productRepo);

	void listProducts(std::ostream& os) const;
};