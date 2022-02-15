#include <string>

#define PATH_ERR 2  // Invalid path error
#define MEM_ERR 3   // Error with memory allocation
#define CLIP_ERR 4  // Error with native Clipboard function

int CopyToClipboard(std::string pathStr);