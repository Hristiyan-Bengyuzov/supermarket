#pragma once
#include "Employee.h"

class Manager : public Employee {
private:
	String specialCode = "";
	String generateSpecialCode() const;
	void saveCodeToFile() const;

public:
	Manager() = default;
	Manager(const String& name, const String& familyName, const String& phoneNumber, unsigned age, const String& plainPass);
	Role getRole() const override;

	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
};