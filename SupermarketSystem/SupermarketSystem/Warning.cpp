#include "Warning.h"

Warning::Warning(size_t senderId, const String& description, unsigned severityPoints)
{
	this->senderId = senderId;
	this->description = description;
	this->severityPoints = severityPoints;
}

Severity Warning::getSeverity() const
{
	if (severityPoints <= 100)  return Severity::Low;
	return severityPoints <= 200 ? Severity::Medium : Severity::High;
}
