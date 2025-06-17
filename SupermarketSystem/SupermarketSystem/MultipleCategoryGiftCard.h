#pragma once
#include "GiftCard.h"

class MultipleCategoryGiftCard : public GiftCard {
private:
	Vector<size_t> categoryIds;

public:
	MultipleCategoryGiftCard() = default;
	MultipleCategoryGiftCard(ushort percentage, const Vector<size_t>& categoryIds);
	GiftCardType getType() const override;
};