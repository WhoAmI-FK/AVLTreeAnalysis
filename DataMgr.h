#pragma once
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>

struct DataMgr
{
	std::vector<std::string> _container;


	void loadFromFile(const std::string& fileName, const std::int64_t& numOfLines);
};