#include "driver.h"

NTSTATUS driver_entry(PDRIVER_OBJECT driver_object,PUNICODE_STRING registry_path) {

	UNREFERENCED_PARAMETER(registry_path);

	UNICODE_STRING device_name = {};
	RtlInitUnicodeString(&device_name, L"\\Device\\adrenochrome");

	PDEVICE_OBJECT device_object = nullptr;
	NTSTATUS status = IoCreateDevice(driver_object, 0, &device_name, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &device_object);

	if (!NT_SUCCESS(status)) {
		debug_print("[-] Failed to create device object\n");
		return status;
	}

	debug_print("[+] Driver device successfully created\n");

	UNICODE_STRING symbolic_link = {};
	RtlInitUnicodeString(&symbolic_link, L"\\DosDevices\\adrenochrome");

	status = IoCreateSymbolicLink(&symbolic_link, &device_name);

	if (!NT_SUCCESS(status)) {
		debug_print("[-] Failed to create symbolic link\n");
		IoDeleteDevice(device_object);
		return status;
	}

	debug_print("[+] Driver symlink successfully established\n");

	SetFlag(device_object->Flags, DO_BUFFERED_IO);

	driver_object->MajorFunction[IRP_MJ_CREATE] = driver::create;
	driver_object->MajorFunction[IRP_MJ_CLOSE] = driver::close;
	driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = driver::device_control;

	ClearFlag(device_object->Flags, DO_DEVICE_INITIALIZING);

	debug_print("[+] Driver initialized successfully \n");

	return status;
}
 
NTSTATUS DriverEntry(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path) {

	debug_print("[+] adrenochrome here \n");

	UNICODE_STRING driver_name = {};
	RtlInitUnicodeString(&driver_name, L"\\Driver\\adrenochrome");

	return IoCreateDriver(&driver_name, &driver_entry);
}