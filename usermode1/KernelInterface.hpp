#pragma once
#include <iostream>
#include "kernelmode_comm.hpp"

#define PONG_BUFSIZ 10

class KernelInterface
{
public:
	HANDLE hDriver;

	KernelInterface(LPCSTR RegistryPath)
	{
		hDriver = CreateFileA(RegistryPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
		//hDriver = CreateFileW(RegistryPath, GENERIC_ALL, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, 0);
	}

	INT PingRootkit()
	{
		if (hDriver == INVALID_HANDLE_VALUE)
		{
			std::cout << "failed to open symlink\n";
			return -1;
		}

		CHAR msg[PONG_BUFSIZ] = {0};
		CHAR msg_out[PONG_BUFSIZ] = {0};
		DWORD nRead;

		if (DeviceIoControl(hDriver, IO_PING_ROOTKIT, msg, sizeof(msg), msg_out, sizeof(msg_out), &nRead, NULL))
		{
			for (int i = 0; i < strlen(msg); i++) 
			{
				std::cout << msg[i];
			}
			std::cout << std::endl;

			return 0;
		}

		return -1;
	}
};