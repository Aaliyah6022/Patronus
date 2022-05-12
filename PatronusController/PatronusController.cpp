#include <iostream>
#include "kernelinterface.hpp"

HWND window = nullptr;
unsigned long threadId, processId = 0;



int main()
{
   
    KernelInterface Driver = KernelInterface("\\\\.\\patronus");

    /*
    ULONG address = Driver.GetClientAddress();

    std::cout << "game address: " << address << std::endl;
    */
    
    while (!window)
    {
        window = FindWindowA(NULL, "Tiger-Win64-Shipping.exe");
        std::cout << "window: " << window << std::endl;
    }

    
    while (!processId)
    {
        threadId = GetWindowThreadProcessId(window, &processId);
        std::cout << "threadId: " << threadId << std::endl;
        std::cout << "processId: " << processId << std::endl;
    }


    while (true)
    {
        //uint32_t LocalPlayerAdress = Driver.ReadVirtualMemory<uint32_t>(processId, threadId + dwLocalPlayerOffset, sizeof(uint32_t));
    }

}
