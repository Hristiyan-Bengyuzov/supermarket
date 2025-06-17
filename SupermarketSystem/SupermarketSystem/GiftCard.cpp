#include "GiftCard.h"

String GiftCard::generateCode() const
{
	String res = 0;
	res += GenUtils::genDigit();
	res += GenUtils::genUpper();
	res += String::parseFrom(id);
	res += GenUtils::genUpper();
	res += GenUtils::genDigit();
	return res;
}

GiftCard::GiftCard(ushort percentage)
{
	this->id = giftCardCounter++;
	this->percentage = percentage;
	this->code = generateCode();
}

size_t GiftCard::getId() const
{
	return id;
}
