#include "PasswordUtils.h"

const uint32 PasswordUtils::k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint32 PasswordUtils::rotr(uint32 x, uint32 n)
{
    return (x >> n) | (x << (32 - n));
}

uint32 PasswordUtils::ch(uint32 x, uint32 y, uint32 z)
{
    return (x & y) ^ (~x & z);
}

uint32 PasswordUtils::maj(uint32 x, uint32 y, uint32 z)
{
    return (x & y) ^ (x & z) ^ (y & z);
}

uint32 PasswordUtils::SIG0(uint32 x)
{
    return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
}

uint32 PasswordUtils::SIG1(uint32 x)
{
    return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
}

uint32 PasswordUtils::sig0(uint32 x)
{
    return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
}

uint32 PasswordUtils::sig1(uint32 x)
{
    return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
}

void PasswordUtils::transform(uint32* state, const uint8* block)
{
	uint32 w[64];
	for (int i = 0; i < 16; i++) {
		w[i] = (block[i * 4] << 24) |
			(block[i * 4 + 1] << 16) |
			(block[i * 4 + 2] << 8) |
			(block[i * 4 + 3]);
	}
	for (int i = 16; i < 64; i++) {
		w[i] = sig1(w[i - 2]) + w[i - 7] + sig0(w[i - 15]) + w[i - 16];
	}

	uint32 a = state[0];
	uint32 b = state[1];
	uint32 c = state[2];
	uint32 d = state[3];
	uint32 e = state[4];
	uint32 f = state[5];
	uint32 g = state[6];
	uint32 h = state[7];

	for (int i = 0; i < 64; i++) {
		uint32 temp1 = h + SIG1(e) + ch(e, f, g) + k[i] + w[i];
		uint32 temp2 = SIG0(a) + maj(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + temp1;
		d = c;
		c = b;
		b = a;
		a = temp1 + temp2;
	}

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	state[4] += e;
	state[5] += f;
	state[6] += g;
	state[7] += h;
}

void PasswordUtils::toHex(uint32 val, char* output)
{
	const char* hex = "0123456789abcdef";
	for (int i = 0; i < 8; ++i) {
		output[i] = hex[(val >> (28 - 4 * i)) & 0xF];
	}
}

String PasswordUtils::sha256(const String& input)
{
	uint32 state[8] = {
	  0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
	  0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
	};

	const uint8* data = (const uint8*)input.c_str();
	size_t inputSize = input.getSize();
	uint64 bitlen = inputSize * 8;

	size_t fullLen = inputSize + 1 + 8;
	size_t paddedLen = ((fullLen + 63) / 64) * 64;
	uint8* padded = new uint8[paddedLen](); 

	for (size_t i = 0; i < inputSize; i++) {
		padded[i] = data[i];
	}
	padded[inputSize] = 0x80;

	for (int i = 0; i < 8; ++i) {
		padded[paddedLen - 8 + i] = (bitlen >> (56 - i * 8)) & 0xff;
	}

	for (size_t i = 0; i < paddedLen; i += 64) {
		transform(state, &padded[i]);
	}

	delete[] padded;

	char hashStr[65];
	for (int i = 0; i < 8; ++i) {
		toHex(state[i], &hashStr[i * 8]);
	}
	hashStr[64] = '\0';

	return String(hashStr);
}
