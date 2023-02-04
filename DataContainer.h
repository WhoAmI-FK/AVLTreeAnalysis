#pragma once
#include <chrono>
#include <fstream>
#include <vector>

enum class FileType {
	RDATA = 0,
	ODATA = 1,
	NODATA = 2
};

struct DataContainer
{
	int len;
	std::chrono::nanoseconds INS_AVL;
	std::chrono::nanoseconds INS_BST;
	
	std::chrono::nanoseconds SEARCH_AVL;
	std::chrono::nanoseconds SEARCH_BST;

	std::chrono::nanoseconds SEARCH_NOIN_AVL;
	std::chrono::nanoseconds SEARCH_NOIN_BST;

	void init();

	static void outputDataToFile(const std::vector<DataContainer>& cont, int div, FileType type);
};