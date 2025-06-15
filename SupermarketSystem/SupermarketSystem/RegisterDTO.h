#pragma once
#include "Employee.h"

struct RegisterDTO {
	Role role;
	String firstName;
	String lastName;
	String phoneNumber;
	unsigned age;
	String plainPass;
};