#include "SingleCategoryGiftCard.h"

SingleCategoryGiftCard::SingleCategoryGiftCard(ushort percentage, size_t categoryId) : GiftCard(percentage)
{
	this->categoryId = categoryId;
}

GiftCardType SingleCategoryGiftCard::getType() const
{
	return	GiftCardType::Single;
}
