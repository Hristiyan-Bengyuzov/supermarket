#include "ProductService.h"

ProductService::ProductService(ProductRepository& productRepo) : productRepo(productRepo)
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
