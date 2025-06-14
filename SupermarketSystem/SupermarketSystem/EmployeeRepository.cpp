#pragma once
#include "EmployeeRepository.h"

EmployeeRepository::EmployeeRepository() : Repository("employees.bin")
{
    loadData();
}

bool EmployeeRepository::loadData()
{
    if (!file.c_str())
        return false;

    std::ifstream in(file.c_str(), std::ios::binary | std::ios::in);
    if (!in.is_open())
        return false;

    items.clear();

    size_t count;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (size_t i = 0; i < count; ++i) {
        Role role;
        in.read(reinterpret_cast<char*>(&role), sizeof(Role));

        SharedPtr<Employee> employee;
        switch (role) {
        case Role::Manager:
            employee = SharedPtr<Employee>(new Manager());
            break;
        case Role::Cashier:
            employee = SharedPtr<Employee>(new Cashier());
            break;
        default:
            continue; 
        }

        employee->deserialize(in);
        items.push_back(employee);
    }

    return true;

}
