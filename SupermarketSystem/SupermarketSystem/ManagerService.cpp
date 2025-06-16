#include "ManagerService.h"

ManagerService::ManagerService(EmployeeRepository& employeeRepo, ProductRepository& productRepo, CategoryRepository& categoryRepo, RegisterRequestRepository& requestRepo) : employeeRepo(employeeRepo), productRepo(productRepo), categoryRepo(categoryRepo), requestRepo(requestRepo)
{
}

void ManagerService::listPending(std::ostream& os) const
{
	bool found = false;

	auto requests = requestRepo.getAll();
	for (size_t i = 0; i < requests.getSize(); i++)
	{
		if (requests[i]->getStatus() == Status::Pending)
		{
			if (!found)
			{
				found = true;
				os << "Requests: " << std::endl;
			}
			requests[i]->print(os);
		}
	}

	if (!found)
		throw std::runtime_error("No pending requests");
}

bool ManagerService::approve(size_t managerId, size_t requestId, const String& specialCode)
{

	SharedPtr<Employee> employee = employeeRepo.findById(managerId);
	if (!employee || employee->getRole() != Role::Manager)
		throw std::runtime_error("Invalid manager");

	// this is fucking stupid
	SharedPtr<Manager> manager = SharedPtr<Manager>(dynamic_cast<Manager*>(employee.get()));
	if (manager->getSpecialCode() != specialCode)
		throw std::runtime_error("Invalid special code");

	SharedPtr<RegisterRequest> request = requestRepo.findById(requestId);
	if (!request)
		throw std::runtime_error("No request found");

	request->approve();
	Cashier* newCahier = new Cashier{ request->getFirstName(),request->getFamilyName(),request->getPhoneNumber(),request->getAge(),request->getPlainPass() };
	employeeRepo.add(newCahier);
	std::cout << "Created cashier with ID: " << newCahier->getId() << std::endl;
	return employeeRepo.saveChanges() && requestRepo.saveChanges();
}

bool ManagerService::decline(size_t managerId, size_t requestId, const String& specialCode)
{
	SharedPtr<Employee> employee = employeeRepo.findById(managerId);
	if (!employee || employee->getRole() != Role::Manager)
		throw std::runtime_error("Invalid manager");

	// this is fucking stupid
	SharedPtr<Manager> manager = SharedPtr<Manager>(dynamic_cast<Manager*>(employee.get()));
	if (manager->getSpecialCode() != specialCode)
		throw std::runtime_error("Invalid special code");

	SharedPtr<RegisterRequest> request = requestRepo.findById(requestId);
	if (!request)
		throw std::runtime_error("No request found");

	request->decline();
	return requestRepo.saveChanges();
}
