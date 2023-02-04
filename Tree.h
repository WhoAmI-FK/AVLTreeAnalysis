#pragma once
#include <iostream>
#include <string>
#include <queue>

namespace __trees {

	enum __height {
		HEIGHT_SAME = 0,
		HEIGHT_CHANGE
	};

	namespace BST {
		template<typename T>
		struct Node {
			Node<T>* left;
			Node<T>* right;
			T value;
			Node()
				: left(nullptr),
				right(nullptr)
			{

			}
		};


		template<typename T>
		struct Tree {
			Node<T>* root = nullptr;

			~Tree()
			{
				clear(root);
			}

			void clear()
			{
				clear(root);
			}

			// for bst tree doesn't work!
			// due to the abundance of recursive func calls
			/*void clear(Node<T>*& ptr)
			{
				if (ptr != nullptr)
				{
					if(ptr->left != nullptr)
					clear(ptr->left);

					if(ptr->right != nullptr)
					clear(ptr->right);

					if (ptr == root)
					{
						auto temp = root;
						root = nullptr;
						delete temp;
					}
					else delete ptr;
				}
		//		root = nullptr;
			}
			*/

			void clear(Node<T>*& ptr)
			{
				if (ptr == nullptr)
				{
					return;
				}

				std::queue<Node<T>*> q;
				q.push(ptr);
				while (!q.empty())
				{
					Node<T>* tmp = q.front();
					q.pop();
					if (tmp->left)
					{
						q.push(tmp->left);
					}

					if (tmp->right)
					{
						q.push(tmp->right);
					}
					delete tmp;
				}
				root = nullptr;
			}

			void insert(T v)
			{
				Node<T>* parent = nullptr;
				Node<T>* ptr = root;
				while (ptr != nullptr)
				{
					if (v < ptr->value)
					{
						parent = ptr;
						ptr = ptr->left;
					}
					else {
						parent = ptr;
						ptr = ptr->right;
					}
				}
				Node<T>* inserted = new Node<T>;
				inserted->value = v;
				if (parent == nullptr)
				{
					root = inserted;
				}
				else {
					if (v < parent->value)
					{
						parent->left = inserted;
					}
					else {
						parent->right = inserted;
					}
				}
			}

			// was remade from recursive to iterative
			bool isStored(Node<T>* ptr, const T& val)
			{
				while (ptr != nullptr)
				{
					if (ptr->value == val)
					{
						return true;
					}
					else if (val > ptr->value)
					{
						ptr = ptr->right;
					}
					else {
						ptr = ptr->left;
					}
				}
				return false;
			}

			bool isStored(const T& val)
			{

				return isStored(root, val);
			}
		};
	}

	namespace AVL {
		// TODO
		// rr_rotation done 
		// ll_rotation done 
		// lr_rotation done 
		// rl_rotation done
		// balance_factor + insert : 

		template<typename T>
		struct AVLNode {
			T val;
			int balanceFactor;
			AVLNode<T>* left;
			AVLNode<T>* right;
			AVLNode(const T& ref)
			{
				val = ref;
				left = right = nullptr;
				balanceFactor = 0;
			}
		};

		template<typename T>
		struct AVLTree {
			AVLNode<T>* root;
			AVLTree() {
				root = nullptr;
			}

			~AVLTree()
			{
				clear(root);
			}

			void clear()
			{
				clear(root);
			}

			void clear(AVLNode<T>*& ptr)
			{
				if (ptr != nullptr)
				{
					clear(ptr->left);
					clear(ptr->right);
					if (ptr == root)
					{
						auto temp = root;
						root = nullptr;
						delete temp;
					}else delete ptr;
				}
//				root = nullptr;
			}
			
			void insert(AVLNode<T>*& ptr, const T& v, int& change)
			{
				if (ptr == nullptr) {
					ptr = new AVLNode<T>(v);
					change = __height::HEIGHT_CHANGE;
					return;
				}
				if (ptr->val >= v) {
					insert(ptr->left, v, change);
					change = change < 0 ? change : -change;
				
				}else{
					insert(ptr->right, v, change);
					change = change > 0 ? change : -change;
				}
				// recalc BalanceFactor
				ptr->balanceFactor += change;

				if (ptr->balanceFactor == -2) {
					if (ptr->left->balanceFactor == -1)
					{
						ptr = lLeftRotate(ptr,change);
					}
					else if (ptr->left->balanceFactor == 1)
					{
						ptr = lRightRotate(ptr,change);
					}
				}else if (ptr->balanceFactor == 2) {
					if (ptr->right->balanceFactor == 1)
					{
						ptr = rRightRotate(ptr,change);
					}
					else if (ptr->right->balanceFactor == -1)
					{
						ptr = rLeftRotate(ptr,change);
					}
				}
				if (ptr->balanceFactor == 0)
				{
					change = __height::HEIGHT_SAME;
					return;
				}
			}

			void insert(T v)
			{
				int change = HEIGHT_CHANGE;
				insert(root, v, change);
			}

			int BF(AVLNode<T>* ptr)
			{
				return getHeight(ptr->right) - getHeight(ptr->left);
			
				// BF(X) < 0 is called "left-heavy"
				// BF(X) > 0 is called "right-heavy"
				// BF(X) = 0 is called "balanced"

			}

			AVLNode<T>* rRightRotate(AVLNode<T>* ptr, int& change)
			{ // Left Rotation
				AVLNode<T>* tmp = ptr->right;
				if (ptr->right->balanceFactor == 0)
				{
					change = HEIGHT_SAME;
				}
				else {
					change = HEIGHT_CHANGE;
				}
				ptr->right = tmp->left;
				tmp->left = ptr;
				ptr->balanceFactor -= (1 + std::max(tmp->balanceFactor, 0));
				tmp->balanceFactor -= (1 - std::min(ptr->balanceFactor, 0));
				return tmp;
			}

			AVLNode<T>* lLeftRotate(AVLNode<T>* ptr, int& change)
			{ // Right Rotation
				AVLNode<T>* tmp = ptr->left;
				if (ptr->left->balanceFactor == 0)
				{
					change = HEIGHT_SAME;
				}
				else {
					change = HEIGHT_CHANGE;
				}
				ptr->left = tmp->right;
				tmp->right = ptr;
				ptr->balanceFactor += (1 - std::min(tmp->balanceFactor, 0));
				tmp->balanceFactor += (1 + std::max(ptr->balanceFactor, 0));
				return tmp;
			}

			AVLNode<T>* lRightRotate(AVLNode<T>* ptr, int& change)
			{ // LEFT -> Right rotates
				AVLNode<T>* tmp = ptr->left;
				ptr->left = rRightRotate(tmp, change);
				AVLNode<T>* ret = lLeftRotate(ptr, change);
				change = HEIGHT_CHANGE;
				return ret;
			}

			AVLNode<T>* rLeftRotate(AVLNode<T>* ptr, int& change)
			{ // right -> left rotates
				AVLNode<T>* tmp = ptr->right;
				ptr->right = lLeftRotate(tmp, change);
				AVLNode<T>* ret = rRightRotate(ptr, change);
				change = HEIGHT_CHANGE;
				return ret;
			}

			bool isStored(AVLNode<T>* ptr, const T& val)
			{
				while (ptr != nullptr)
				{
					if (ptr->val == val)
					{
						return true;
					}
					else if (val > ptr->val)
					{
						ptr = ptr->right;
					}
					else {
						ptr = ptr->left;
					}
				}
				return false;
			}

			int getHeight(AVLNode<T>* node) {
				int height = 0;
				if (node != nullptr)
				{
					int l_height = getHeight(node->left);
					int r_height = getHeight(node->right);
					height = std::max(l_height, r_height) + 1;
				}
				return height;
			}

			bool isStored(const T& val)
			{

				return isStored(root, val);
			}

			void print()
			{
				print(root, 1);
			}

			void print(AVLNode<T>* ptr, int level)
			{
				if (ptr != nullptr)
				{
					print(ptr->right, level + 1);
					std::cout << std::endl;
					if (ptr == root)
						std::cout << "Root ->";
						for (int i = 0; i < level && ptr != root; i++)
							std::cout << "        ";
						std::cout << ptr->val << ",BF:" << ptr->balanceFactor;
						print(ptr->left, level + 1);
				}
			}

		};
	}
}