#pragma once
#include "String.h"

enum class Severity {
	Low,
	Medium,
	High
};

static size_t warningCounter = 0;
class Warning {
private:
	size_t id = 0;
	size_t senderId = 0;
	String description = "";
	unsigned severityPoints = 0;

public:
	Warning() = default;
	Warning(size_t senderId, const String& description, unsigned severityPoints);

	Severity getSeverity() const;
};