#pragma once
#include<fstream>

struct Printable {
	virtual ~Printable() = default;
	virtual void print(std::ostream& os) const = 0;
};