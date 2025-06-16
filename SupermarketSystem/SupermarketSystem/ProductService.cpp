#include "ProductService.h"

ProductService::ProductService(ProductRepository& productRepo, CategoryRepository& categoryRepo) : productRepo(productRepo), categoryRepo(categoryRepo)
{
}

void ProductService::listProducts(std::ostream& os) const
{
	if (productRepo.count() == 0)
		throw std::runtime_error("No products in the store");

	auto products = productRepo.getAll();
	os << "Products: " << std::endl;
	for (size_t i = 0; i < products.getSize(); i++)
	{
		products[i]->print(os);
	}
}

// i know i can use lambda function but i'm too lazy to refactor
void ProductService::listProductByCategory(std::ostream& os, size_t categoryId) const
{
	if (productRepo.count() == 0)
		throw std::runtime_error("No products in the store");

	if (!categoryRepo.findById(categoryId))
		throw std::runtime_error("Category not found");

	auto products = productRepo.getAll();
	os << "Products: " << std::endl;
	for (size_t i = 0; i < products.getSize(); i++)
	{
		if (products[i]->getCategoryId() == categoryId)
		{
			products[i]->print(os);
		}
	}
}
