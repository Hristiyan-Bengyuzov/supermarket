#pragma once
#include "String.h"

struct ValidationUtils {
	static bool isValidName(const String& name);
	static bool isValidPhoneNumber(const String& phoneNumber);
};