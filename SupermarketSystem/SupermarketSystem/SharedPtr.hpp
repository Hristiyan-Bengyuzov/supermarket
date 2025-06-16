#pragma once

template <typename T>
class SharedPtr {
	T* ptr;
	size_t* refsCount;

public:
	SharedPtr() : ptr(nullptr), refsCount(nullptr) {};

	explicit SharedPtr(T* ptr) : ptr(ptr), refsCount(ptr ? new size_t(1) : nullptr) {};

	SharedPtr(const SharedPtr& other) : ptr(other.ptr), refsCount(other.refsCount) {
		if (refsCount) {
			(*refsCount)++;
		}
	}

	SharedPtr& operator=(const SharedPtr& other) {
		if (this != &other) {
			removeExistingReference();

			ptr = other.ptr;
			refsCount = other.refsCount;

			if (refsCount) {
				(*refsCount)++;
			}
		}
		return *this;
	}

	template <typename U>
	friend class SharedPtr;

	template <typename U>
	SharedPtr(const SharedPtr<U>& other)
		: ptr(dynamic_cast<T*>(other.ptr)),
		refsCount(other.refsCount)
	{
		if (refsCount) {
			(*refsCount)++;
		}
	}

	template <typename U>
	SharedPtr<T>& operator=(const SharedPtr<U>& other) {
		if (static_cast<void*>(this) != static_cast<const void*>(&other)) {
			removeExistingReference();

			ptr = dynamic_cast<T*>(other.ptr);
			refsCount = other.refsCount;

			if (refsCount) {
				(*refsCount)++;
			}
		}
		return *this;
	}

	~SharedPtr() {
		removeExistingReference();
	}

	T& operator*() const {
		return *ptr;
	}

	T* operator->() const {
		return ptr;
	}

	T* get() const {
		return ptr;
	}

	size_t use_count() const {
		return refsCount ? *refsCount : 0;
	}

	explicit operator bool() const {
		return ptr != nullptr;
	}

private:
	void removeExistingReference() {
		if (refsCount) {
			(*refsCount)--;
			if (*refsCount == 0) {
				delete ptr;
				delete refsCount;
			}
		}
	}
};