#pragma once
#include "Tree.h"
#include <cassert>
#include <vector>
#include <cstdint>
#include <random>

#define FROM -1000000
#define TO 1000000

class Tester
{
public:
	enum class TCs {
		TC1 = 1,
		TC2 // I combine two tests in one just to ease the process
	};

	std::vector<int> _dataCont;
	int numOfNodes;
	Tester()
	{
		numOfNodes = 0;
	}

	__trees::AVL::AVLTree<int> A;
	
	int verify()
	{
		exec(static_cast<TCs>(1));
		exec(static_cast<TCs>(2));
		return 0;
	}

	int TC1(__trees::AVL::AVLNode<int>* p)
	{
		if (p)
		{
			int l = TC1(p->left);
			int r = TC1(p->right);
			assert(p->balanceFactor > -2 && p->balanceFactor < 2);
			assert(A.BF(p) == p->balanceFactor);

			return std::max(l, r) + 1;
		}
		return 0;
	}

	void TC2()
	{
		int supMax = getMaxElFromTree();
		int checkedMax = supMax;
		checkMax(A.root, checkedMax);
		assert(supMax == checkedMax);
		assert(numOfNodes == (TO - FROM + 1));
	}

	int getMaxElFromTree()
	{
		__trees::AVL::AVLNode<int>* tmp = A.root;

		while (tmp->right != nullptr)
		{
			tmp = tmp->right;
		}
		return tmp->val;
	}


	void checkMax(__trees::AVL::AVLNode<int>* ptr,int& max)
	{
		if (ptr == nullptr)
		{
			return;
		}
		numOfNodes++; // to check num of nodes 
		max = max > ptr->val ? max : ptr->val;
		checkMax(ptr->left, max);
		checkMax(ptr->right, max);
	}

	void exec(TCs tcNum)
	{
		switch (tcNum)
		{
		case TCs::TC1:
			insertGenDataToTree();
			TC1(A.root);
			break;
		case TCs::TC2:
			TC2();
			break;
		}
	}

	void randomGenToContainer(const std::int64_t& from, const std::int64_t& to)
	{
		assert(to>=from);
		if (!_dataCont.empty())
		{
			_dataCont.clear();
		}
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<std::int64_t> dist(from, to);
		for (std::int64_t i = from; i <= to; i++)
		{
			_dataCont.push_back(dist(gen));
		}
	}
	void insertGenDataToTree()
	{
		A.clear(A.root);
		randomGenToContainer(FROM,TO);
		for (const auto& v : _dataCont)
		{
			A.insert(v);
		}
//		A.print();
	}
};