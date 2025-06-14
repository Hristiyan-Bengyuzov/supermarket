#pragma once
#include "String.h"
#include "PasswordUtils.h"
#include "Serializable.h"

class Password : public Serializable {
private:
	String hashed = "";
	String salt = "";

	static String generateSalt(uint32 length = 16);
	static String hashWithSalt(const String& plainText, const String& salt);
public:
	Password() = default;
	Password(const String& plainText);

	bool operator==(const String& plainText) const;

	const String& getHash() const;

	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
};