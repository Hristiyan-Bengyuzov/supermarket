#pragma once
#include "Repository.hpp"
#include "GiftCard.h"
#include "SingleCategoryGiftCard.h"
#include "MultipleCategoryGiftCard.h"
#include "AllProductsGiftCard.h"

class GiftCardRepository : public Repository<GiftCard> {
	bool loadData();
public:
	GiftCardRepository();
};