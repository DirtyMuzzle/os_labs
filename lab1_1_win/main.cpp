#include<Windows.h>
#include<stdio.h>

int main(VOID) {
    STARTUPINFO startInfo;
    PROCESS_INFORMATION processInfo;
    DWORD exitCode;
    ZeroMemory(&startInfo, sizeof(startInfo));
    ZeroMemory(&processInfo, sizeof(processInfo));
    if (!CreateProcess(L"C:\\Users\\pavel\\source\\repos\\OS1\\x64\\Debug\\process.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &startInfo, &processInfo)) {
        printf("Creating process is failed\n" + GetLastError());
        return 1;
    }

    WaitForSingleObject(processInfo.hProcess, INFINITE);
    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);
    return 0;
}
