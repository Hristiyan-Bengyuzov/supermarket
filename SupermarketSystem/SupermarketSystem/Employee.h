#pragma once
#include "String.h"
#include "Password.h"

enum class Role {
	Cashier,
	Manager
};

static size_t counter = 0;
class Employee : public Serializable {
protected:
	size_t id = 0;
	String name = "";
	String familyName = "";
	String phoneNumber = "";
	unsigned age = 0;
	Password password;

public:
	Employee();
	Employee(const String& name, const String& familyName, const String& phoneNumber, unsigned age, const String& plainPass);
	void setName(const String& name);
	void setFamilyName(const String& familyName);
	void setPhoneNumber(const String& phoneNumber);
	void setAge(unsigned age);

	virtual Role getRole() const = 0;

	virtual ~Employee() = default;
	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
};