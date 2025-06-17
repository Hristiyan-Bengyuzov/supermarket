#include "MultipleCategoryGiftCard.h"

MultipleCategoryGiftCard::MultipleCategoryGiftCard(ushort percentage, const Vector<size_t>& categoryIds) : GiftCard(percentage)
{
	this->categoryIds = categoryIds;
}

GiftCardType MultipleCategoryGiftCard::getType() const
{
	return GiftCardType::Multiple;
}

void MultipleCategoryGiftCard::addCategoryId(size_t id)
{
	categoryIds.push_back(id);
}

void MultipleCategoryGiftCard::serialize(std::ofstream& ofs) const
{
	GiftCardType type = getType();
	ofs.write(reinterpret_cast<const char*>(&type), sizeof(GiftCardType));
	GiftCard::serialize(ofs);

	size_t categoriesSize = categoryIds.getSize();
	ofs.write(reinterpret_cast<const char*>(&categoriesSize), sizeof(size_t));
	for (size_t i = 0; i < categoriesSize; i++)
		ofs.write(reinterpret_cast<const char*>(&categoryIds[i]), sizeof(size_t));
}

void MultipleCategoryGiftCard::deserialize(std::ifstream& ifs)
{
	GiftCard::deserialize(ifs);

	size_t categoriesSize = 0;
	ifs.read(reinterpret_cast<char*>(&categoriesSize), sizeof(size_t));
	categoryIds.clear();

	for (size_t i = 0; i < categoriesSize; i++) {
		size_t categoryId;
		ifs.read(reinterpret_cast<char*>(&categoryId), sizeof(size_t));
		addCategoryId(categoryId);
	}
}
