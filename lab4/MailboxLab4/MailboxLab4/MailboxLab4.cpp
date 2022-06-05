#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <vector>
#include <string>

using namespace std;

struct Mail {
	LPCTSTR path;
	HANDLE handle;
	uint32_t maxSize;
	uint32_t currentEnd = 3;
	uint32_t amountOfMessages = 0;

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
			OPEN_ALWAYS, // recreating file
			0,
			0);
		setMessagesAmount(0);
		setMessagesSize(0);
		setMessagesMaxSize(maxSize);
	}

	
	bool addMessage(LPCTSTR message) {
		uint32_t messageSize = _tcslen(message) * sizeof(TCHAR);
		if (currentEnd + messageSize > maxSize) { return false; }
		if (!SetFilePointer(handle, currentEnd * sizeof(int), 0, 0)) return false;
		if (!WriteFile(handle, &messageSize, sizeof(int), 0, 0)) return false;

		currentEnd++;
		if (!SetFilePointer(handle, currentEnd * sizeof(int), 0, 0)) return false;
		if (!WriteFile(handle, &message, messageSize, 0, 0)) return false;
		currentEnd += messageSize;

		return true; 
	}

	bool readMessage(uint32_t index) {
		if (index < 0 || index >= amountOfMessages) { return false;  }
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
			std::wcout << i + 1 << ") " << mails[i].getMailPath() << std::endl;
		}
	}
};

void printMainMenu() {
	std::cout << "1. Open existing mails;\n2. Create a new mail;\n3. Exit." << std::endl;
}

void createMail(MailBox mailBox) {
	std::cout << "Enter the name for the mail: ";
	std::wstring name;
	std::wcin >> name;

	std::cout << "Enter the max capacity for the mail: ";
	int capacity;
	std::cin >> capacity;
	while (capacity < 20 || capacity > 10000) {
		std::cout << "Invalid capacity. Enter new: ";
		std::cin >> capacity;
	}

	std::wstring path = L"../mails/" + name + L".dendan";
	Mail newMail = *mailBox.addMail(path.c_str(), 1000);

	std::wcout << name << " mail has been created!" << std::endl;
}

void printMailActions() {
	std::cout << "1. Add new message\n2. Read message\n3. Read message and delete\n4. Delete message\n5. Delete all messages\n0. Go back." << std::endl;
}

wstring readMessageFromConsole() {
	wcout << "Enter a message (press Enter to finish):\n";
	wstring msgStr;
	getline(wcin >> ws, msgStr);
	return msgStr;
}

void writeOperationResult(bool result) {
	if (result) { std::cout << "Succesfully performed operation :)\n"; }
	else { std::cout << "Error occured while performing operation :(\n"; }
}

int main() {
	MailBox mailBox;

	Mail mainMail = *mailBox.addMail(L"../mails/main.dendan", 1000);
	Mail secondaryMail = *mailBox.addMail(L"../mails/secondary.dendan", 1000);

	while (true) {
		
		printMainMenu();
		int n;
		std::cin >> n;
		if (n == 1) {
			std::cout << "Choose a mail:" << std::endl;
			mailBox.printMails();
			int n;
			std::cin >> n;
			while (n <= 0 || n > mailBox.amountOfMails()) {
				std::cout << "Invalid number! Enter new: ";
				std::cin >> n;
			}
			std::wcout << "You've chosen " << mailBox.retrieveMailByNumber(n)->path << " mail." << std::endl;
			while (true) {
				printMailActions();
				std::cin >> n;
				while (n < 0 || n > 5) {
					std::cout << "Invalid value. Enter new: " << std::endl;
					std::cin >> n;
				}
				if (n == 1) {
					std::wstring msg = readMessageFromConsole();
					LPCTSTR message = msg.c_str();
					bool result = (*mailBox.retrieveMailByNumber(n)).addMessage(message);
					writeOperationResult(result);					
				} else if (n == 2) {

				} else if (n == 3) {

				} else if (n == 4) {

				} else if (n == 5) {

				} else { break; }
			}
			
		}
		else if (n == 2) {
			createMail(mailBox);
		}
		else if (n == 3) {
			break;
		}
		else {
			std::cout << "Invalid value";
			continue;
		}		

	}

	std::cout << "Bye!" << std::endl;
}


