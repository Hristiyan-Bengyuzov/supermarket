#include "Cashier.h"

Cashier::Cashier(const String& name, const String& familyName, const String& phoneNumber, unsigned age, const String& plainPass) : Employee(name, familyName, phoneNumber, age, plainPass, Role::Cashier)
{
}

void Cashier::addWarningId(size_t warningId)
{
	warningIds.push_back(warningId);
}
