#pragma once
#include "Printable.h"
#include "String.h"
#include "Password.h"
#include "Constants.h"

using namespace Constants;

enum class Role {
	Cashier,
	Manager,
	None
};

static size_t counter = 0;
class Employee : public Serializable, public Printable {
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

	size_t getId() const;
	const String& getName() const;
	const String& getFamilyName() const;
	const String& getPhoneNumber() const;
	unsigned getAge() const;
	const Password& getPass() const;

	virtual Role getRole() const = 0;
	static Role getRole(const String& str);

	bool checkPass(const String& plainPass) const;

	virtual ~Employee() = default;
	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
	void print(std::ostream& os) const override;
};