#include "gtest/gtest.h"
#include "clipapp.h"
#include "Windows.h"
#include <iostream>

TEST(CopyToClipboardTest, CopyLocalClip) {
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(NULL, path, MAX_PATH);
	std::wstring pathWstr(path);

	size_t srcPath = pathWstr.find(L"build");
	pathWstr.erase(srcPath);
	pathWstr.append(L"tests\\copperfield.mp4");

	std::string pathStr(pathWstr.begin(), pathWstr.end());
	std::cout << pathStr;

	EXPECT_EQ(CopyToClipboard(pathStr), 0);
}