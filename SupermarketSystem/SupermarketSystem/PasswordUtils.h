#pragma once
#include "String.h"

typedef unsigned char uint8;
typedef unsigned int uint32;
typedef unsigned long long uint64;

class PasswordUtils {
    static uint32 rotr(uint32 x, uint32 n);
    static uint32 ch(uint32 x, uint32 y, uint32 z);
    static uint32 maj(uint32 x, uint32 y, uint32 z);
    static uint32 SIG0(uint32 x);
    static uint32 SIG1(uint32 x);
    static uint32 sig0(uint32 x);
    static uint32 sig1(uint32 x);
    static void transform(uint32* state, const uint8* block);
    static void toHex(uint32 val, char* output);

    static const uint32 k[64];
public:
    static String sha256(const String& input);
};