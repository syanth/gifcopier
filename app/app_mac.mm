#include <AppKit/AppKit.h>
#include "clipapp.h"

int CopyToClipboard(std::string pathStr) {
    pathStr = "file://" + pathStr;

    NSString *urlNSStr = [NSString stringWithUTF8String:pathStr.c_str()];
    NSURL *URL = [NSURL URLWithString:urlNSStr];

    NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];
    [pasteboard clearContents];
    [pasteboard writeObjects:@[URL]];
    [pasteboard setString:URL.absoluteString forType:NSPasteboardTypeFileURL];

    return 0;
}

int DownloadClip(std::string URL) {
    system("rm -f clip.gif");
    system("rm -f clip.mp4");
    if (!URL.compare(URL.size() - 4, 4, ".gif")) {
        std::string command = "curl -o clip.gif \"" + URL + "\"";
        system(command.c_str());
        // Converting the GIF to MP4.
        // faststart for browsers to play as it loads, yuv420p is the most common pixel format
        // Crop to get dimensions divisible by 2 for H.264 (We will only lose at most 1 line of pixels)
        system("./ffmpeg -i clip.gif -movflags faststart -pix_fmt yuv420p -vf \"crop = trunc(iw / 2) * 2:trunc(ih / 2) * 2\" clip.mp4");
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