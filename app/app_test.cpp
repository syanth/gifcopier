#include "gtest/gtest.h"
#include "clipapp.h"

TEST(CopyToClipboardTest, CopyEmpty) {
	EXPECT_EQ(CopyToClipboard(""), 0);
}