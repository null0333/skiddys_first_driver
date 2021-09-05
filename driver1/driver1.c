#pragma warning (disable : 4100)
#include "driver1.h"
#include "print_debug.h"
#include "data.h"
#include "usermode_comm.h"


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverOject, PUNICODE_STRING pRegistryPath)
{
	pDriverOject->DriverUnload = UnloadDriver;

	RtlInitUnicodeString(&dev, L"\\Device\\rootkit_ping");
	RtlInitUnicodeString(&dos, L"\\DosDevices\\rootkit_ping");

	IoCreateDevice(pDriverOject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	IoCreateSymbolicLink(&dos, &dev);

	pDriverOject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;
	pDriverOject->MajorFunction[IRP_MJ_CREATE] = CreateCall;
	pDriverOject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;

	pDeviceObject->Flags |= DO_DIRECT_IO;
	pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	DebugMessage("loaded nulls shitty driver lol\n");

	return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject)
{
	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(pDriverObject->DeviceObject);

	DebugMessage("unloaded nulls shitty driver lol\n");

	return STATUS_SUCCESS;
}