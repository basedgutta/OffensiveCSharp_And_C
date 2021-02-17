#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wincrypt.h>
#pragma comment (lib, "crypt32.lib")
#pragma comment (lib, "advapi32")
#include <psapi.h>
#include "helpers.h"

#pragma comment(linker, "/entry:WinMain")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

  MEMORYSTATUSEX memoryStatus;
  memoryStatus.dwLength = sizeof(memoryStatus);
  GlobalMemoryStatusEx(&memoryStatus);
  DWORD RAMMB = memoryStatus.ullTotalPhys / 1024 / 1024;
  if (RAMMB < 2048) return false;
  
}
