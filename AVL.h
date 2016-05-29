#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

template<typename T>
class AVL
{
	// ========================================== Node ===============================================
	//
	template<typename T>
	struct Node
	{
		T key;
		unsigned int height;
		Node<T> * left;
		Node<T> * right;
		Node<T> * parent;

		Node<T>(T key, Node<T> * p = nullptr, Node<T> * l = nullptr, Node<T> * r = nullptr) :
			key(key), parent(p), left(l), right(r), height(1) {}

		
	};
	// ===============================================================================================
	
	// root
	//
	Node<T> * root;
	
	// num of rotations
	//
	static int count;

	// if null then height = 0
	//
	unsigned int height(Node<T> const * p) const
	{
		return p ? p->height : 0;
	}

	// balance factor
	//
	int bfactor(Node<T> * p)
	{
		return height(p->right) - height(p->left);
	}

	// correct height
	//
	void fixheight(Node<T> * p)
	{
		unsigned int hl = height(p->left);
		unsigned int hr = height(p->right);
		p->height = (hl>hr ? hl : hr) + 1;
	}

	// right rotate around p
	//
	Node<T> * rotateRight(Node<T> * p) // return new root
	{
		Node<T> * q = p->left;
		p->left = q->right;
		q->right = p;
		q->parent = p->parent; //
 		p->parent = q; //
		fixheight(p);
		fixheight(q);

		++count;
		return q;
	}

	// left rotate around q
	//
	Node<T> * rotateLeft(Node<T> * q) // return new root
	{
		Node<T> * p = q->right;
		q->right = p->left;
		p->left = q;
		p->parent = q->parent; //
		q->parent = p; //
		q->parent = p;
		fixheight(q);
		fixheight(p);

		++count;
		return p;
	}

	// balancing p node
	//
	Node<T> * balance(Node <T> * p)
	{
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateRight(p->right);
			return rotateLeft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateLeft(p->left);
			return rotateRight(p);
		}
		return p; // in else case balancing isn't needed
	}

public:
	// ========================================== Iterator ==========================================
	//
	template <typename T>
	class iterator
	{
		Node<T> * node;

	public:
		// constructor
		//
		iterator(Node<T> * n) : node(n) {}

		// operator *
		//
		T operator *() const 
		{
			return node->key;
		}

		// operator ==
		//
		bool operator ==(iterator<T> other)
		{
			return node == other.node;
		}

		// operator !=
		//
		bool operator !=(iterator<T> other)
		{
			return node != other.node;
		}

	private:
		bool isLeaf(Node<T> * p)
		{
			return p->left == nullptr && p->right == nullptr;
		}

	public:

		// operator increment
		//
		void operator ++()
		{
			if (node == nullptr)
				return;

			if (node->right != nullptr)
			{
				node = node->right;
				while (node->left != nullptr)
					node = node->left;
			}
			else
			{
				T elem = node->key;
				while (node != nullptr && node->key <= elem)
					node = node->parent;
			}
		}

		// opetator decrement
		//
		void operator--()
		{
			if (node == nullptr)
				return;

			if (node->left != nullptr)
			{
				node = node->left;
				while (node->right != nullptr)
					node = node->right;
			}
			else
			{
				T elem = node->key;
				while (node != nullptr && node->key >= elem)
					node = node->parent;
			}
		}

	};
	// ==============================================================================================

	// constructor
	//
	AVL() : root(nullptr) {}

	// max depth of the tree
	//
	int getDepth()
	{
		return root->left->height > root->right->height ? root->left->height : root->right->height;
	}

	// begin, a.k.a. min elem
	//
	iterator<T> begin()
	{
		Node<T> * cur{ root };
		while (cur->left != nullptr)
			cur = cur->left;
		return iterator<T>(cur);
	}

	// end
	//
	iterator<T> end()
	{
		return iterator<T>(nullptr);
	}

	// insertion
	//
private:
	Node<T> * insRec(Node<T> * p, int k)
	{
		if (!p) 
			return new Node<T>(k);

		if (k < p->key) {
			p->left = insRec(p->left, k);
			p->left->parent = p;
		}
			
		else {
			p->right = insRec(p->right, k);
			p->right->parent = p;
		}
			

		return balance(p); // return new root 
	}

public:
	void insert(int const k)
	{
		root = insRec(root, k);

#ifndef TIME_TEST
		std::cout << count << " rotations was made.\n";
#endif
		count = 0;
	}
	
	// find
	//
private:
	Node<T> * findRec(Node<T> * p, T const & k)
	{
		if (p == nullptr)
			return p;
		if (k < p->key)
			return findRec(p->left, k);
		else if (k > p->key)
			return findRec(p->right, k);
		else return p;
	}

public:
	iterator<T> find(T const & k)
	{
		return iterator<T>(findRec(root, k));
	}

	// removing
	//
private:
	Node<T> * findMin(Node<T> * p) // searching min key in tree p 
	{
		return p->left ? findMin(p->left) : p;
	}

	Node<T> * removeRec(Node<T> * p, T const & k)
	{
		if (p == nullptr)
			return nullptr;

		if (k < p->key)
		{
			p->left = removeRec(p->left, k);
			if (p->left)
				p->left->parent = p;
			balance(p);
		}
		else if (k > p->key)
		{
			p->right = removeRec(p->right, k);
			if (p->right)
				p->right->parent = p;
			balance(p);
		}

		else
		{
			Node<T> * left = p->left;
			Node<T> * right = p->right;
			Node<T> * parent = p->parent;

			delete p;

			if (!left && !right)
			{
				return nullptr;
			}
			else if (!left)
			{
				right->parent = parent;
				return balance(right);
			}
			else if (!right)
			{
				left->parent = parent;
				return balance(left);
			}
			else
			{
				Node<T> * min{ findMin(right) };
				Node<T> * minPar{ min->parent };

				// removing min
				if (right != min)
				{
					minPar->left = min->right;
					if (min->right)
					{
						min->right->parent = minPar;
					}
				}
				else
				{
					min->parent = parent;
				}

				// reparing pointers
				min->left = left;
				min->left->parent = min;

				if (right != min)
				{
					min->right = right;
					min->right->parent = min;
				}

				min->parent = parent;

				if (min != right)
				{
					Node<T> * cur{ minPar };
					while (cur)
					{
						fixheight(cur);
						if (cur != parent)
							cur = cur->parent;
						else
						{
							fixheight(cur);
							break;
						}
					}
				}

				return balance(min);
			}
		}
	}

public:
	void remove(T const & k)
	{
		root = removeRec(root, k);

#ifndef TIME_TEST
		std::cout << count << " rotations was made.\n";
#endif
		count = 0;
	}
	

	// print fallen tree
	//
private:
	void printRec(Node<T> * p, int depth = 0)
	{
		if (p == nullptr)
			return;
	
		printRec(p->right, depth + 1);

		for (int i{ 0 }; i != depth; ++i)
			std::cout << "     ";
		std::cout << p->key << '\n';

		printRec(p->left, depth + 1);
	}

public:
	void print()
	{
		std::cout << "================ Tree ================\n";

		printRec(root);

		std::cout << "======================================\n";
	}

	// saving into the binary file
	//
	void saveInFile(std::string const & name)
	{
		std::ofstream ofs(name);
		std::queue<Node<T> *> q;
		Node<T> * cur;

		q.push(root);
		while (!q.empty()) {
			cur = q.front();
			q.pop();
			ofs << cur->key << ' ';
			if (cur->left != nullptr)
				q.push(cur->left);
			if (cur->right != nullptr)
				q.push(cur->right);
		}
		std::cout << "Saved into the " << name << '\n';
	}

	// loading from a file
	//
	void loadFromFile(std::string const & name)
	{
		root = nullptr;
		std::ifstream ifs(name);
		while (ifs) {
			T k;
			ifs >> k;
			insert(k);
		}
	}

};

#endif /* AVL_H */