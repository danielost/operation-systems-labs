#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <vector>

struct Mail {
	LPCWSTR path;
	HANDLE handle;
	uint32_t maxSize;
	
	void setMessagesAmount(int amount) {
		SetFilePointer(handle, 0, 0, 0);
		WriteFile(handle, &amount, sizeof(int), 0, 0);
	}

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
		setMessagesAmount(10);
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
