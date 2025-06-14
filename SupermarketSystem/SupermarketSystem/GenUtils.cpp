#include "GenUtils.h"
#include<cstdlib>

char GenUtils::genDigit()
{
	return '0' + rand() % 10;
}

char GenUtils::genLower()
{
	return 'a' + rand() % 26;
}

char GenUtils::genUpper()
{
	return 'A' + rand() % 26;
}
