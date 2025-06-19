#include "CommandUtils.h"
#include "Constants.h"
using namespace Constants;

void CommandUtils::printCommandWithArgs(const String& name, const String& args)
{
	std::cout << "  " << CMD << name << RESET << " " << ARG << args << RESET << std::endl;
}