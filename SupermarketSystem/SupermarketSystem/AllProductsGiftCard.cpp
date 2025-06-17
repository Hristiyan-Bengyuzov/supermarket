#include "AllProductsGiftCard.h"

AllProductsGiftCard::AllProductsGiftCard(ushort percentage) : GiftCard(percentage)
{
}

GiftCardType AllProductsGiftCard::getType() const
{
	return GiftCardType::All;
}

void AllProductsGiftCard::serialize(std::ofstream& ofs) const
{
	GiftCardType type = getType();
	ofs.write(reinterpret_cast<const char*>(&type), sizeof(GiftCardType));
	GiftCard::serialize(ofs);
}

void AllProductsGiftCard::deserialize(std::ifstream& ifs)
{
	GiftCard::deserialize(ifs);
}
