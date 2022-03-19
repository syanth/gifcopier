#include "gtest/gtest.h"
#include "clipapp.h"

TEST(CopyToClipboardTest, CopyEmpty) {
	EXPECT_EQ(CopyToClipboard(""), 0);
}

TEST(DownloadClipTest, DownloadImgur) {
    std::string URL = "https://i.imgur.com/FKSBCVT.mp4";
    EXPECT_EQ(DownloadClip(URL), 0);
}

TEST(CopyToClipboardTest, DownloadAndCopy) {
    std::string URL = "https://i.imgur.com/FKSBCVT.mp4";
    DownloadClip(URL);
    fs::path clip = "clip.mp4";
    fs::path p = fs::current_path() / clip;
    EXPECT_EQ(CopyToClipboard(p.string()), 0);
}