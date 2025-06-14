#include "ValidationUtils.h"
#include "CharUtils.h"


bool ValidationUtils::isValidName(const String& name)
{
	if (name == nullptr || !CharUtils::isUpperCase(name[0]))
		return false;

	for (size_t i = 1; i < name.getSize(); i++)
	{
		if (!CharUtils::isLowerCase(name[i]))
			return false;
	}

	return true;
}

// wish i could use regex...
bool ValidationUtils::isValidPhoneNumber(const String& phoneNumber)
{
	if (phoneNumber == nullptr)
		return false;

	if (phoneNumber.startsWith("+3598"))
	{
		char c = phoneNumber[5];
		if (c != '7' && c != '8' && c != '9')
			return false;

		for (size_t i = 6; i < phoneNumber.getSize(); i++)
		{
			if (!CharUtils::isDigit(phoneNumber[i]))
				return false;
		}
	}
	else if (phoneNumber.startsWith("08"))
	{
		char c = phoneNumber[2];
		if (c != '7' && c != '8' && c != '9')
			return false;

		for (size_t i = 3; i < phoneNumber.getSize(); i++)
		{
			if (!CharUtils::isDigit(phoneNumber[i]))
				return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}
