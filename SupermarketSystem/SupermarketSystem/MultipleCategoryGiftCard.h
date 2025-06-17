#pragma once
#include "GiftCard.h"

class MultipleCategoryGiftCard : public GiftCard {
private:
	Vector<size_t> categoryIds;

public:
	MultipleCategoryGiftCard() = default;
	MultipleCategoryGiftCard(ushort percentage, const Vector<size_t>& categoryIds);
	GiftCardType getType() const override;
	void addCategoryId(size_t id);
	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
};