#include "driver.h"

int main() {
	const DWORD pid = get_process_id(L"Notepad.exe");

	if (pid == 0) {
		std::cout << "failed to find process \n";
		std::cin.get();
		return 1;
	}

	const HANDLE driver_handle = CreateFileW(L"\\\\.\\adrenochrome", GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, nullptr);

	if (driver_handle == INVALID_HANDLE_VALUE) {
		std::cout << "failed to create our driver handle \n";	
		std::cin.get();
		return 1;
	}

	if (driver::attach_to_process(driver_handle, pid) == true)
		std::cout << "attachment successful \n";

	CloseHandle(driver_handle);
	std::cin.get();
	return 0;
}