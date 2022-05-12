#pragma warning (disable : 4047)

#include "events.h"
#include "logger.h"


PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{
	UNREFERENCED_PARAMETER(ImageInfo);
	UNREFERENCED_PARAMETER(ProcessId);
	
	if (wcsstr(FullImageName->Buffer, L"\\Tiger-Win64-Shipping.exe"))
	{
		//DebugMessage("Game process found.");
		//GameBaseAddress = ImageInfo->ImageBase;
		//DebugMessage("Base adress: %p \n", GameBaseAdress);
		//ProcessID = (ULONG)ProcessId;
		//DebugMessage("Process ID: %p \n", ProcessId);
	}

	return STATUS_SUCCESS;
}