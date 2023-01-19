#pragma once
#include <iostream>
#include <string>

namespace __trees {

	namespace __customClass {

		class CustomString : public std::string
		{

			CustomString(const std::string& str)
				: std::string(str)
			{

			}

			bool operator<(const CustomString& str)
			{

			}

			bool operator>(const CustomString& str)
			{

			}

			bool operator>=(const CustomString& str)
			{

			}

			bool operator<=(const CustomString& str)
			{

			}

			bool operator==(const CustomString& str)
			{
				
			}



		};
	}

	namespace BST {
		template<typename T>
		struct Node {
			Node<T>* left;
			Node<T>* right;
			T value;
			Node()
				: left(nullptr),
				right(nullptr),
				value(0)
			{

			}
		};


		template<typename T>
		struct Tree {
			Node<T>* root = nullptr;

			~Tree()
			{
				delete_tree(root);
			}

			void delete_tree(Node<T>* root)
			{
				if (root != nullptr)
				{
					delete_tree(root->left);
					delete_tree(root->right);
					delete root;
				}
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

			bool isStored(Node<T>* ptr, const T& val)
			{
				if (ptr == nullptr)
				{
					return false;
				}

				if (ptr->value == val)
				{
					return true;
				}

				if (val > ptr->value)
				{
					return isStored(ptr->right, val);
				}
				else {
					return isStored(ptr->left, val);
				}
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

		namespace __pseudo {
		/*
			void rotateR(AVLNode* ptr)
			{
				AVLNode* tmp = ptr;
				ptr = ptr->left;
				tmp->left = ptr->right;
				ptr->right = tmp;
			}

			void rotateL(AVLNode* ptr)
			{
				AVLNode* tmp = ptr;
				ptr = ptr->right;
				tmp->right = ptr->left;
				ptr->left = tmp;
			}
			*/
		}


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
			
			void insert(AVLNode<T>*& ptr, const T& v)
			{
				if (ptr == nullptr) {
					ptr = new AVLNode<T>(v);
					return;
				}
				if (ptr->val >= v) {
					insert(ptr->left, v);
				
				}else{
					insert(ptr->right, v);
				}
				// recalc BalanceFactor
				ptr->balanceFactor = BF(ptr);

				if (ptr->balanceFactor == -2) {
					if (ptr->left->balanceFactor == -1)
					{
						ptr = lLeftRotate(ptr);
					}
					else if (ptr->left->balanceFactor == 1)
					{
						ptr = lRightRotate(ptr);
					}
				}else if (ptr->balanceFactor == 2) {
					if (ptr->right->balanceFactor == 1)
					{
						ptr = rRightRotate(ptr);
					}
					else if (ptr->right->balanceFactor == -1)
					{
						ptr = rLeftRotate(ptr);
					}
				}

			}

			void insert(T v)
			{
				insert(root, v);
			}

			int BF(AVLNode<T>* ptr)
			{
				return getHeight(ptr->right) - getHeight(ptr->left);
			
				// BF(X) < 0 is called "left-heavy"
				// BF(X) > 0 is called "right-heavy"
				// BF(X) = 0 is called "balanced"

			}

			AVLNode<T>* rRightRotate(AVLNode<T>* ptr)
			{ // Left Rotation
				AVLNode<T>* tmp = ptr->right;
				ptr->right = tmp->left;
				tmp->left = ptr;
				ptr->balanceFactor = BF(ptr);
				tmp->balanceFactor = BF(tmp);
				return tmp;
			}

			AVLNode<T>* lLeftRotate(AVLNode<T>* ptr)
			{ // Right Rotation
				AVLNode<T>* tmp = ptr->left;
				ptr->left = tmp->right;
				tmp->right = ptr;
				ptr->balanceFactor = BF(ptr);
				tmp->balanceFactor = BF(tmp);
				return tmp;
			}

			AVLNode<T>* lRightRotate(AVLNode<T>* ptr)
			{ // LEFT -> Right rotates
				AVLNode<T>* tmp = ptr->left;
				ptr->left = rRightRotate(tmp);
				ptr->balanceFactor = BF(ptr);
				tmp->balanceFactor = BF(tmp);
				return lLeftRotate(ptr);
			}

			AVLNode<T>* rLeftRotate(AVLNode<T>* ptr)
			{ // right -> left rotates
				AVLNode<T>* tmp = ptr->right;
				ptr->right = lLeftRotate(tmp);
				ptr->balanceFactor = BF(ptr);
				tmp->balanceFactor = BF(tmp);
				return rRightRotate(ptr);
			}

			bool isStored(AVLNode<T>* ptr, const T& val)
			{
				if (ptr == nullptr)
				{
					return false;
				}

				if (ptr->val == val)
				{
					return true;
				}

				if (val > ptr->val)
				{
					return isStored(ptr->right, val);
				}
				else {
					return isStored(ptr->left, val);
				}
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