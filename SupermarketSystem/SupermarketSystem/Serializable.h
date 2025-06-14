#pragma once
#include <fstream>

struct Serializable {
	virtual ~Serializable() = default;
	virtual void serialize(std::ofstream& ofs) const = 0;
	virtual void deserialize(std::ifstream& ifs) = 0;
};