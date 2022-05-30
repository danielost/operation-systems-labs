#pragma once

#include <vector>

extern "C++" uint64_t gcd(uint64_t, uint64_t);
extern "C++" int64_t powMod(int64_t, int64_t, int64_t);
extern "C++" std::vector<uint64_t> generatePrimes(uint64_t);
extern "C++" uint64_t getRandomPrime();
extern "C++" std::pair<uint64_t, uint64_t> generatePublicKey(uint64_t, uint64_t, uint64_t, uint64_t);
extern "C++" std::pair<uint64_t, uint64_t> generatePrivateKey(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);