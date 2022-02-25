#include <AppKit/AppKit.h>
#include "clipapp.h"

int CopyToClipboard(std::string pathStr) {
    NSString *urlNSStr = [NSString stringWithUTF8String:pathStr.c_str()];
    NSURL *URL = [NSURL URLWithString:urlNSStr];

    NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];
    [pasteboard clearContents];
    [pasteboard writeObjects:@[URL]];
    [pasteboard setString:URL.absoluteString forType:NSPasteboardTypeFileURL];

    return 0;
}