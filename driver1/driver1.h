#pragma once
#include <ntifs.h>

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverOject, PUNICODE_STRING pRegistryPath);

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverOject);