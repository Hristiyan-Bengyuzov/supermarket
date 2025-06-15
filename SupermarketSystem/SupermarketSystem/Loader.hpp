#pragma once
#include "String.h"
#include "Vector.hpp"
#include "SharedPtr.hpp"

template<typename T>
bool load(const String& file, Vector<SharedPtr<T>>& items)
{
	if (!file.c_str())
		return false;

	std::ifstream in(file.c_str(), std::ios::binary | std::ios::in);

	if (!in.is_open())
		return false;

	items.clear();

	size_t count;
	in.read((char*)&count, sizeof(count));

	for (size_t i = 0; i < count; ++i) {
		SharedPtr<T> item(new T());
		item->deserialize(in);
		items.push_back(item);
	}

	return true;
}