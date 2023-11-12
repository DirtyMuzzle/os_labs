#include<windows.h>
#include<stdio.h>

//bool WINAPI 
BOOL WINAPI CtrlHandler(_In_ DWORD dwCtrlType) {
    if (dwCtrlType == CTRL_C_EVENT) {
        printf("Ctrl-C event\n");
        exit(1);
    }
    else if (dwCtrlType = CTRL_CLOSE_EVENT) {
        printf("CTRL-CLOSE event\n");
        exit(2);
    }
    else {
        return FALSE;
    }
}

int main(void) {
    if (SetConsoleCtrlHandler(CtrlHandler, TRUE)) {
        printf("Waiting for signal\n");
        while (TRUE) {}
        return 0;
    }
    else {
        printf("ERROR with setting control handler");
        return 1;
    }
}
