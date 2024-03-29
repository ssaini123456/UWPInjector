#pragma once
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "Permission.h"

const char* path = ""; //note:edit this when the final product is ready
const std::wstring& winName = "";
size_t pathsize = strlen(path);
std::wstring bindStr(&path[0], &path[pathsize]);

class Injector {
private:
	static uint32_t GetPid() {
		uint32_t currId = 0;
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (snapshot != INVALID_HANDLE_VALUE) {
			PROCESSENTRY32 pEntry;
			pEntry.dwSize = sizeof(pEntry);
			if (Process32First(snapshot, &pEntry)) {
				do {
					if (!winName.compare(pEntry.szExeFile)) {
						currId = pEntry.th32ProcessID;
						break;
					}
				} while (Process32Next(snapshot, &pEntry));
			}
		}
		CloseHandle(snapshot);
		return currId;
	}

	static int Inject(const char* path) {
		uint32_t pId = GetPid();
		HANDLE procHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pId);
		if (procHandle && procHandle != INVALID_HANDLE_VALUE) {
			void* allocatedBytes = VirtualAllocEx(procHandle, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			WriteProcessMemory(procHandle, allocatedBytes, path, strlen(path) + 1, 0);
			HANDLE hThread = CreateRemoteThread(procHandle, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, allocatedBytes, 0, 0);
			if (hThread) { CloseHandle(hThread); }

			if (procHandle) { CloseHandle(procHandle); }
		}


		return 0;
	}

public:
	static void performinjection() {
		SetAccessControl(bindStr, L"S-1-15-2-1");
		Inject(path);
	}

};
