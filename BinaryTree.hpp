#ifndef _BINARYTREE_HPP
#define _BINARYTREE_HPP
#include <iostream>


template <typename T>
class BinaryTree
{
private:
	class TreeNode
	{
		friend class BinaryTree<typename T>;
	private:
		TreeNode(T value) :
			m_data(value),
			m_left(nullptr),
			m_right(nullptr) {}
		T m_data;
		TreeNode* m_left;
		TreeNode* m_right;
	};

	TreeNode* m_root;
	bool insert(TreeNode*& tree, T value)
	{
		if (tree == nullptr) //value not found
		{
			tree = new TreeNode(value);
			return true;
		}
		else if (tree->m_data == value) //value found
		{
			return false;
		}
		else //continue search on left subtree
		{
			if (value < tree->m_data)
				return insert(tree->m_left, value);
			else
				return insert(tree->m_right, value);

		}
	}
	void display(TreeNode* tree)
	{
		if (tree)
		{
			display(tree->m_left);
			std::cout << tree->m_data << std::endl;
			display(tree->m_right);
		}
	}
	void remove(TreeNode*& tree, T value)
	{
			if (tree == nullptr) return;
			if (value < tree->m_data)
				remove(tree->m_left, value);
			else if (value > tree->m_data)
				remove(tree->m_right, value);
			else
				// We have found the node to delete.
				makeDeletion(tree);
	}
	void makeDeletion(TreeNode*& tree)
	{
		TreeNode* nodeToDelete = tree;
		TreeNode* attachPoint;
		if (tree->m_right == nullptr)
		{
			tree = tree->m_left;
		}
		else if (tree->m_left == nullptr)
		{
			tree = tree->m_right;
		}
		else
		{

			attachPoint = tree->m_right;
			while (attachPoint->m_left != nullptr)
			{
				attachPoint = attachPoint->m_left;
			}
			attachPoint->m_left = tree->m_left;

			tree = tree->m_right;
		}
		delete nodeToDelete;
	}

	bool search(TreeNode* tree, T value)
	{
		if (tree == nullptr)
		{
			return false;
		}
		else if (tree->m_data == value)
		{
			return true;
		}
		else if (value < tree->m_data)
		{
			return search(tree->m_left, value);
		}
		else if (value > tree->m_data)
		{
			return search(tree->m_right, value);
		}
		else
			return false;
	}
	unsigned int numberNodes(TreeNode* tree)
	{
		if (tree)
		{
			if (tree->m_left == nullptr && tree->m_right == nullptr)
			{
				return 1;
			}
			else if (tree->m_left == nullptr && tree->m_right != nullptr)
			{
				return 1 + numberNodes(tree->m_right);
			}
			else if (tree->m_right == nullptr && tree->m_left != nullptr)
			{
				return 1 + numberNodes(tree->m_left);
			}
			else if (tree->m_right != nullptr && tree->m_left != nullptr)
			{
				return 1 + numberNodes(tree->m_left) + numberNodes(tree->m_right);
			}
		}
	}
	unsigned int numberLeafNodes(TreeNode* tree)
	{
		if (tree)
		{
			if (tree->m_left == nullptr && tree->m_right == nullptr)
			{
				return 1;
			}
			else if (tree->m_left == nullptr && tree->m_right != nullptr)
			{
				return numberLeafNodes(tree->m_right);
			}
			else if (tree->m_right == nullptr && tree->m_left != nullptr)
			{
				return numberLeafNodes(tree->m_left);
			}
			 else if (tree->m_right != nullptr && tree->m_left != nullptr)
			{
				return numberLeafNodes(tree->m_left) + numberLeafNodes(tree->m_right);
			}
		}
	}
	unsigned int height(TreeNode* tree)
	{
		if (tree)
		{
			if (tree->m_left == nullptr && tree->m_right == nullptr)
			{
				return 1 ;
			}
			else if (tree->m_left == nullptr)
			{
				return 1+ height(tree->m_right);
			}
			else if (tree->m_right == nullptr)
			{
				return 1 + height(tree->m_left);
			}
			else 
			{
				return 1 + std::max(height(tree->m_left), height(tree->m_right));
			}
		}
	}
public:
	BinaryTree() :
		m_root(nullptr){}				// constructor
	~BinaryTree()
	{
		destructorHelper(m_root);
	}
	void destructorHelper(TreeNode*& tree)
	{
		if (tree->m_left != nullptr)
		{
			destructorHelper(tree->m_left);
			delete tree->m_left;
		}
		if (tree->m_right != nullptr)
		{
			destructorHelper(tree->m_right);
			delete tree->m_right;
		}
	}

	bool insert(T value){return insert(m_root, value);}	// inserts a value into the tree, does not allow duplicates. If the value is already in the tree, false is returned, true otherwise.

	void display(){display(m_root);}			// displays all contents from left to right	
	void remove(T value){remove(m_root, value);}	// deletes a value from the tree.
	
	bool search(T value){return search(m_root, value);}			// tests to see if a value exists in the tree.
	
	unsigned int numberNodes(){return numberNodes(m_root);}		// returns a count of all nodes in the tree.
	
	unsigned int numberLeafNodes(){return numberLeafNodes(m_root);}	// returns a count of all the leaf nodes in the tree
	
	unsigned int height() {return height(m_root);}			// returns the height of the tree.
	
	void statInfo()
	{
		std::cout
			<< "-- Tree Stats --"
			<< std::endl
			<< std::endl
			<< "Total Nodes: "
			<< numberNodes()
			<< std::endl
			<< "Leaf Nodes: "
			<< numberLeafNodes()
			<< std::endl
			<< "Tree Height: "
			<< height()
			<< std::endl;

	}

};






#endif
