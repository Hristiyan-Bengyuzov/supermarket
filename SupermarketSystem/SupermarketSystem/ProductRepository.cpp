#include "ProductRepository.h"

bool ProductRepository::loadData()
{
	if (!file.c_str())
		return false;

	std::ifstream in(file.c_str(), std::ios::binary | std::ios::in);
	if (!in.is_open())
		return false;

	items.clear();

	size_t count;
	in.read(reinterpret_cast<char*>(&count), sizeof(count));

	for (size_t i = 0; i < count; ++i) {
		ProductType type;
		in.read(reinterpret_cast<char*>(&type), sizeof(ProductType));

		SharedPtr<Product> product;
		switch (type) {
		case ProductType::ByUnit:
			product = SharedPtr<Product>(new ProductByUnit());
			break;
		case ProductType::ByWeight:
			product = SharedPtr<Product>(new ProductByWeight());
			break;
		default:
			continue;
		}

		product->deserialize(in);
		items.push_back(product);
	}

	return true;
}

ProductRepository::ProductRepository() : Repository("products.bin")
{
	loadData();
}

bool ProductRepository::hasProductWithCategory(size_t categoryId) const
{
	auto products = getAll();
	for (size_t i = 0; i < products.getSize(); i++)
	{
		if (products[i]->getCategoryId() == categoryId)
			return true;
	}
	return false;
}
