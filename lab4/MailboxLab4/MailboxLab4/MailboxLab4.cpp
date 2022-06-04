#include <iostream>
#include <windows.h>
#include <vector>
#include <tchar.h>

struct Mail {
	uint32_t msgCount = 0;
	LPCWSTR path;
	HANDLE handle;
	uint32_t maxSize;
	
	Mail(LPCWSTR path, uint32_t maxSize) {
		this->path = path;
		this->maxSize = maxSize;
		handle = CreateFile(path, 
			GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ, 
			0, 
			CREATE_ALWAYS, // recreating file
			0,
			0);
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
	Mail mail(L"../mails/mainmail.dendan", 1000);

}
