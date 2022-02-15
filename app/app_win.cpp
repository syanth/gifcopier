#define _UNICODE
#define UNICODE
#include <Windows.h>
#include <Shlobj_core.h>
#include "clipapp.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <stdlib.h>
#include <crtdbg.h>
#endif

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
    if (!hdrop) return MEM_ERR;
    DROPFILES* df = (DROPFILES*)GlobalLock(hdrop);
    if (!df) return MEM_ERR;
    df->pFiles    = sizeof(DROPFILES);
    df->fWide     = TRUE;

    // Copy over the path
    wchar_t* dstStart = (wchar_t*)&df[1]; // Offset!
	wcscpy(dstStart, path);
    GlobalUnlock(hdrop);

    // Ownership of allocated memory transferred to OS, no need to free it
    OpenClipboard(NULL);
    EmptyClipboard();
    if (!SetClipboardData(CF_HDROP, df)) return CLIP_ERR;
    CloseClipboard();

    delete[] path;
	return 0;
}