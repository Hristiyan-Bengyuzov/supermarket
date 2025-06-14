#include "Cashier.h"

Cashier::Cashier(const String& name, const String& familyName, const String& phoneNumber, unsigned age, const String& plainPass) : Employee(name, familyName, phoneNumber, age, plainPass)
{
}

void Cashier::addWarningId(size_t warningId)
{
	warningIds.push_back(warningId);
}

Role Cashier::getRole() const
{
	return Role::Cashier;
}
