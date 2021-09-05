#pragma warning (disable : 4100 4267)
#include "print_debug.h"
#include "usermode_comm.h"

NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS Status = STATUS_UNSUCCESSFUL;
	ULONG nCopied = 0;
	CHAR *Pong = "pong";

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ULONG ControlCode = stack->Parameters.DeviceIoControl.IoControlCode;
	if (ControlCode == IO_PING_ROOTKIT)
	{
		DebugMessage("ping recv from userland, sending pong\n");
		RtlCopyMemory(Irp->AssociatedIrp.SystemBuffer, Pong, strlen(Irp->AssociatedIrp.SystemBuffer));
		nCopied = strlen(Pong);
		Status = STATUS_SUCCESS;
	}

	Irp->IoStatus.Status = Status;
	Irp->IoStatus.Information = nCopied;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return Status;
}

NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	DebugMessage("conn with usermode proc established\n");

	return STATUS_SUCCESS;
}

NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	DebugMessage("conn with usermode proc terminated\n");

	return STATUS_SUCCESS;
}