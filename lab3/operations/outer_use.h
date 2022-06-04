#pragma once

#ifdef OPERATIONS_EXPORTS
	#define OPERATIONS_API extern "C++" __declspec(dllexport)
#else
	#define OPERATIONS_API extern "C++" __declspec(dllimport)
#endif

OPERATIONS_API std::pair<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>> getKeyPair();
OPERATIONS_API uint64_t encryptMessage(uint64_t, std::pair<uint64_t, uint64_t>);
OPERATIONS_API uint64_t decryptMessage(uint64_t, std::pair<uint64_t, uint64_t>);