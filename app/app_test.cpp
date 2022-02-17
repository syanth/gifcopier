#include "gtest/gtest.h"
#include "clipapp.h"

TEST(CopyToClipboardTest, CopyLocalClip) {
	std::string pathStr = "C:\\dev\\test\\copperfield.mp4"; // Temp path for testing
	//std::string pathStr = "file:///Users/syanth/Documents/jon.mp4";
	EXPECT_EQ(CopyToClipboard(pathStr), 0);
}