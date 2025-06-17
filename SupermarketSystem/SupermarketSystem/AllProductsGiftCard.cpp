#include "AllProductsGiftCard.h"

AllProductsGiftCard::AllProductsGiftCard(ushort percentage) : GiftCard(percentage)
{
}

GiftCardType AllProductsGiftCard::getType() const
{
	return GiftCardType::All;
}
