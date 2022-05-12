#pragma once
#pragma warning(disable: 6001 4244)
#include "communication.hpp"

class KernelInterface
{
public:
	HANDLE hDriver;

	KernelInterface(LPCSTR RegistryPath)
	{
		hDriver = CreateFileA(RegistryPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	}

	DWORD GetClientAddress()
	{
		if (hDriver == INVALID_HANDLE_VALUE)
		{
			return 0;
		}

		ULONG Address;
		DWORD Bytes;

		if (DeviceIoControl(hDriver, IO_GET_CLIENTADDRESS, &Address, sizeof(Address), &Address, sizeof(Address), &Bytes, NULL))
		{
			return Address;
		}

		return 0;
	}

	template <typename type>
	type ReadVirtualMemory(ULONG processId, ULONG ReadAddress, SIZE_T Size)
	{
		type Buffer;

		if (hDriver == INVALID_HANDLE_VALUE)
		{
			return Buffer;
		}

		KERNEL_READ_REQUEST ReadRequest;

		ReadRequest.ProcessId = processId;
		ReadRequest.Address = ReadAddress;
		ReadRequest.pBuff = &Buffer;
		ReadRequest.Size = Size;

		if (DeviceIoControl(hDriver, IO_READ_REQUEST, &ReadRequest, sizeof(ReadRequest), &ReadRequest, sizeof(ReadRequest), 0, 0))
		{
			return Buffer;
		}

		return Buffer;
	}

	template <typename type>
	bool WriteVirtualMemory(ULONG processId, ULONG WriteAddress, type WriteValue, SIZE_T Size)
	{
		if (hDriver == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		DWORD Bytes;

		KERNEL_WRITE_REQUEST WriteRequest;

		WriteRequest.ProcessId = processId;
		WriteRequest.Address = ReadAddress;
		WriteRequest.pBuff = &WriteValue;
		WriteRequest.Size = Size;

		if (DeviceIoControl(hDriver, IO_WRITE_REQUEST, &WriteRequest, sizeof(WriteRequest), 0, 0, &Bytes, NULL)
		{
			return true;
		}

		return false;
	}
};
