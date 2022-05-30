#include <iostream>
#include <Windows.h>
#include <locale>
#include "../ControlSum/Header.h"

typedef std::pair<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>> (*getKeyPair)();
typedef uint64_t (*encryptMessage)(uint64_t, std::pair<uint64_t, uint64_t>);
typedef uint64_t (*decryptMessage)(uint64_t, std::pair<uint64_t, uint64_t>);

int main() {
	setlocale(LC_ALL, "Ukrainian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HMODULE rs;

	int n;
	std::cout << "Type 1 to see info in English, and 0 to see it in Ukrainian: ";
	std::cin >> n;
	if (n) {
		rs = LoadLibrary(TEXT("EngLib.dll"));
	} 
	else if (n == 0) {
		rs = LoadLibrary(TEXT("UkrLib.dll"));
	}
	else {
		std::cout << "You need to type 0 or 1!.";
		return 0;
	}
	if (rs == 0) {
		std::cout << "Failure! Library was not loaded" << std::endl;
		return 0;
	}

	TCHAR str[50];
	for (int i = 101; i < 105; i++) {
		LoadString(rs, i, str, 50);
		std::wcout << str << std::endl;
	}
	FreeLibrary(rs);

	//we used this function once to write the check sum to the operations.dll for the first time
	//writeSum((char*)"..\\Debug\\operations.dll");

	HMODULE h = LoadLibrary(TEXT("operations.dll"));
	if (h == 0) {
		std::cout << "Failure! RSA library was not loaded" << std::endl;
		return 0;
	}
	
	getKeyPair gkp = (getKeyPair)GetProcAddress(h, "getKeyPair");
	encryptMessage encryptM = (encryptMessage)GetProcAddress(h, "encryptMessage");
	decryptMessage decryptM = (decryptMessage)GetProcAddress(h, "decryptMessage");

	for (int i = 0; i < 3; i++) {
		auto keys1 = gkp();
		auto keys2 = gkp();
		uint64_t d0 = keys1.second.first;
		uint64_t e0 = keys1.first.first;
		uint64_t n0 = keys1.first.second;

		uint64_t d1 = keys2.second.first;
		uint64_t e1 = keys2.first.first;
		uint64_t n1 = keys2.first.second;

		std::cout << "Example " << i + 1 << std::endl;
		std::cout << "{d0, e0, n0}: " << d0 << ", " << e0 << ", " << n0 << "\n";
		std::cout << "{d1, e1, n1}: " << d1 << ", " << e1 << ", " << n1 << "\n";
	
		std::cout << "Enter a number: ";
		uint64_t t;
		std::cin >> t;
		if (t >= n0 - 1) {
			std::cout << "Number must be less than (n0 - 1)." << std::endl;
			return 0;
		}

		uint64_t e1t = encryptM(t, {e1, n1});
		std::cout << "e1t: " << e1t << "\n";
		uint64_t d1e1t = decryptM(e1t, { d1, n1 });
		std::cout << "d1e1t: " << d1e1t << "\n";

		if (d1e1t != t) {
			std::cout << "Failure! d1e1t message is incorrect!\n";
			return 0;
		}

		uint64_t e0d1e1t = encryptM(d1e1t, { e0, n0 });
		std::cout << "e0d1e1t: " << e0d1e1t << "\n";
		uint64_t d0e0d1e1t = decryptM(e0d1e1t, { d0, n0 });
		std::cout << "d0e0d1e1t: " << d0e0d1e1t << "\n";

		if (d0e0d1e1t != t) {
			std::cout << "Failure! d0e0d1e1t message is incorrect!\n";
			return 0;
		}

		std::cout << "Success!" << std::endl;
	}
	return 0;
	//Made by D(e/a)n
}


