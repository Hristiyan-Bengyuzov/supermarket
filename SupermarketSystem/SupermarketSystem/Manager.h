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

	// constructor used for promotion
	Manager(size_t id, const String& name, const String& familyName, const String& phoneNumber, unsigned age, const Password& pass);

	Role getRole() const override;

	const String& getSpecialCode() const;

	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
	void print(std::ostream& os) const override;
};