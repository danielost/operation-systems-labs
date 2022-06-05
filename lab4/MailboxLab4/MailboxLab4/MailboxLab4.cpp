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
	
	void setMessagesSize(int size) {
		SetFilePointer(handle, sizeof(int), 0, 0);
		WriteFile(handle, &size, sizeof(int), 0, 0);
	}

	void setMessagesMaxSize(int size) {
		SetFilePointer(handle, sizeof(int) * 2, 0, 0);
		WriteFile(handle, &size, sizeof(int), 0, 0);
	}

	LPCTSTR getMailPath() {
		return path;//.substr(path.find("\\"));;
	}

	Mail(LPCTSTR path, uint32_t maxSize) {
		this->path = path;
		this->maxSize = maxSize;
		handle = CreateFile(path, 
			GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ, 
			0, 
			CREATE_ALWAYS, // recreating file
			0,
			0);
		setMessagesAmount(0);
		setMessagesSize(0);
		setMessagesMaxSize(maxSize);
	}
};

struct MailBox {
	std::vector<Mail> mails;

	Mail* addMail(PCTSTR path, int mailMaxSize) {
		Mail mail = Mail(path, mailMaxSize);
		mails.push_back(mail);
		return &mail;
	}

	Mail* retrieveMailByNumber(int mailNumber) {
		return &mails[mailNumber - 1];
	}

	int amountOfMails() {
		return mails.size();
	}

	void printMails() {
		if (amountOfMails() == 0) {
			std::cout << "Your mailbox is empty." << std::endl;
			return;
		}
		std::cout << "Your Mailbox (total: " << amountOfMails() << ")" << std::endl;
		for (int i = 0; i < amountOfMails(); i++) {
			//_tprintf(_T("%d) %s\n"), i + 1, mails[i].getMailPath());
			std::wcout << i + 1 << ") " << mails[i].getMailPath() << std::endl;
		}
	}
};

int main() {
	MailBox mailBox;

	Mail mainMail = *mailBox.addMail(L"../mails/main.dendan", 1000);
	Mail secondaryMail = *mailBox.addMail(L"../mails/secondary.dendan", 1000);

	mailBox.printMails();
}
