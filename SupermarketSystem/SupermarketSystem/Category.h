#pragma once
#include "String.h"
#include "Serializable.h"

static size_t categoryCounter = 0;
class Category : public Serializable {
private:
	size_t id = 0;
	String name = "";
	String description = "";

public:
	Category() = default;
	Category(const String& name, const String& description);

	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
};