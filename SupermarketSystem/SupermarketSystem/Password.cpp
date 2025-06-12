#include "Password.h"

String Password::generateSalt(uint32 length)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    String salt;

    for (uint32 i = 0; i < length; i++) {
        salt += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return salt;
}

String Password::hashWithSalt(const String& plainText, const String& salt)
{
    String salted = plainText + salt;
    return PasswordUtils::sha256(salted);
}

Password::Password(const String& plainText)
{
    salt = generateSalt();
    hashed = hashWithSalt(plainText, salt);
}

bool Password::operator==(const String& plainText) const
{
    return hashed == hashWithSalt(plainText, salt);
}

const String& Password::getHash() const
{
    return hashed;
}
