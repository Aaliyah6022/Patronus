#pragma warning (disable : 4047 4024 )

#include "communication.h"
#include "logger.h"
#include "header.h"
#include "memory.h"

NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	DebugMessage("CreateCall was called, connection enstablished!\n");

	return STATUS_SUCCESS;
}

NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	DebugMessage("Connection Terminated!\n");

	return STATUS_SUCCESS;
}

NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	
	NTSTATUS Status = STATUS_UNSUCCESSFUL;
	ULONG ByteIO = 0;
	
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	ULONG ControlCode = stack->Parameters.DeviceIoControl.IoControlCode;
	/*
	if (ControlCode == IO_GET_CLIENTADDRESS)
	{
		PULONG OutPut = (PULONG)Irp->AssociatedIrp.SystemBuffer;
		*OutPut = GameBaseAddress;

		DebugMessage("ClientAddress requested!\n");

		Status = STATUS_SUCCESS;
		ByteIO = sizeof(*OutPut);
	}*/
	if (ControlCode == IO_READ_REQUEST)
	{
		PKERNEL_READ_REQUEST ReadInput = (PKERNEL_READ_REQUEST)Irp->AssociatedIrp.SystemBuffer;

		PEPROCESS Process;

		if (NT_SUCCESS(PsLookupProcessByProcessId(ReadInput->ProcessId, &Process)))
		{
			KernelReadVirtualMemory(Process, ReadInput->Adress, ReadInput->pBuff, ReadInput->Size);
			Status = STATUS_SUCCESS;
			ByteIO = sizeof(KERNEL_READ_REQUEST);

			DbgPrintEx(0, 0, "Read Params:  %lu, %#010x \n", ReadInput->ProcessId, ReadInput->Adress);

			Status = STATUS_SUCCESS;
			ByteIO = sizeof(KERNEL_READ_REQUEST);
		}
	}
	else if (ControlCode == IO_WRITE_REQUEST)
	{
		PKERNEL_WRITE_REQUEST WriteInput = (PKERNEL_WRITE_REQUEST)Irp->AssociatedIrp.SystemBuffer;

		PEPROCESS Process;

		if (NT_SUCCESS(PsLookupProcessByProcessId(WriteInput->ProcessId, &Process)))
		{
			KernelWriteVirtualMemory(Process, WriteInput->pBuff, WriteInput->Adress, WriteInput->Size);

			Status = STATUS_SUCCESS;
			ByteIO = sizeof(KERNEL_READ_REQUEST);
		}
	}
	else
	{
		Status = STATUS_INVALID_PARAMETER;
		ByteIO = 0;
	}


	Irp->IoStatus.Status = Status;
	Irp->IoStatus.Information = ByteIO;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}
