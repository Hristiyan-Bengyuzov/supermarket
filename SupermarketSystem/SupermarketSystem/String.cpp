#include "String.h"
#include "Constants.h"


using namespace Constants;
String::String() : String("")
{
}

String::String(const char* data)
{
	if (!data)
	{
		this->size = 0;
		this->capacity = allocateCapacity(0);
		this->data = new char[this->capacity];
		this->data[0] = '\0';
	}
	else
	{
		this->size = strlen(data);
		this->capacity = allocateCapacity(this->size);
		this->data = new char[this->capacity];
		strcpy(this->data, data);
	}
}

String::String(size_t newSize) : size(0), capacity(allocateCapacity(newSize))
{
	this->data = new char[this->capacity] { '\0' };
}

String::String(const String& other)
{
	copyFrom(other);
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

const char* String::c_str() const
{
	return this->data;
}

size_t String::getSize() const
{
	return this->size;
}

size_t String::getCapacity() const
{
	return this->capacity;
}

const char& String::operator[](size_t idx) const
{
	return this->data[idx];
}

char& String::operator[](size_t idx)
{
	return this->data[idx];
}

String& String::operator+=(char c)
{
	if (getSize() + 1 >= getCapacity())
	{
		resize(allocateCapacity(getSize() + 1));
	}

	this->data[this->size] = c;
	this->data[this->size + 1] = '\0';
	this->size += 1;

	return *this;
}

String& String::operator+=(const String& other)
{
	if (getSize() + other.getSize() >= getCapacity())
	{
		resize(allocateCapacity(getSize() + other.getSize()));
	}

	strncat(this->data, other.data, other.getSize());

	this->size += other.getSize();

	return *this;
}

String operator+(const String& lhs, const String& rhs)
{
	String toReturn(lhs.getSize() + rhs.getSize());

	toReturn += lhs;
	toReturn += rhs;

	return toReturn;
}

String String::parseFrom(size_t num)
{
	if (num == 0)
		return String("0");

	String res;

	while (num)
	{
		res += '0' + num % 10;
		num /= 10;
	}

	return res.reverse();
}

String String::reverse() const
{
	String reversed;
	for (int i = getSize() - 1; i >= 0; --i)
	{
		reversed += (*this)[i];
	}
	return reversed;
}

String String::substr(size_t begin, size_t howMany) const
{
	if (begin + howMany > getSize()) return String("");

	String toReturn(howMany);
	strncat(toReturn.data, this->data + begin, howMany);
	return toReturn;
}

bool String::startsWith(const String& other) const
{
	if (other.size > size)
		return false;

	for (size_t i = 0; i < other.size; i++)
	{
		if (data[i] != other.data[i])
			return false;
	}

	return true;
}

bool String::endsWith(const String& other) const
{
	if (other.size > size)
		return false;

	size_t startPos = size - other.size;
	for (size_t i = 0; i < other.size; i++)
	{
		if (data[startPos + i] != other.data[i])
			return false;
	}

	return true;
}

size_t String::toSizeT() const
{
	size_t result = 0;
	for (size_t i = 0; i < size; ++i) {
		if (data[i] < '0' || data[i] > '9')
			throw std::invalid_argument("String contains non-digit characters");
		result = result * 10 + (data[i] - '0');
	}
	return result;
}

double String::toDouble() const
{
	double result = 0.0;
	double fraction = 0.0;
	bool isFraction = false;
	double divisor = 10.0;

	for (size_t i = 0; i < size; ++i) {
		if (data[i] == '.') {
			if (isFraction)
				throw std::invalid_argument("String contains multiple decimal points");
			isFraction = true;
		}
		else if (data[i] >= '0' && data[i] <= '9') {
			if (!isFraction) {
				result = result * 10 + (data[i] - '0');
			}
			else {
				fraction += (data[i] - '0') / divisor;
				divisor *= 10;
			}
		}
		else {
			throw std::invalid_argument("String contains invalid characters");
		}
	}

	return result + fraction;
}

Vector<String> String::split(char delimeter) const
{
	Vector<String> result;
	size_t start = 0;
	size_t end = 0;

	while (end <= size) {
		if (end == size || data[end] == delimeter) {
			if (start != end) {
				size_t length = end - start;
				char* substring = new char[length + 1];
				strncpy(substring, data + start, length);
				substring[length] = '\0';
				result.push_back(String(substring));
				delete[] substring;
			}
			start = end + 1;
		}
		end++;
	}

	return result;
}

bool operator==(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) != 0;
}

bool operator<=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) <= 0;
}

bool operator>=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) >= 0;
}

bool operator<(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) < 0;
}

bool operator>(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) > 0;
}

std::istream& operator>>(std::istream& is, String& other)
{
	char buff[1025];
	is >> buff;

	size_t buffLength = strlen(buff);

	if (buffLength >= other.getCapacity())
	{
		other.resize(other.allocateCapacity(buffLength));
	}

	strcpy(other.data, buff);

	other.size = buffLength;

	return is;
}

std::ostream& operator<<(std::ostream& os, const String& other)
{
	return os << other.data;
}

void String::serialize(std::ofstream& ofs) const
{
	ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));
	ofs.write(data, size);
}

void String::deserialize(std::ifstream& ifs)
{
	size_t newSize;
	ifs.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));

	char* newData = new char[newSize + 1];
	ifs.read(newData, newSize);
	newData[newSize] = '\0';

	delete[] data;
	data = newData;
	size = newSize;
	capacity = newSize + 1;
}

String String::readLine(const char* message)
{
	std::cout << message;
	char buffer[1025];
	if (!std::cin.getline(buffer, sizeof(buffer)))
	{
		throw std::runtime_error("Error reading input");
	}

	return String(buffer);
}

String String::readLineNotEmpty(const char* message)
{
	while (true)
	{
		String line = readLine(message);
		if (line.getSize() > 0)
		{
			return line;
		}
		std::cout << FAILURE << "Input cannot be empty. Please try again." << RESET << std::endl;
	}
}

String::~String()
{
	free();
}

unsigned int String::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
	{
		n &= (n - 1);
	}

	return n << 1;
}

unsigned int String::allocateCapacity(unsigned int size) const
{
	return std::max(getNextPowerOfTwo(size + 1), 8u);
}

void String::resize(size_t newCapacity)
{
	this->capacity = newCapacity;

	char* newData = new char[this->capacity];
	strcpy(newData, this->data);

	delete[] this->data;
	this->data = newData;
}

void String::copyFrom(const String& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->data = new char[strlen(other.data) + 1];
	strcpy(this->data, other.data);
}

void String::free()
{
	delete[] this->data;

	this->data = nullptr;
	this->size = this->capacity = 0;
}