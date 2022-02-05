#define _UNICODE
#define UNICODE
#include <Windows.h>
#include <Shlobj_core.h>
#include "clipapp.h"

int CopyToClipboard(std::string pathStr) {
    // String Conversion for Windows API
    const char* pathPtr = pathStr.c_str();
    int bufSize = MultiByteToWideChar(CP_UTF8, NULL, pathPtr, -1, NULL, 0);
    wchar_t* path = new wchar_t[bufSize];
    MultiByteToWideChar(CP_UTF8, NULL, pathPtr, -1, path, bufSize);

    // Calculate bytes needed for memory allocation
    int clpSize = sizeof(DROPFILES) + sizeof(wchar_t) * (wcslen(path) + 2); // two \0 needed at the end

    // GlobalAlloc memory so Windows can re-allocate
    HDROP hdrop   = (HDROP)GlobalAlloc(GHND, clpSize);
    DROPFILES* df = (DROPFILES*)GlobalLock(hdrop);
    df->pFiles    = sizeof(DROPFILES);
    df->fWide     = TRUE;

    // Copy over the path
    wchar_t* dstStart = (wchar_t*)&df[1]; // Offset!
	wcscpy(dstStart, path);
    GlobalUnlock(hdrop);

    // Ownership of allocated memory transferred to OS, no need to free it
    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_HDROP, df);
    CloseClipboard();

    delete[] path;
	return 0;
}