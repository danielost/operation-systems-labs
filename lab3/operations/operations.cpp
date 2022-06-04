#include "pch.h"
#include "inner_use.h"
#include "outer_use.h"

#include <vector>
#include <string>
#include <iostream>

//returns the greates common divisor of two numbers
extern "C++" uint64_t gcd(uint64_t a, uint64_t b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

//function for fast number exponentiation in logarithmic time
extern "C++" int64_t powMod(int64_t a, int64_t e, int64_t mod) {
    int64_t res = 1;
    while (e != 0) {
        if (e & 1) {
            res *= a;
            res %= mod;
        }
        e /= 2;
        a *= a;
        a %= mod;
    }
    return res;
}

//generating prime numbers using sieve of Eratosthenes
extern "C++" std::vector<uint64_t> generatePrimes(uint64_t upBorder) {
    std::vector<uint64_t> primeList;

    std::vector<bool> sieve(upBorder + 1, true);
    for (uint64_t i = 2; i < sieve.size(); i += 1) {
        if (sieve[i]) {
            for (uint64_t j = i + i; j < sieve.size(); j += i) {
                sieve[j] = false;
            }
            primeList.push_back(i);
        }
    }
    return primeList;
}

extern "C++" uint64_t getRandomPrime() {
    srand(time(NULL));
    return generatePrimes(100000)[rand() % 1000];
}

extern "C++" std::pair<uint64_t, uint64_t> generatePrivateKey(uint64_t p, uint64_t q, uint64_t n, uint64_t euler) {
    uint64_t privateKey = rand() * rand();
    
    while (gcd(privateKey, euler) != 1) {
        privateKey++;
    }
    return { privateKey, n };
}

extern "C++" std::pair<uint64_t, uint64_t> generatePublicKey(uint64_t privateKey, uint64_t p, uint64_t q, uint64_t n, uint64_t euler) {
    uint64_t publicKey = 3;
    while ((privateKey * publicKey) % euler != 1) {
        publicKey++;
    }
    return { publicKey, n };
}

OPERATIONS_API std::pair<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>> getKeyPair() {
    uint64_t p = getRandomPrime();
    uint64_t q = getRandomPrime();
    while (p == q) { //updating q in case it equals to p
        q = getRandomPrime();
    }
    uint64_t n = p * q;
    uint64_t euler = (p - 1) * (q - 1);

    std::pair<uint64_t, uint64_t> privateKey = generatePrivateKey(p, q, n, euler);
    std::pair<uint64_t, uint64_t> publicKey = generatePublicKey(privateKey.first, p, q, n, euler);

    return { publicKey, privateKey };
}

OPERATIONS_API uint64_t encryptMessage(uint64_t message, std::pair<uint64_t, uint64_t> publicKey) {
    return powMod(message, publicKey.first, publicKey.second);
}

OPERATIONS_API uint64_t decryptMessage(uint64_t message, std::pair<uint64_t, uint64_t> privateKey) {
    return powMod(message, privateKey.first, privateKey.second);
}

//Made by D(e/a)n