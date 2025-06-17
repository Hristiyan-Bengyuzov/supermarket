#pragma once
#include "GiftCard.h"

class AllProductsGiftCard : public GiftCard {
public:
	AllProductsGiftCard() = default;
	AllProductsGiftCard(ushort percentage);
	GiftCardType getType() const override;
	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
};