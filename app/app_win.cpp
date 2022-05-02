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

int DownloadClip(std::string URL) {
    system("del /q clip.gif");
    system("del /q clip.mp4");
    if (URL.find("mp4") == -1) {
        std::string command = "curl -o clip.gif \"" + URL + "\"";
        system(command.c_str());
        // Converting the GIF to MP4.
        // faststart for browsers to play as it loads, yuv420p is the most common pixel format
        // Crop to get dimensions divisible by 2 for H.264 (We will only lose at most 1 line of pixels)
        system("ffmpeg -i clip.gif -movflags faststart -pix_fmt yuv420p -vf \"crop = trunc(iw / 2) * 2:trunc(ih / 2) * 2\" clip.mp4");
    }
    else
    {
        std::string command = "curl -o clip.mp4 \"" + URL + "\"";
        system(command.c_str());
    }   
    // Verify file is non-empty
    fs::path clip = "clip.mp4";
    fs::path p = fs::current_path() / clip;
    if (fs::file_size(p)) return 0;
    return FILE_ERR;
}