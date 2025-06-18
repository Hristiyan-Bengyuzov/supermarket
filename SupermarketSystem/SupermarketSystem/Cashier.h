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

	int removeLastWarning();
	void addWarningId(size_t warningId);
	Role getRole() const override;
	void completeTransaction();
	size_t getTransactionsMade() const;
	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
	void print(std::ostream& os) const override;
};