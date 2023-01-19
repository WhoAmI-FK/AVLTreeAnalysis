#include "Tree.h"
#include <iostream>
#include <string>
#include <random>
#include <cassert>
#include <algorithm>
#include <limits>

constexpr int step = 100;
constexpr int maxlen = 10000;
constexpr int times = 100;

int potentialMain()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	// add data collection
	for (int len = step; len <= maxlen; len += step) {

		//DataContainer sorts;
	//	sorts.init();
		//sorts.len = len;
		std::vector<int> original(len);
		for (int i = 0; i < len; i++)
		{
			original[i] = i;
		}

		std::vector<int> arr;
		std::vector<int> sorted;
		for (int t = 0; t < times; t++)
		{

			std::shuffle(original.begin(), original.end(), gen);

		//	sorts.INS += __time::TimerAPI::get().estimateTime(original, arr, __sorting::SortingTypes::INSERTION_SORT);

		//	sorts.MER += __time::TimerAPI::get().estimateTime(original, arr, __sorting::SortingTypes::MERGE_SORT);

		//	sorts.QUI += __time::TimerAPI::get().estimateTime(original, arr, __sorting::SortingTypes::QUICK_SORT);

		//	sorts.HEP += __time::TimerAPI::get().estimateTime(original, arr, __sorting::SortingTypes::HEAP_SORT);

			//			sorts.INS_B += __time::TimerAPI::get().estimateTime(arr, sorted, __sorting::SortingTypes::INSERTION_SORT);

			//			sorts.MER_B += __time::TimerAPI::get().estimateTime(arr, sorted, __sorting::SortingTypes::MERGE_SORT);

			//			sorts.QUI_B += __time::TimerAPI::get().estimateTime(arr, sorted, __sorting::SortingTypes::QUICK_SORT);

			//			sorts.HEP_B += __time::TimerAPI::get().estimateTime(arr, sorted, __sorting::SortingTypes::HEAP_SORT);
		}

		std::cout
			<< len << " "
		//	<< sorts.INS.count() / times << " "
		//	<< sorts.MER.count() / times << " "
		//	<< sorts.QUI.count() / times << " "
		//	<< sorts.HEP.count() / times << " "
			//			<< sorts.INS_B.count() / times << " "
			//			<< sorts.MER_B.count() / times << " "
			//			<< sorts.QUI_B.count() / times << " "
			//			<< sorts.HEP_B.count() / times << " "
			<< std::endl;

		// collectedData.push_back(sorts);
	}

}

int main()
{
	// test 1
	{
		__trees::AVL::AVLTree<int> A;
		A.insert(4);
		A.insert(2);
		A.insert(5);
		A.insert(3);
		A.insert(7);
		A.insert(1);
		A.insert(6);

		A.print();

		std::cout << "\n\n" << (A.isStored(5) ? "YES" : "NO") << std::endl;
		std::cout << std::endl << "Tree H: " << A.getHeight(A.root);
	}
	std::cout << std::endl << "------------------------------\n\n";
	// Test 2
	{
		__trees::AVL::AVLTree<int> A;
		A.insert(10);
		A.insert(5);
		A.insert(7);
		A.insert(9);
		A.insert(12);
		A.insert(8);
		A.print();

		std::cout << "\n\n" << (A.isStored(10) ? "YES" : "NO") << std::endl;
		std::cout << std::endl << "Tree H: " << A.getHeight(A.root);
	}

	std::cout << std::endl << "------------------------------\n\n";
	{
		
		__trees::AVL::AVLTree<std::string> A;
		A.insert("abcd");
		A.insert("bbbb");
		A.insert("dasd");
		A.print();
	//	std::cout << std::endl << "Tree H: " << A.getHeight(A.root); 
	}


	return 0;
}

