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

struct MailBox {
	std::vector<Mail> mails;

	Mail* addMail(PCTSTR path, int mailMaxSize) {
		Mail mail = Mail(path, mailMaxSize);
		mails.push_back(mail);
		return &mail;
	}
};

int main() {

}
