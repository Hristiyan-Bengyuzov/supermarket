#pragma once

#include "String.h"
#include "Vector.hpp"
#include "SharedPtr.hpp"
#include <fstream>

template <typename T>
class Repository {
protected:
	Vector<SharedPtr<T>> items;
	String file;

public:
	explicit Repository(const String& file) : file(file) {}

	virtual ~Repository() {
		saveChanges();
	}

	void add(T* item) {
		items.push_back(SharedPtr<T>(item));
	}

	void add(const T& item) {
		items.push_back(SharedPtr<T>(new T(item)));
	}

	bool removeById(size_t id) {
		for (size_t i = 0; i < items.getSize(); ++i) {
			if (items[i] && items[i]->getId() == id) {
				items.remove(i);
				return true;
			}
		}
		return false;
	}

	bool editById(size_t id, const T& newData) {
		SharedPtr<T> item = findById(id);
		if (item) {
			*item = newData;
			return true;
		}
		return false;
	}

	SharedPtr<T> findById(size_t id) const {
		for (size_t i = 0; i < items.getSize(); ++i) {
			if (items[i] && items[i]->getId() == id) {
				return items[i];
			}
		}
		return SharedPtr<T>();
	}

	SharedPtr<T> findByName(const String& name) const {
		for (size_t i = 0; i < items.getSize(); ++i) {
			if (items[i] && items[i]->getName() == name) {
				return items[i];
			}
		}
		return SharedPtr<T>();
	}

	const Vector<SharedPtr<T>>& getAll() const {
		return items;
	}

	void clear() {
		items.clear();
	}

	size_t count() const {
		return items.getSize();
	}

	bool saveChanges() const {
		if (!file.c_str())
			return false;

		std::ofstream out(file.c_str(), std::ios::binary | std::ios::out);

		if (!out.is_open())
			return false;

		size_t count = items.getSize();
		out.write((const char*)&count, sizeof(count));

		for (size_t i = 0; i < count; ++i) {
			if (items[i]) {
				items[i]->serialize(out);
			}
		}

		return true;
	}
};
