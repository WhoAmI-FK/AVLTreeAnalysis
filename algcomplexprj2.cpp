#include "Tree.h"
#include <iostream>
#include <string>
#include <random>
#include <cassert>
#include <algorithm>
#include <functional>
#include "DataMgr.h"
#include "Test.h"
#include "DataContainer.h"

#define FILE_NAME "wordlist.txt"

constexpr int step = 100;
constexpr int numOfLines =10000;
constexpr int times = 100;
constexpr double coeffNonSortedEl = 0.1;


std::vector<std::string> nonListBelongedWords
=
{
	"guts",
	"goku",
	"sharingan",
	"huskar",
	"cplusplus",
	"barbarosa",
	"samurai",
	"sensei",
	"valhala"
};

/*
Do this on three input data sets:
1. random data,
2. ordered data,
3. nearly ordered data
*/

void getRandomData(DataMgr& d, const std::string& fileName, int numLines)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	d.loadFromFile(fileName, numLines);
	std::shuffle(d._container.begin(), d._container.end(), gen);
}


void getOrderedData(DataMgr& d, const std::string& fileName, int numLines)
{
	d.loadFromFile(fileName, numLines);
	std::sort(d._container.begin(), d._container.end());
}

void getNearlyOrderedData(DataMgr& d, const std::string& fileName, int numLines)
{

	// 1. load data
	// 2. sort array
	// 3. swap random elements in the array acc to coef
	d.loadFromFile(fileName, numLines);
	std::sort(d._container.begin(), d._container.end());
	int numOfSwaps = d._container.size() * coeffNonSortedEl;
	//	std::cout << "\n----------------------\n" << numOfSwaps << "\n----------------------\n";
	std::random_device rd;
	std::mt19937 gen(rd());
	int a, b;
	std::uniform_int_distribution<int> dist(0, d._container.size() - 1);
	for (int i = 0; i < numOfSwaps; i++)
	{
		a = dist(gen);
		b = dist(gen);
		std::swap(d._container[a], d._container[b]);
	}	

}

std::string getRandWordFromDataSet(DataMgr& d)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, d._container.size() - 1);
	return d._container[(dist(gen))];
}

std::string getRandWordNoFromDataSet()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, nonListBelongedWords.size()-1);
	return nonListBelongedWords[(dist(gen))];
}

int main()
{
	// firstly for insertion
	// add data collection
	std::vector<std::function<void(DataMgr&, const std::string&, int)>> getData
		=
	{
		getRandomData,
		getOrderedData,
		getNearlyOrderedData
	};
	int dataTypeIndex = 0;
	for (auto& get : getData) {
		__trees::AVL::AVLTree<std::string> AVLT;
		__trees::BST::Tree<std::string> BSTT;
		std::vector<DataContainer> collectedData;
		for (int len = step; len <= numOfLines; len += step) {
			DataMgr m;
			DataContainer dataSet;
			dataSet.init();
			dataSet.len = len;
			for (int t = 0; t < times; t++)
			{
				if (dataTypeIndex != 2) continue;
				get(m, FILE_NAME, len);
				for (int t = 0; t < m._container.size() - 1; t++)
				{
					AVLT.insert(m._container[t]);
					BSTT.insert(m._container[t]);
				}
				auto begin = std::chrono::steady_clock::now();
				AVLT.insert(m._container[m._container.size() - 1]);
				auto end = std::chrono::steady_clock::now();
				dataSet.INS_AVL += (end - begin);
				 
				begin = std::chrono::steady_clock::now();
				BSTT.insert(m._container[m._container.size() - 1]);
				end = std::chrono::steady_clock::now();
				dataSet.INS_BST += (end - begin);

				std::string wordToSearch = getRandWordFromDataSet(m);

				begin = std::chrono::steady_clock::now();
				bool b = AVLT.isStored(wordToSearch);
				end = std::chrono::steady_clock::now();
				assert(b);
				dataSet.SEARCH_AVL += (end - begin);

				begin = std::chrono::steady_clock::now();
			    BSTT.isStored(wordToSearch);
				end = std::chrono::steady_clock::now();
				assert(b);
				dataSet.SEARCH_BST += (end - begin);

				wordToSearch = getRandWordNoFromDataSet();

				begin = std::chrono::steady_clock::now();
				b = AVLT.isStored(wordToSearch);
				end = std::chrono::steady_clock::now();
				assert(!b);
				dataSet.SEARCH_NOIN_AVL += (end - begin);

				wordToSearch = getRandWordNoFromDataSet();
				begin = std::chrono::steady_clock::now();
				b = BSTT.isStored(wordToSearch);
				end = std::chrono::steady_clock::now();
				assert(!b);
				dataSet.SEARCH_NOIN_BST += (end - begin);


				AVLT.clear();
				BSTT.clear();
			}

			std::cout
				<< len << " "
				<< dataSet.INS_AVL.count() / times << " "
				<< dataSet.INS_BST.count() / times << " "
				<< dataSet.SEARCH_AVL.count() / times << " "
				<< dataSet.SEARCH_BST.count() / times << " "
				<< dataSet.SEARCH_NOIN_AVL.count() / times << " "
				<< dataSet.SEARCH_NOIN_BST.count() / times << " "
				<< std::endl;
			collectedData.push_back(dataSet);
		}
		DataContainer::outputDataToFile(collectedData, times, static_cast<FileType>(dataTypeIndex));
		dataTypeIndex++;
		collectedData.clear();
	}
	return 0;
}