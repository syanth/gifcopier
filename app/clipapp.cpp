#include "clipapp.h"

std::ofstream logfile;

int main()
{
    #ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif
        
    logfile.open("clipapp.log");

    std::string URL = getURL();
    logfile << "Received URL: " + URL;
    
    if (DownloadClip(URL)) LogError(FILE_ERR);
    fs::path clip = "clip.mp4";
    fs::path p = fs::current_path() / clip;
    if (CopyToClipboard(p.string())) LogError(CLIP_ERR);

    SendStatus(true);

    logfile.close();
}

std::string getURL() {
    char lenBytes[4];
    std::cin.read(lenBytes, 4);
    unsigned int msgLen = *reinterpret_cast<unsigned int*>(lenBytes);
    char* msg = new char[msgLen+1];
    msg[msgLen] = '\0';
    std::cin.read(msg, msgLen);
    std::string msgStr(msg);
    delete[] msg;

    // Actual message string is between quotations, rest is gibberish
    size_t end = msgStr.find_last_of("\"");
    std::string msgTrim = msgStr.substr(9, end - 9);
    return msgTrim;
}

void SendStatus(bool success) {
    std::string msg;
    if (success) msg = "{\"text\":\"Successful copy.\"}";
    else msg = "{\"text\":\"Failed copy.\"}";
    unsigned int msgLen = msg.length();
    char* lenBytes = reinterpret_cast<char*>(&msgLen);
    std::cout.write(lenBytes, 4);
    std::cout << msg << std::flush;
}

void LogError(int errorCode) {
    if (errorCode < 10) logfile << "Error.\n";
    else if (errorCode < 20) logfile << "Error copying file to clipboard.\n";
    else if (errorCode < 30) logfile << "Error downloading clip.\n";
    logfile << "Exiting with code " + std::to_string(errorCode) + ".\n";    
    logfile.close();
    exit(EXIT_FAILURE);
}