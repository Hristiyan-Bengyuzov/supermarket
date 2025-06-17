#pragma once
#include "GiftCard.h"

class SingleCategoryGiftCard : public GiftCard {
private:
	size_t categoryId = 0;

public:
	SingleCategoryGiftCard() = default;
	SingleCategoryGiftCard(ushort percentage, size_t categoryId);
	GiftCardType getType() const override;
	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
};