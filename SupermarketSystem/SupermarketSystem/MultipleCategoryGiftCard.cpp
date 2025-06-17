#include "MultipleCategoryGiftCard.h"

MultipleCategoryGiftCard::MultipleCategoryGiftCard(ushort percentage, const Vector<size_t>& categoryIds) : GiftCard(percentage)
{
	this->categoryIds = categoryIds;
}

GiftCardType MultipleCategoryGiftCard::getType() const
{
	return GiftCardType::Multiple;
}
