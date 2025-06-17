#include "GiftCardRepository.h"

bool GiftCardRepository::loadData()
{
	if (!file.c_str())
		return false;

	std::ifstream in(file.c_str(), std::ios::binary | std::ios::in);
	if (!in.is_open())
		return false;

	items.clear();

	size_t count;
	in.read(reinterpret_cast<char*>(&count), sizeof(count));

	for (size_t i = 0; i < count; ++i) {
		GiftCardType type;
		in.read(reinterpret_cast<char*>(&type), sizeof(GiftCardType));

		SharedPtr<GiftCard> giftcard;
		switch (type) {
		case GiftCardType::Single: giftcard = SharedPtr<GiftCard>(new SingleCategoryGiftCard()); break;
		case GiftCardType::Multiple: giftcard = SharedPtr<GiftCard>(new MultipleCategoryGiftCard()); break;
		case GiftCardType::All: giftcard = SharedPtr<GiftCard>(new AllProductsGiftCard()); break;
		default: continue;
		}

		giftcard->deserialize(in);
		items.push_back(giftcard);
	}

	return true;
}

GiftCardRepository::GiftCardRepository() : Repository("giftcards.bin")
{
	loadData();
}
