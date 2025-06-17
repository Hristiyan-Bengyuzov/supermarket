#include "ManagerService.h"

ManagerService::ManagerService(EmployeeRepository& employeeRepo, ProductRepository& productRepo, CategoryRepository& categoryRepo, RegisterRequestRepository& requestRepo, WarningRepository& warningRepo) : employeeRepo(employeeRepo), productRepo(productRepo), categoryRepo(categoryRepo), requestRepo(requestRepo), warningRepo(warningRepo)
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

	SharedPtr<Manager> manager(employee);
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

	SharedPtr<Manager> manager(employee);
	if (manager->getSpecialCode() != specialCode)
		throw std::runtime_error("Invalid special code");

	SharedPtr<RegisterRequest> request = requestRepo.findById(requestId);
	if (!request)
		throw std::runtime_error("No request found");

	request->decline();
	return requestRepo.saveChanges();
}

void ManagerService::listWarnedCashiers(std::ostream& os, unsigned points) const
{
	bool found = false;
	auto employees = employeeRepo.getAll();

	for (size_t i = 0; i < employees.getSize(); i++)
	{
		if (employees[i]->getRole() == Role::Cashier)
		{
			unsigned cashierPoints = warningRepo.getPoints(employees[i]->getId());
			if (cashierPoints >= points)
			{
				if (!found)
				{
					found = true;
					os << "Warned cashiers: " << std::endl;
				}
				employees[i]->print(os);
			}
		}
	}

	if (!found)
		throw std::runtime_error("No warned cashiers found");
}

bool ManagerService::warnCashier(const CreateWarningDTO& dto)
{
	SharedPtr<Employee> manager = employeeRepo.findById(dto.managerId);
	if (!manager || manager->getRole() != Role::Manager)
		throw std::runtime_error("Invalid manager");

	SharedPtr<Employee> cashierEmp = employeeRepo.findById(dto.cashierId);
	if (!cashierEmp || cashierEmp->getRole() != Role::Cashier)
		throw std::runtime_error("Invalid cashier");

	SharedPtr<Cashier> cashier = SharedPtr<Cashier>(dynamic_cast<Cashier*>(cashierEmp.get()));

	Warning newWarning(dto.managerId, dto.cashierId, dto.description, dto.points);
	warningRepo.add(newWarning);
	cashier->addWarningId(newWarning.getId());
	return employeeRepo.saveChanges() && warningRepo.saveChanges();
}

bool ManagerService::promoteCashier(size_t managerId, size_t cashierId, const String& specialCode)
{
	SharedPtr<Employee> managerEmp = employeeRepo.findById(managerId);
	if (!managerEmp || managerEmp->getRole() != Role::Manager)
		throw std::runtime_error("Invalid manager");

	SharedPtr<Manager> manager(managerEmp);
	if (manager->getSpecialCode() != specialCode)
		throw std::runtime_error("Invalid special code");

	SharedPtr<Employee> cashier = employeeRepo.findById(cashierId);
	if (!cashier || cashier->getRole() != Role::Cashier)
		throw std::runtime_error("Invalid cashier");

	employeeRepo.removeById(cashierId);
	Manager* newManager = new Manager(cashierId, cashier->getName(), cashier->getFamilyName(), cashier->getPhoneNumber(), cashier->getAge(), cashier->getPass());
	employeeRepo.add(newManager);
	return employeeRepo.saveChanges();
}

// bruh this is pretty much the same as promoting :sob:
bool ManagerService::fireCashier(size_t managerId, size_t cashierId, const String& specialCode)
{
	SharedPtr<Employee> managerEmp = employeeRepo.findById(managerId);
	if (!managerEmp || managerEmp->getRole() != Role::Manager)
		throw std::runtime_error("Invalid manager");

	SharedPtr<Manager> manager(managerEmp);
	if (manager->getSpecialCode() != specialCode)
		throw std::runtime_error("Invalid special code");

	SharedPtr<Employee> cashier = employeeRepo.findById(cashierId);
	if (!cashier || cashier->getRole() != Role::Cashier)
		throw std::runtime_error("Invalid cashier");

	return employeeRepo.removeById(cashierId) && employeeRepo.saveChanges();
}

bool ManagerService::addCategory(const CreateCategoryDTO& dto)
{
	if (categoryRepo.findByName(dto.name))
		throw std::runtime_error("Category already exists");

	Category newCategory(dto.name, dto.description);
	categoryRepo.add(newCategory);
	return categoryRepo.saveChanges();
}

bool ManagerService::deleteCategory(size_t categoryId)
{
	if (!categoryRepo.findById(categoryId))
		throw std::runtime_error("Category not found");

	if (productRepo.hasProductWithCategory(categoryId))
		throw std::runtime_error("Can't delete category. There are products referencing it");

	return categoryRepo.removeById(categoryId) && categoryRepo.saveChanges();
}

bool ManagerService::addProduct(const CreateProductDTO& dto)
{
	if (productRepo.findByName(dto.name))
		throw std::runtime_error("Product already exists");

	SharedPtr<Category> category = categoryRepo.findByName(dto.categoryName);
	if (!category)
		throw std::runtime_error("Category not found");

	Product* newProduct = nullptr;

	switch (dto.type)
	{
	case ProductType::ByUnit: newProduct = new ProductByUnit(dto.name, category->getId(), dto.price, dto.unitsOrWeight); break;
	case ProductType::ByWeight: newProduct = new ProductByWeight(dto.name, category->getId(), dto.price, dto.unitsOrWeight); break;
	}

	productRepo.add(newProduct);
	return productRepo.saveChanges();
}

bool ManagerService::loadProduct(const LoadProductDTO& dto)
{
	SharedPtr<Product> product = productRepo.findById(dto.productId);
	if (!product || product->getType() != dto.type)
		throw std::runtime_error("Product not found");

	switch (dto.type)
	{
	case ProductType::ByUnit: {
		auto unitProduct = dynamic_cast<ProductByUnit*>(product.get());
		if (!unitProduct) throw std::runtime_error("Invalid product type");
		unitProduct->setQuantity(unitProduct->getQuantity() + dto.unitsOrWeight);
		return productRepo.saveChanges();
	}
	case ProductType::ByWeight: {
		auto weightProduct = dynamic_cast<ProductByWeight*>(product.get());
		if (!weightProduct) throw std::runtime_error("Invalid product type");
		weightProduct->setTotalKilos(weightProduct->getTotalKilos() + dto.unitsOrWeight);
		return productRepo.saveChanges();
	}
	default: throw std::runtime_error("Unknown product type");
	}
}
bool ManagerService::deleteProduct(size_t productId)
{
	if (!productRepo.findById(productId))
		throw std::runtime_error("Product not found");
	return productRepo.removeById(productId) && productRepo.saveChanges();
}

bool ManagerService::loadProducts(const String& file)
{
	if (!file.c_str())
		throw std::runtime_error("Invalid file");

	std::ifstream ifs(file.c_str());

	if (!ifs.is_open())
		throw std::runtime_error("File not found");

	char buffer[1024];
	while (ifs.getline(buffer, 1024))
	{
		String line(buffer);
		Vector<String> tokens = line.split(':');

		try
		{
			if (tokens[0] == "NEW")
			{
				ProductType type = Product::getType(tokens[1]);
				CreateProductDTO dto = { type, tokens[2], tokens[3], tokens[4].toDouble(), tokens[5].toDouble() };
				addProduct(dto);
			}
			else
			{
				ProductType type = Product::getType(tokens[0]);
				LoadProductDTO dto = { type, tokens[1].toSizeT(), tokens[2].toDouble() };
				loadProduct(dto);
			}
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
			return false;
		}
	}
	return true;
}
