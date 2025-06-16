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
