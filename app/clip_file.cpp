#include "clipapp.h"

int DownloadClip(std::string URL) {
    std::string command = "curl -so clip.mp4 " + URL;
    system(command.c_str());
    // Verify file is non-empty
    fs::path clip = "clip.mp4";
    fs::path p = fs::current_path() / clip;
    if (fs::file_size(p)) return 0;
    return FILE_ERR;
}