#pragma once
#include "String.h"
#include "Serializable.h"
#include "Printable.h"

enum class Status {
	Pending,
	Approved,
	Declined
};

static size_t requestCounter = 0;
class RegisterRequest : public Serializable, public Printable {
private:
	size_t id = 0;
	Status status = Status::Pending;
	String firstName = "";
	String familyName = "";
	String phoneNumber = "";
	unsigned age = 0;
	String plainPass = 0;

public:
	RegisterRequest() = default;
	RegisterRequest(const String& firstName, const String& familyName, const String& phoneNumber, unsigned age, const String& plainPass);

	void approve();
	void decline();
	size_t getId() const;
	Status getStatus() const;
	const String& getFirstName() const;
	const String& getFamilyName() const;
	const String& getPhoneNumber() const;
	unsigned getAge() const;
	const String& getPlainPass() const;

	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
	void print(std::ostream& os) const override;
};