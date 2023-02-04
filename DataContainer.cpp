#include "DataContainer.h"
#include <fstream>
#include <sstream>

void DataContainer::init()
{
	INS_AVL = std::chrono::nanoseconds(0);
	INS_BST = std::chrono::nanoseconds(0);

	SEARCH_AVL = std::chrono::nanoseconds(0);
	SEARCH_BST = std::chrono::nanoseconds(0);

	SEARCH_NOIN_AVL = std::chrono::nanoseconds(0);
	SEARCH_NOIN_BST = std::chrono::nanoseconds(0);
}

void DataContainer::outputDataToFile(const std::vector<DataContainer>& cont, int div, FileType type)
{
	std::ofstream out;
	

	switch (type) {
	case FileType::RDATA:
		out.open("resultsRIns.txt", std::ios::out | std::ios::trunc);
		out << "size AVL BST" << std::endl;
		for (const auto& v : cont)
		{
			out << v.len << " "
				<< v.INS_AVL.count() / div << " "
				<< v.INS_BST.count() / div << " "
				<< std::endl;
		}
		out.close();

		out.open("resultsRSearch.txt", std::ios::out | std::ios::trunc);
		out << "size AVL BST" << std::endl;
		for (const auto& v : cont)
		{
			out << v.len << " "
				<< v.SEARCH_AVL.count() / div << " "
				<< v.SEARCH_BST.count() / div << " "
				<< std::endl;
		}
		out.close();

		out.open("resultsRNotInSearch.txt", std::ios::out | std::ios::trunc);
		out << "size AVL BST" << std::endl;
		for (const auto& v : cont)
		{
			out << v.len << " "
				<< v.SEARCH_NOIN_AVL.count() / div << " "
				<< v.SEARCH_NOIN_BST.count() / div << " "
				<< std::endl;
		}
		out.close();
		break;
	case FileType::ODATA:
		out.open("resultsOIns.txt", std::ios::out | std::ios::trunc);
		out << "size AVL BST" << std::endl;
		for (const auto& v : cont)
		{
			out << v.len << " "
				<< v.INS_AVL.count() / div << " "
				<< v.INS_BST.count() / div << " "
				<< std::endl;
		}
		out.close();

		out.open("resultsOSearch.txt", std::ios::out | std::ios::trunc);
		out << "size AVL BST" << std::endl;
		for (const auto& v : cont)
		{
			out << v.len << " "
				<< v.SEARCH_AVL.count() / div << " "
				<< v.SEARCH_BST.count() / div << " "
				<< std::endl;
		}
		out.close();

		out.open("resultsONotInSearch.txt", std::ios::out | std::ios::trunc);
		out << "size AVL BST" << std::endl;
		for (const auto& v : cont)
		{
			out << v.len << " "
				<< v.SEARCH_NOIN_AVL.count() / div << " "
				<< v.SEARCH_NOIN_BST.count() / div << " "
				<< std::endl;
		}
		out.close();
		break;
	case FileType::NODATA:
		out.open("resultsNOIns.txt", std::ios::out | std::ios::trunc);
		out << "size AVL BST" << std::endl;
		for (const auto& v : cont)
		{
			out << v.len << " "
				<< v.INS_AVL.count() / div << " "
				<< v.INS_BST.count() / div << " "
				<< std::endl;
		}
		out.close();

		out.open("resultsNOSearch.txt", std::ios::out | std::ios::trunc);
		out << "size AVL BST" << std::endl;
		for (const auto& v : cont)
		{
			out << v.len << " "
				<< v.SEARCH_AVL.count() / div << " "
				<< v.SEARCH_BST.count() / div << " "
				<< std::endl;
		}
		out.close();

		out.open("resultsNONotInSearch.txt", std::ios::out | std::ios::trunc);
		out << "size AVL BST" << std::endl;
		for (const auto& v : cont)
		{
			out << v.len << " "
				<< v.SEARCH_NOIN_AVL.count() / div << " "
				<< v.SEARCH_NOIN_BST.count() / div << " "
				<< std::endl;
		}
		out.close();
		break;
	}
}