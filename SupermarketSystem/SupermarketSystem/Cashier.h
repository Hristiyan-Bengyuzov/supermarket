#pragma once
#include "Vector.hpp"
#include "Employee.h"

class Cashier : public Employee {
private:
	size_t transactionsMade = 0;
	Vector<size_t> warningIds;

public:
	Cashier() = default;
	Cashier(const String& name, const String& familyName, const String& phoneNumber, unsigned age, const String& plainPass);

	void addWarningId(size_t warningId);
};