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

  OBJECT_ATTRIBUTES objectAttributes;
  UNICODE_STRING uDeviceName;
  RtlSecureZeroMemory(&uDeviceName, sizeof(uDeviceName));
  RtlInitUnicodeString(&uDeviceName, L"\\Device\\VBoxGuest"); 
  InitializeObjectAttributes(&objectAttributes, &uDeviceName, OBJ_CASE_INSENSITIVE, 0, NULL);
  HANDLE hDevice = NULL;
  IO_STATUS_BLOCK ioStatusBlock;
  NTSTATUS status = NtCreateFile(&hDevice, GENERIC_READ, &objectAttributes, &ioStatusBlock, NULL, 0, 0, FILE_OPEN, 0, NULL, 0);
  if (NT_SUCCESS(status)) return false;
}
