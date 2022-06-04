#include <iostream>
#include <windows.h>
#include <vector>
#include <tchar.h>

struct Mail {
	size_t msgCount = 0;
	LPCWSTR path;
	HANDLE handler;
	DWORD maxSize;
	
	Mail(LPCWSTR path, int maxSize) {
		this->path = path;
		this->maxSize = maxSize;
	}
};

int main() {
	Mail mail(_T("../"), 32);
}
