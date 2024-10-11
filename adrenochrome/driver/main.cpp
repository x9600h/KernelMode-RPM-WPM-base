#include "driver.h"

NTSTATUS driver_entry(PDRIVER_OBJECT driver_object,PUNICODE_STRING registry_path) {

	UNREFERENCED_PARAMETER(registry_path);
	
	UNICODE_STRING device_name = {};
	RtlInitUnicodeString(&device_name, L"\\Driver\\adrenochrome");
	
	PDEVICE_OBJECT device_object = nullptr; 
	NTSTATUS status = IoCreateDevice(driver_object, 0, &device_name, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &device_object);

	if (status != STATUS_SUCCESS) {
		DbgPrint("[-] Failed to create driver device. Status: 0x%X\n", status); 
		return status;
	}

	debug_print("[+] Driver device successfully created");

	UNICODE_STRING symbolic_link = {};
	RtlInitUnicodeString(&symbolic_link, L"\\DosDevices\\adrenochrome");

	status = IoCreateSymbolicLink(&symbolic_link, &device_name);

	if (status != STATUS_SUCCESS) {
		debug_print("[-] Failed to establish symbolic link \n");
		return status;
	}

	debug_print("[+] Device symbolic link successfully established");

	SetFlag(device_object->Flags, DO_BUFFERED_IO);

	driver_object->MajorFunction[IRP_MJ_CREATE] = driver::create;
	driver_object->MajorFunction[IRP_MJ_CLOSE] = driver::close;
	driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = driver::device_control;

	ClearFlag(device_object->Flags, DO_DEVICE_INITIALIZING);

	return STATUS_SUCCESS;
}
 
NTSTATUS DriverEntry(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path) {

	debug_print("[+] adrenochrome started \n");

	UNICODE_STRING device_name = {};
	RtlInitUnicodeString(&device_name, L"\\Driver\\adrenochrome");

	PDEVICE_OBJECT device_object = nullptr;
	NTSTATUS status = IoCreateDevice(driver_object, 0, &device_name, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &device_object);


	if (status != STATUS_SUCCESS) {
		DbgPrint("[-] Failed to create driver device. Status: 0x%X\n", status);
		return status;
	}

	debug_print("[+] Driver device successfully created");
}