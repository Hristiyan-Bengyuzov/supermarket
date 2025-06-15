#include "RegisterRequestRepository.h"
#include "Loader.hpp"

bool RegisterRequestRepository::loadData()
{
    return load<RegisterRequest>(file, items);
}

RegisterRequestRepository::RegisterRequestRepository() : Repository("requests.bin")
{
    loadData();
}
