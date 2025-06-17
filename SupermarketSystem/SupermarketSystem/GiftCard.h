#pragma once
#include "String.h"
#include "GenUtils.h"
#include "Serializable.h"

enum class GiftCardType {
	Single,
	Multiple,
	All
};

typedef unsigned short ushort;

static size_t giftCardCounter = 0;
class GiftCard : public  Serializable {
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
	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
};