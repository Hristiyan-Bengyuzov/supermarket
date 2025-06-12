// SupermarketSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "String.h"
#include "PasswordUtils.h"

int main()
{
	String str = "hello";
	String res = PasswordUtils::sha256(str);
	std::cout << res;
}
