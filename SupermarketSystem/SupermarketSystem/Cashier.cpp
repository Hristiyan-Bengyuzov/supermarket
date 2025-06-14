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

void Cashier::serialize(std::ofstream& ofs) const
{
	Role role = getRole();
	ofs.write(reinterpret_cast<const char*>(&role), sizeof(Role));

	Employee::serialize(ofs);
	ofs.write(reinterpret_cast<const char*>(&transactionsMade), sizeof(size_t));

	size_t warningSize = warningIds.getSize();
	ofs.write(reinterpret_cast<const char*>(&warningSize), sizeof(size_t));
	for (size_t i = 0; i < warningSize; i++)
		ofs.write(reinterpret_cast<const char*>(&warningIds[i]), sizeof(size_t));
}

void Cashier::deserialize(std::ifstream& ifs)
{
    Employee::deserialize(ifs);
    ifs.read(reinterpret_cast<char*>(&transactionsMade), sizeof(size_t));

    size_t warningSize = 0;
    ifs.read(reinterpret_cast<char*>(&warningSize), sizeof(size_t));
    warningIds.clear();

    for (size_t i = 0; i < warningSize; i++) {
        size_t warningId;
        ifs.read(reinterpret_cast<char*>(&warningId), sizeof(size_t));
        warningIds.push_back(warningId);
    }
}
