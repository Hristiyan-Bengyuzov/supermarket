#pragma once
#include "String.h"
#include "GenUtils.h"

enum class GiftCardType {
	Single,
	Multiple,
	All
};

typedef unsigned short ushort;

static size_t giftCardCounter = 0;
class GiftCard {
private:
	size_t id = 0;
	String code = "";
	ushort percentage = 0;
	String generateCode() const;

public:
	GiftCard() = default;
	GiftCard(ushort percentage);
	virtual ~GiftCard() = default;
	virtual GiftCardType getType() const = 0;

	size_t getId() const;
};