#include "clipapp.h"

int main()
{
    #ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif

    std::string pathStr = "C:\\dev\\test\\copperfield.mp4"; // Temp path for testing
    //std::string pathStr = "file:///Users/syanth/Documents/jon.mp4";
    CopyToClipboard(pathStr);
}