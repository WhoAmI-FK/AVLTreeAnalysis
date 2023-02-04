#include "DataMgr.h"


void DataMgr::loadFromFile(const std::string& fileName, const std::int64_t& numOfLines)
{
	_container.clear();
	auto count = numOfLines;
	std::ifstream stream;
	stream.open(fileName);
	std::string holder;

	while (stream >> holder && count > 0)
	{
		_container.push_back(holder);
		count--;
	}

	stream.close();
}