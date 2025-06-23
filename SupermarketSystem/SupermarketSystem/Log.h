#pragma once
#include "DateTime.h"
#include "String.h"
#include "Serializable.h"
#include "Printable.h"

static size_t logCounter = 0;
class Log : public Serializable, public Printable {
private:
	size_t id = 0;
	size_t employeeId;
	DateTime dateTime;
	String message;

public:
	Log() = default;
	Log(size_t employeeId, const String& message);

	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
	void print(std::ostream& os) const override;
};