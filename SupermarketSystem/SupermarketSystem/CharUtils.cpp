#include "CharUtils.h"

bool CharUtils::isLowerCase(char c)
{
	return c >= 'a' && c <= 'z';
}

bool CharUtils::isUpperCase(char c)
{
	return c >= 'A' && c <= 'Z';
}

bool CharUtils::isDigit(char c)
{
	return c >= '0' && c <= '9';
}
