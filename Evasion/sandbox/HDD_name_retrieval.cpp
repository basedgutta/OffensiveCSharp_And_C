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

  // check the HDD
  HDEVINFO hDeviceInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_DISKDRIVE, 0, 0, DIGCF_PRESENT);
  SP_DEVINFO_DATA deviceInfoData;
  deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
  SetupDiEnumDeviceInfo(hDeviceInfo, 0, &deviceInfoData);
  DWORD propertyBufferSize;
  SetupDiGetDeviceRegistryPropertyW(hDeviceInfo, &deviceInfoData, SPDRP_FRIENDLYNAME, NULL, NULL, 0, &propertyBufferSize);
  PWSTR HDDName = (PWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, propertyBufferSize);
  SetupDiGetDeviceRegistryPropertyW(hDeviceInfo, &deviceInfoData, SPDRP_FRIENDLYNAME, NULL, (PBYTE)HDDName, propertyBufferSize, NULL);
  CharUpperW(HDDName);
  if (wcsstr(HDDName, L"VBOX")) return false;
  
  

}
