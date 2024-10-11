#include "driver.h"

int main() {
	const DWORD pid = get_process_id(L"Notepad.exe");

	if (pid == 0) {
		std::cout << "failed to find process \n";
		return 1;
	}

	const HANDLE driver = CreateFile(L"\\\\.\\adrenochrome", GENERIC_READ, 0, nullptr, 
										OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (driver == INVALID_HANDLE_VALUE) {
		std::cout << "failed to create our driver handle \n";		
		return 1;
	}

	if (driver::attach_to_process(driver, pid) == true) 
		std::cout << "attachment successful \n";

	CloseHandle(driver);
	return 0;
}