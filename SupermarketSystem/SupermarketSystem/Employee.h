#pragma once
#include "String.h"
#include "Password.h"

enum class Role {
	None,
	Cashier,
	Manager
};

static size_t counter = 0;
class Employee {
protected:
	size_t id = 0;
	String name = "";
	String familyName = "";
	String phoneNumber = "";
	unsigned age = 0;
	Password password;
	Role role = Role::None;

public:
	Employee();
	Employee(const String& name, const String& familyName, const String& phoneNumber, unsigned age, const String& plainPass, const Role& role);
	void setName(const String& name);
	void setFamilyName(const String& familyName);
	void setPhoneNumber(const String& phoneNumber);
	void setAge(unsigned age);
};