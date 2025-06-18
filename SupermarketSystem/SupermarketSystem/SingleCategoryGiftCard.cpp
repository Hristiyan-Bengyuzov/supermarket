#include "SingleCategoryGiftCard.h"

SingleCategoryGiftCard::SingleCategoryGiftCard(ushort percentage, size_t categoryId) : GiftCard(percentage)
{
	this->categoryId = categoryId;
}

GiftCardType SingleCategoryGiftCard::getType() const
{
	return	GiftCardType::Single;
}

size_t SingleCategoryGiftCard::getCategoryId() const
{
	return categoryId;
}

void SingleCategoryGiftCard::serialize(std::ofstream& ofs) const
{
	GiftCardType type = getType();
	ofs.write(reinterpret_cast<const char*>(&type), sizeof(GiftCardType));
	GiftCard::serialize(ofs);
	ofs.write(reinterpret_cast<const char*>(&categoryId), sizeof(size_t));
}

void SingleCategoryGiftCard::deserialize(std::ifstream& ifs)
{
	GiftCard::deserialize(ifs);
	ifs.read(reinterpret_cast<char*>(&categoryId), sizeof(size_t));
}
