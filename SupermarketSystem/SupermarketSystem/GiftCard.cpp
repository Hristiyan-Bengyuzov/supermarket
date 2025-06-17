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

GiftCardType GiftCard::getType(const String& str)
{
	if (str == "single") return GiftCardType::Single;
	if (str == "multiple") return GiftCardType::Multiple;
	if (str == "all") return GiftCardType::All;
	throw std::runtime_error("Invalid giftcard type");
}

ushort GiftCard::getPercentage() const
{
	return percentage;
}

size_t GiftCard::getId() const
{
	return id;
}

void GiftCard::serialize(std::ofstream& ofs) const
{
	ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));
	code.serialize(ofs);
	ofs.write(reinterpret_cast<const char*>(&percentage), sizeof(ushort));
}

void GiftCard::deserialize(std::ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&id), sizeof(id));
	if (id >= giftCardCounter)
		giftCardCounter = id + 1;

	code.deserialize(ifs);
	ifs.read(reinterpret_cast<char*>(&percentage), sizeof(ushort));
}
