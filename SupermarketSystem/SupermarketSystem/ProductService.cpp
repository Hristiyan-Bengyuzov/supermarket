#include "ProductService.h"
#include "Constants.h"

using namespace Constants;

ProductService::ProductService(ProductRepository& productRepo, CategoryRepository& categoryRepo) : productRepo(productRepo), categoryRepo(categoryRepo)
{
}

double ProductService::getPriceById(size_t productId) const
{
	auto product = productRepo.findById(productId);
	if (!product)
		throw std::runtime_error("Product not found");
	return product->getPrice();
}

void ProductService::listProducts(std::ostream& os) const
{
	if (productRepo.count() == 0)
		throw std::runtime_error("No products in the store");

	const Vector<SharedPtr<Product>>& products = productRepo.getAll();
	os << std::endl << HEADER << "Products: " << RESET << std::endl;
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

	const Vector<SharedPtr<Product>>& products = productRepo.getAll();
	os << std::endl << HEADER << "Products: " << RESET << std::endl;
	for (size_t i = 0; i < products.getSize(); i++)
	{
		if (products[i]->getCategoryId() == categoryId)
		{
			products[i]->print(os);
		}
	}
}

void ProductService::decreaseQuantity(size_t productId, double quantityOrWeight)
{
	SharedPtr<Product> product = productRepo.findById(productId);
	if (!product)
		throw std::runtime_error("Product not found");
	product->sell(quantityOrWeight);
	productRepo.saveChanges();
}
