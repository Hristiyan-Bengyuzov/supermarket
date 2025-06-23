#pragma once
#include<ctime>
#include "String.h"
#include "Serializable.h"

class DateTime : public Serializable {
private:
	time_t rawTime;
	tm* timeInfo;

public:
	DateTime();

	String toString() const;

	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
};