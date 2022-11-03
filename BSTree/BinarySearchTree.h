#pragma once
#include<iostream>
#include<string>

using namespace std;

template<class K>
class BSTreeNode
{
public:
	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;
	K _key;

	BSTreeNode(const K& key)
		: _left(nullptr)
		, _right(nullptr)
		, _key(key)
	{}
};

//class BinarySearchTree
template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node;
public:
	// method one
	//BSTree()
	//{}

	// method two C++11支持，强制生成默认构造
	BSTree() = default;

	BSTree(const BSTree<K>& tree)
	{
		// 别忘了返回根节点
		_root = _Copy(tree._root);
	}

	~BSTree()
	{
		_Destroy(_root);
	}

	// t2 = t1 传参也是拷贝构造,交换一下就行
	BSTree<K>& operator=(const BSTree<K> tree)
	{
		if (this != &tree)
			swap(_root, tree._root);
		return *this;
	}

	bool Find(const K& key)
	{
		if (_root == nullptr)
			return false;
		else
		{
			Node* cur = _root;
			while (cur)
			{
				if (key > cur->_key)
					cur = cur->_right;
				else if (key < cur->_key)
					cur = cur->_left;
				else
					return true;
			}
			return false;
		}
	}

	bool Insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}
		else
		{

			// 左边比根节点小，右边比根节点大，先找到空的位置再插入
			// 注意此处指针不能连写
			Node* cur = _root;
			Node* prev = nullptr;
			while (cur)
			{
				if (key > cur->_key)
				{
					// 保存之前的节点用于链接新插入的节点
					prev = cur;
					cur = cur->_right;
				}
				else if (key < cur->_key)
				{
					prev = cur;
					cur = cur->_left;
				}
				else
					// 搜索二叉树中不允许出现相同的值
					return false;
			}
			// 找到空位置，创建待插入的节点
			cur = new Node(key);
			// 在与prev的值判断一下，比_key大插在右边,比_key小插在左边
			if (key > prev->_key)
				prev->_right = cur;
			else
				prev->_left = cur;
			return true;
		}
	}

	bool Erase(const K& key)
	{
		if (_root == nullptr)
			return false;
		Node* cur = _root;
		Node* prev = nullptr;
		while (cur)
		{
			if (key > cur->_key)
			{
				prev = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				prev = cur;
			    cur = cur->_left;
			}
			// 找到了，开始删除
			else
			{
				// 删除节点没有孩子、删除节点只有一个孩子归为一类，可直接到删除
				// 1. 左为空，prev指向cur右边
				// 2. 右为空，prev指向cur左边
				if (cur->_right == nullptr)
				{
					// 特殊处理一下删除根节点的情况
					if (cur == _root)
						// 更新根节点
						_root = cur->_left;
					else
					{
						// 注意判断一下cur是在prev的左边还是右边
						if (cur == prev->_right)
							prev->_right = cur->_left;
						// cur在prev的左边
						else
							prev->_left = cur->_left;
					}
					delete cur;
					cur = nullptr;
				}
				// 删除节点左边为空，prev指向右边节点
				else if (cur->_left == nullptr)
				{
					if (cur == _root)
						_root = cur->_right;
					else
					{
						if (cur == prev->_right)
							prev->_right = cur->_right;
						else
							prev->_left = cur->_right;
					}
					delete cur;
					cur = nullptr;
				}
				// 删除节点左右都不为空
				else
				{
					// 替换法删除
					// 注意此处minParent不能给空指针，因为要删除节点可能是根节点
					Node* minParent = cur;
					// 统一用右子树最小节点去替换，先找到右子树最左节点
					Node* min = cur->_right;
					while (min->_left)
					{
						minParent = min;
						min = min->_left;
					}
					// 交换后要删除节点就变为只有一个孩子或者没有孩子了，可直接删
					swap(min->_key, cur->_key);
					// 最左节点下依旧可能链接着节点
					if (min == minParent->_left)
						// 此时替换节点已经是最左节点，其左子树必为空，只需让其父节点指向右
						minParent->_left = min->_right;
					// 删除的是根节点，最左节点在parent的右边
					else
						minParent->_right = min->_right;
					delete min;
					min = nullptr;
				}
				return true;
			}
		}
		// 树中没有这个值
		return false;
	}

	void InOrder()
	{
		_InOrder(_root);
		std::cout << std::endl;
	}

	void PreOrder()
	{
		_PreOrder(_root);
		std::cout << std::endl;
	}

	void PosOrder()
	{
		_PosOrder(_root);
		std::cout << std::endl;
	}

	size_t Size()
	{
		return _Size(_root);
	}

	/////////////////////////////////////////////////////////
	// 递归版
	bool FindR(const K& key)
	{
		return _FindR(_root, key);
	}

	bool InsertR(const K& key)
	{
		return _InsertR(_root, key);
	}

	bool EraseR(const K& key)
	{
		return _EraseR(_root, key);
	}

private:
	// 前序遍历拷贝构造
	Node* _Copy(Node* root)
	{
		if (root == nullptr)
			return nullptr;
		Node* copyRoot = new Node(root->_key);
		copyRoot->_left = _Copy(root->_left);
		copyRoot->_right = _Copy(root->_right);
		return copyRoot;
	}

	// 后序遍历销毁二叉树
	void _Destroy(Node*& root)
	{
		if (root == nullptr)
			return;
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
		// 此处给的是引用的话就能够真正的置空了
		root = nullptr;
	}

	size_t _Size(Node* root)
	{
		if (root == nullptr)
			return 0;
		return _Size(root->_left) + _Size(root->_right) + 1;
	}

	// 此处也要给引用，这样root就能是上一层节点的左右指针的引用了
	bool _EraseR(Node*& root, const K& key)
	{
		if (root == nullptr)
			return false;
		if (key > root->_key)
			return _EraseR(root->_right, key);
		else if (key < root->_key)
			return _EraseR(root->_left, key);
		// found, start delete
		else
		{
			// 保存一下要删除的节点
			Node* del = root;
			if (root->_right == nullptr)
			{
				// root是上一层左右指针的别名
				root = root->_left;
			}
			else if (root->_left == nullptr)
			{
				root = root->_right;
			}
			else
			{
				// 找到右子树最小节点替换删除
				Node* min = root->_right;
				while (min->_left)
				{
					min = min->_left;
				}
				swap(min->_key, root->_key);
				// 这样写是错误的，因为交换后树的结构发生了变化，再从根节点找key是找不到的
				// 需要到root->right 才能找到key
				//return Erase(key);
				return _EraseR(root->_right, key);
			}
			delete del;
			del = nullptr;
			return true;
		}
	}

	// 此处的引用是神来之笔
	// 引用只在最后一次找到空创建插入节点起作用,链接起上一次调用的root->right/root->left
	bool _InsertR(Node*& root, const K& key)
	{
		// 找到空位置进行插入
		// 上一层左右指针的别名
		if (root == nullptr)
		{
			root = new Node(key);
			return true;
		}
		else if (key > root->_key)
			return _InsertR(root->_right, key);
		else if (key < root->_key)
			return _InsertR(root->_left, key);
		// 树中已经有这个值了，搜索二叉树不允许重复
		else
			return false;
	}

	bool _FindR(Node* root, const K& key)
	{
		// 走到找不到返回false
		if (root == nullptr)
			return false;
		// 递归去左右子树去找
		if (key > root->_key)
			return _FindR(root->_right, key);
		else if (key < root->_key)
			return _FindR(root->_left, key);
		else
			return true;
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		std::cout << root->_key << " ";
		_InOrder(root->_right);
	}

	void _PreOrder(Node* root)
	{
		if (root == nullptr)
			return;
		std::cout << root->_key <<" ";
		_PreOrder(root->_left);
		_PreOrder(root->_right);
	}

	void _PosOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_PosOrder(root->_left);
		_PosOrder(root->_right);
		std::cout << root->_key << " ";
	}

private:
	Node* _root = nullptr;
};

void TestInsert()
{
	BSTree<int> t;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3, 4 };
	for (auto& e : a)
	{
		t.Insert(e);
	}
	// 排序+去重
	t.InOrder();
}

void TestFind()
{
	BSTree<int> t;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3, 4 };
	for (auto& e : a)
	{
		t.Insert(e);
	}
	if (t.Find(14))
		cout << "found" << endl;
	else
		cout << "no found" << endl;
	if (t.Find(140))
		cout << "found" << endl;
	else
		cout << "no found" << endl;
}

void TestErase()
{
	BSTree<int> t;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3, 4 };
	for (int& e : a)
	{
		t.Insert(e);
	}
	t.InOrder();
	//t.Erase(8);
	//t.Erase(13);
	//t.Erase(3);
	//t.Erase(3);
	for (auto e : a)
	{
		t.Erase(e);
	}
	t.InOrder();
	t.Insert(1);
	t.Insert(2);
	t.Insert(3);
	t.Insert(4);
	t.InOrder();
}

void TestFindR()
{
	BSTree<int> t;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3, 4 };
	for (int& e : a)
	{
		t.Insert(e);
	}
	if (t.FindR(4))
		cout << "yes" << endl;
	if (t.FindR(100))
		cout << "yes" << endl;
	else
		cout << "no" << endl;
}

void TestInsertR()
{
	BSTree<int> t;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3, 4 };
	for (int& e : a)
	{
		t.InsertR(e);
	}
	t.InOrder();
	t.Erase(4);
	t.InOrder();
}

void TestEraseR()
{
	BSTree<int> t;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3, 4 };
	for (int& e : a)
	{
		t.Insert(e);
	}
	t.InOrder();
	//t.EraseR(14);
	//t.InOrder();
	//t.EraseR(8);
	//t.InOrder();
	for (auto& e : a)
	{
		t.EraseR(e);
		t.InOrder();
	}
}

void TestSize()
{
	BSTree<int> t;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3, 4 };
	for (int& e : a)
	{
		t.Insert(e);
	}
	t.InOrder();
	cout << t.Size() << endl;
}

void TestCopy()
{
	BSTree<int> t;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3, 4 };
	for (int& e : a)
	{
		t.Insert(e);
	}
	//t.InOrder();
	// 默认生成的是浅拷贝，指向的是同一块空间
	BSTree<int> t2 = t;
	t2.InOrder();
	//t2.Erase(8);
	//t2.InOrder();
	//t.InOrder();
	//t.InOrder();
	BSTree<int> t3 = t2;
	t3.InOrder();
	for (auto& e : a)
	{
		t2.Erase(e);
	}
	t2.InOrder();
	t3.InOrder();
	t3.Erase(8);
	t3.InOrder();
}

void TestOrder()
{
	BSTree<int> t;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3, 4 };
	for (int& e : a)
	{
		t.Insert(e);
	}
	t.InOrder();
	t.PreOrder();
	t.PosOrder();
}

//////////////////////////////////////////////////////////////////////////////
// keyValue模型
namespace keyValue
{
	template<class K, class V>
	class BSTreeNode
	{
	public:
		BSTreeNode<K, V>* _left;
		BSTreeNode<K, V>* _right;
		K _key;
		V _val;
		BSTreeNode(const K& key, const V& val)
			: _left(nullptr)
			, _right(nullptr)
			, _key(key)
			, _val(val)
		{}
	};

	template<class K, class V>
	class BSTree
	{
		typedef BSTreeNode<K, V> Node;
	public:
		BSTree() = default;

		BSTree(const BSTree<K, V>& tree)
		{
			// 别忘了返回根节点
			_root = _Copy(tree._root);
		}

		~BSTree()
		{
			_Destroy(_root);
		}

		// 找到之后可修改它的值
		Node* Find(const K& key)
		{
			if (_root == nullptr)
				return nullptr;
			else
			{
				Node* cur = _root;
				while (cur)
				{
					if (key > cur->_key)
						cur = cur->_right;
					else if (key < cur->_key)
						cur = cur->_left;
					else
						return cur;
				}
				return nullptr;
			}
		}

		bool Insert(const K& key, const V& val)
		{
			if (_root == nullptr)
			{
				_root = new Node(key, val);
				return true;
			}
			else
			{
				Node* cur = _root;
				Node* prev = nullptr;
				while (cur)
				{
					if (key > cur->_key)
					{
						// 保存之前的节点用于链接新插入的节点
						prev = cur;
						cur = cur->_right;
					}
					else if (key < cur->_key)
					{
						prev = cur;
						cur = cur->_left;
					}
					else
						// 搜索二叉树中不允许出现相同的值
						return false;
				}
				cur = new Node(key, val);
				if (key > prev->_key)
					prev->_right = cur;
				else
					prev->_left = cur;
				return true;
			}
		}

		bool Erase(const K& key)
		{
			if (_root == nullptr)
				return false;
			Node* cur = _root;
			Node* prev = nullptr;
			while (cur)
			{
				if (key > cur->_key)
				{
					prev = cur;
					cur = cur->_right;
				}
				else if (key < cur->_key)
				{
					prev = cur;
					cur = cur->_left;
				}
				else
				{
					if (cur->_right == nullptr)
					{
						if (cur == _root)
							_root = cur->_left;
						else
						{
							if (cur == prev->_right)
								prev->_right = cur->_left;
							else
								prev->_left = cur->_left;
						}
						delete cur;
						cur = nullptr;
					}
					else if (cur->_left == nullptr)
					{
						if (cur == _root)
							_root = cur->_right;
						else
						{
							if (cur == prev->_right)
								prev->_right = cur->_right;
							else
								prev->_left = cur->_right;
						}
						delete cur;
						cur = nullptr;
					}
					else
					{
						Node* minParent = cur;
						Node* min = cur->_right;
						while (min->_left)
						{
							minParent = min;
							min = min->_left;
						}
						swap(min->_key, cur->_key);
						if (min == minParent->_left)
							minParent->_left = min->_right;
						else
							minParent->_right = min->_right;
						delete min;
						min = nullptr;
					}
					return true;
				}
			}
			return false;
		}

		void InOrder()
		{
			_InOrder(_root);
			std::cout << std::endl;
		}

		private:
			// 后序遍历销毁二叉树
			void _Destroy(Node*& root)
			{
				if (root == nullptr)
					return;
				_Destroy(root->_left);
				_Destroy(root->_right);
				delete root;
				// 此处给的是引用的话就能够真正的置空了
				root = nullptr;
			}

			void _InOrder(Node* root)
			{
				if (root == nullptr)
					return;
				_InOrder(root->_left);
				std::cout << root->_key << " ";
				_InOrder(root->_right);
			}
			private:
				Node* _root = nullptr;
	};	

	void TestKV()
	{
		BSTree<string, string> dict;
		dict.Insert("sort", "排序");
		dict.Insert("left", "左边");
		dict.Insert("right", "右边");
		dict.Insert("string", "字符串");
		dict.Insert("insert", "插入");
		string str;
		while (cin >> str)
		{
			// 类外面tydef失效，需要显示写
			BSTreeNode<string, string>* ret = dict.Find(str);
			if (ret != nullptr)
				std::cout << str << ":" << ret->_val << std::endl;
			else
				std::cout << "error" << std::endl;
		}
	}

	// 记录各种水果所具有的数量
	void TestCountTree()
	{
		BSTree<string, int> fruit;
		string arr[] = { "香蕉", "苹果", "香蕉", "草莓", "香蕉", "苹果", "苹果", "苹果" };
		for (auto& str : arr)
		{
			// 已经存在就++count
			//BSTreeNode<string, int>* ret = fruit.Find(str);
			auto ret = fruit.Find(str);
			if (ret != nullptr)
				ret->_val++;
			else
				fruit.Insert(str, 1);
		}
		fruit.InOrder();
	}
}
