#pragma once
#include "String.h"
#include "Serializable.h"

enum class Severity {
	Low,
	Medium,
	High
};

static size_t warningCounter = 0;
class Warning : public Serializable {
private:
	size_t id = 0;
	size_t senderId = 0;
	size_t cashierId = 0;
	String description = "";
	unsigned severityPoints = 0;

public:
	Warning() = default;
	Warning(size_t senderId, size_t cashierId, const String& description, unsigned severityPoints);

	Severity getSeverity() const;
	size_t getCashierId() const;
	size_t getId() const;
	unsigned getSeverityPoints() const;
	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
};