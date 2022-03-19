#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

#define PATH_ERR 11  // Invalid path error
#define MEM_ERR 12   // Error with memory allocation
#define CLIP_ERR 13  // Error with native Clipboard function
#define FILE_ERR 20	// Error with downloading the clip

int CopyToClipboard(std::string pathStr);
std::string getURL();
void SendStatus(bool success);
int DownloadClip(std::string URL);
void OnError(int errorCode);