#pragma once
#include<iostream>
#include <queue>
#include<stack>
#include<vector>
using namespace std;

template <class T>
class BST
{
	class node
	{
		T data;
		node* left;
		node* right;
	public:
		friend class BST;
		node()
		{
			left = nullptr;
			right = nullptr;

		}
		node(T key)
		{
			data = key;
			left = nullptr;
			right = nullptr;

		}
		node(const node& obj)
		{
			data = obj.data;
			if (obj.left != nullptr)
				left = new node(obj.left->data);
			else
				left = nullptr;
			if (obj.right != nullptr)
				right = new node(obj.right->data);
			else
				right = nullptr;
		}
		~node()
		{
			left = nullptr;
			right = nullptr;
		}
	};

	node* root;
	node* Searchnode(T key, node* t)
	{
		if (t == nullptr)
			return nullptr;
		if (t->data == key)
			return t;
		else if (t->data > key)
			return Searchnode(key, t->left);
		else
			return Searchnode(key, t->right);
	}
	node* Searchnode(T key)
	{
		return Searchnode(key, root);
	}
	bool Search(T key, node* t)
	{
		if (t == nullptr)
			return false;
		if (t->data == key)
			return true;
		else if (t->data > key)
			return Searchnode(key, t->left);
		else
			return Searchnode(key, t->right);
	}
	bool Case1(node* curr, node* prev)
	{
		if (curr == root)
			root = nullptr;
		else if (curr == prev->left)
			prev->left = nullptr;
		else
			prev->right = nullptr;
		delete curr;
		return true;
	}
	bool Case2(node* curr, node* prev)
	{
		if (curr == root)
		{
			node* temp = curr;
			curr = curr->right;
			delete temp;
			root = curr;
		}
		else if (curr == prev->right)
		{
			prev->right = curr->right;
			delete curr;
			return true;
		}
		else
		{
			prev->left = curr->right;

			delete curr;
			return true;
		}

	}
	bool Case3(node* curr, node* prev)
	{
		if (curr == root)
		{
			node* temp = curr;
			curr = curr->left;
			delete temp;
			root = curr;
		}
		else if (curr == prev->left)
		{
			prev->left = curr->left;
			delete curr;
			return true;
		}
		else
		{
			prev->right = curr->left;

			delete curr;
			return true;
		}

	}

	void LVR(node* curr)
	{
		if (curr == nullptr)
			return;
		LVR(curr->left);
		cout << curr->data << " ";
		LVR(curr->right);
	}
	void VLR(node* curr)
	{
		if (curr == nullptr)
			return;
		cout << curr->data << " ";
		VLR(curr->left);
		VLR(curr->right);
	}
	void LRV(node* curr)
	{
		if (curr == nullptr)
			return;
		LRV(curr->left);
		LRV(curr->right);
		cout << curr->data << " ";
	}

	void delete_for_destructor(node* curr)
	{
		if (curr == nullptr)
			return;
		delete_for_destructor(curr->left);
		delete_for_destructor(curr->right);
		delete curr;
		curr = nullptr;
	}
	/*bool isbetween(int key_prev, int new_key, int key_curr)
	{
		if (key_prev < key_curr)
			return (key_prev < new_key&& new_key < key_curr);
		else
			return (key_curr < new_key&& new_key < key_prev);
	}*/
	void insertAgain(node* curr)
	{
		if (curr == nullptr)
			return;
		insertAgain(curr->left);
		Insert(curr->data);
		insertAgain(curr->right);
	}
	queue<node*> convert_to_queue(node* curr)
	{
		queue<node*> q;
		queue<node*>q2;
		q.push(curr);
		//node* curr;
		while (!q.empty())
		{
			curr = q.front();
			q.pop();
			q2.push(curr);
			if (curr->left != nullptr)
				q.push(curr->left);
			if (curr->right != nullptr)
				q.push(curr->right);

		}
		return q2;
	}
	void VLR_stack(node* curr, stack<node*>& s)
	{
		if (curr == nullptr)
			return;
		s.push(curr);
		VLR_stack(curr->left, s);
		VLR_stack(curr->right, s);
	}

	void LVR_Queue(node* curr, queue<node*>& q)
	{
		if (curr == nullptr)
			return;
		LVR_Queue(curr->left, q);
		q.push(curr);
		LVR_Queue(curr->right, q);
	}

	queue<node*> Search_while_pushing_in_queue(T key)
	{
		queue<node*> q;
		node* curr = root;
		while (curr->data != key)
		{
			if (key < curr->data)
			{
				q.push(curr);
				curr = curr->left;
			}
			else
			{
				q.push(curr);
				curr = curr->right;
			}
		}
		return q;
	}

	void pathSum(node* curr, vector<T>& v, T sum)
	{
		if (curr == nullptr)
		{
			return;
		}

		pathSum(curr->left, v, sum + curr->data);

		if (curr->left == nullptr && curr->right == nullptr)
			v.push_back(sum + curr->data);

		pathSum(curr->right, v, sum + curr->data);

	}

	void helper_assignment(node* curr1, node* curr2, node*& root, int signal)
	{
		if (curr1 == nullptr)
		{
			return;
		}

		if (signal == -1)
		{
			curr2 = new node(curr1->data);
			root = curr2;
		}
		else if (signal == 0)
		{
			curr2->left = new node(*curr1);
			curr2 = curr2->left;
		}
		else
		{
			curr2->right = new node(*curr1);
			curr2 = curr2->right;
		}
		helper_assignment(curr1->left, curr2, root, 0);
		helper_assignment(curr1->right, curr2, root, 1);

	}

public:
	BST()
	{
		root = nullptr;

	}

	~BST()
	{
		delete_for_destructor(root);
		root = nullptr;
	}
	bool Search(T key)
	{
		return Search(key, root);
	}
	void Insert(T key)
	{
		node* n = new node(key);
		if (root == nullptr)
		{
			root = n;
			return;
		}
		node* curr = root;
		node* prev = root;
		while (curr != nullptr)
		{
			if (key < curr->data)
			{
				prev = curr;
				curr = curr->left;
			}
			else
			{
				prev = curr;
				curr = curr->right;
			}
		}

		if (prev->data > key)
			prev->left = n;
		else
			prev->right = n;




	}
	bool Delete(int key)
	{
		if (!Search(key))
			return false;
		node* curr = root;
		node* prev = curr;
		while (curr->data != key)
		{
			if (key < curr->data)
			{
				prev = curr;
				curr = curr->left;
			}
			else
			{
				prev = curr;
				curr = curr->right;
			}
		}

		if (curr->left == nullptr && curr->right == nullptr)
		{
			return Case1(curr, prev);
		}
		else if (curr->left == nullptr && curr->right != nullptr)
		{
			return Case2(curr, prev);
		}
		else if (curr->left != nullptr && curr->right == nullptr)
		{
			return Case3(curr, prev);
		}
		else
		{
			node* del = curr;
			curr = curr->right;
			while (curr != nullptr && curr->left != nullptr)  //finding sucessor
			{
				prev = curr;
				curr = curr->left;
			}
			//swaping
			T temp = curr->data;
			curr->data = del->data;
			del->data = temp;
			if (curr->left == nullptr && curr->right == nullptr)
			{
				return Case1(curr, prev);
			}
			else
			{
				return Case2(curr, prev);
			}

		}
	}
	void LVR()
	{
		LVR(root);
	}
	void VLR()
	{
		VLR(root);
	}
	void LRV()
	{
		LRV(root);
	}
	void LevelOrder()
	{
		queue<node*> q;
		q.push(root);
		node* curr;
		while (!q.empty())
		{
			curr = q.front();
			q.pop();
			cout << curr->data << " ";
			if (curr->left != nullptr)
				q.push(curr->left);
			if (curr->right != nullptr)
				q.push(curr->right);

		}
	}

	void LVR_iterative()
	{
		node* curr = root;
		stack<node*> s;  //L
		node* done = nullptr;
		s.push(curr);
		while (!s.empty())
		{
			if (curr->left != nullptr && curr->left != done)
			{
				curr = curr->left;
				s.push(curr);
			}
			else
			{
				curr = s.top();
				s.pop();
				cout << curr->data << " ";
				if (curr->right != nullptr)
				{
					curr = curr->right;
					s.push(curr);
				}
				else
					done = curr;
			}
		}

	}
	void VLR_iterative()
	{
		node* curr = root;
		stack<node*> s;
		s.push(root);
		node* done = nullptr;
		do
		{

			if (curr != done)
			{
				cout << curr->data << " ";

			}
			if (curr != nullptr && curr->left != nullptr)
			{
				curr = curr->left;
				s.push(curr);
			}
			else
			{
				curr = s.top();
				s.pop();
				if (curr->right != nullptr)
				{
					curr = curr->right;
					s.push(curr);
				}
				else
					done = curr;
			}
		} while (!s.empty());
	}
	void LRV_iterative()
	{
		node* curr = root;
		stack<node*> s;
		s.push(curr);
		node* done = root;
		bool stack_empty = false;
		while (!stack_empty)
		{
			if (curr->right == done)
			{
				cout << curr->data << " ";
				done = curr;
				s.pop();
				if (!s.empty())
					curr = s.top();
				else
					stack_empty = true;
			}
			if (curr != nullptr && curr->left != nullptr && curr->left != done)
			{
				curr = curr->left;
				s.push(curr);
			}
			else
			{
				if (s.top()->right == nullptr && curr->right != done)
				{
					curr = s.top();
					cout << curr->data << " ";
					done = curr;
					s.pop();
					curr = s.top();

				}
				if (curr->right == done)
				{
					cout << curr->data << " ";
					done = curr;
					s.pop();
					if (!s.empty())
						curr = s.top();
					else
						stack_empty = true;

				}
				if (curr->right != nullptr && curr->right != done)
				{
					curr = curr->right;
					s.push(curr);
				}
			}
		}

	}
	void UpdateKey(T key1, T key2)
	{
		//searching for key1
		node* curr = root;
		node* prev = root;
		while (curr->data != key1)
		{
			if (key1 < curr->data)
			{
				prev = curr;
				curr = curr->left;
			}
			else
			{
				prev = curr;
				curr = curr->right;
			}
		}


		curr->data = key2;

		if (isBST())
			return;

		//removing the whole subtree
		node* subtree = curr;
		if (prev->right == curr)
			prev->right = nullptr;
		else if (prev->left == curr)
			prev->left = nullptr;
		else
		{
			root = nullptr;
			
		}
		//inserting all the elements of subtree again
		insertAgain(subtree);

	}

	BST& operator=(const BST& obj)
	{
		if (this != &obj)
		{
			node* curr = nullptr;

			helper_assignment(obj.root, curr, this->root, -1);

		}
		return *this;
	}

	bool operator==(const BST& tree2)
	{
		queue<node*> q1;
		queue<node*> q2;
		q1 = convert_to_queue(this->root);
		q2 = convert_to_queue(tree2.root);

		T x;
		T y;
		while (!q1.empty())
		{
			x = q1.front()->data;
			q1.pop();
			y = q2.front()->data;
			q2.pop();
			if (x != y)
				return false;
		}
		return true;
	}

	int countNodes()
	{
		int count = 0;
		node* curr = root;
		stack<node*> s;  //L
		node* done = nullptr;
		s.push(curr);
		while (!s.empty())
		{
			if (curr->left != nullptr && curr->left != done)
			{
				curr = curr->left;
				s.push(curr);
			}
			else
			{
				curr = s.top();
				s.pop();
				count++; //visiting the node
				if (curr->right != nullptr)
				{
					curr = curr->right;
					s.push(curr);
				}
				else
					done = curr;
			}
		}
		return count;
	}
	void Mirror()
	{
		stack<node*> s;
		VLR_stack(root, s);
		node* temp;
		node* curr;
		while (!s.empty())
		{
			curr = s.top();
			temp = curr->left;
			curr->left = curr->right;
			curr->right = temp;
			s.pop();

		}
	}
	void skew()
	{
		queue<node*>q;
		LVR_Queue(root, q);
		node* curr;
		curr = q.front();
		q.pop();
		curr->left = nullptr;
		root = curr;
		node* temp;
		while (!q.empty())
		{
			temp = q.front();
			q.pop();
			temp->left = nullptr;
			curr->right = temp;
			curr = curr->right;

		}
	}

	void Common_Ancestors(T n1, T n2)
	{
		if (!Search(n1))
		{
			cout << n1 << "\n is not a part of tree\n";
			return;
		}
		else if (!Search(n2))
		{
			cout << n2 << "\n is not a part of tree\n";
			return;
		}
		queue<node*> q1 = Search_while_pushing_in_queue(n1);
		queue<node*> q2 = Search_while_pushing_in_queue(n2);
		bool flag = false;
		T x, y;
		while (!q1.empty() && !q2.empty() && !flag)
		{
			x = q1.front()->data;
			q1.pop();
			y = q2.front()->data;
			q2.pop();
			if (x == y)
			{
				cout << x << " ";
			}
			else
				flag = true;
		}

	}

	bool isBST(node* curr)
	{
		if (curr == nullptr)
		{
			return true;
		}
		bool e = isBST(curr->left);
		if (e == false)
			return false;
		if (curr->left != nullptr && curr->right == nullptr)
		{
			if (curr->left->data > curr->data)
				return false;
		}
		else if (curr->left == nullptr && curr->right != nullptr)
		{
			if (curr->right->data < curr->data)
				return false;
		}
		else if (curr->left != nullptr && curr->right != nullptr)
		{
			if (!(curr->left->data < curr->data && curr->data < curr->right->data))
				return false;
		}
		e = isBST(curr->right);
		if (e == false)
			return false;
	}
	bool isBST()
	{
		/*node* curr = root;
		curr = curr->right;
		curr = curr->right;
		curr = curr->left;

		curr->data = 15;
		return isBST(root);*/

		return isBST(root);
	}

	void pathSum(vector<int>& v)
	{
		int i = 0;
		pathSum(root, v, 0);
	}
	int Width()
	{
		node* curr = root;
		queue<node*> q;
		queue<node*>q2;
		q.push(curr);
		q.push(nullptr);
		q2.push(curr);
		q2.push(nullptr);
		//node* curr;
		while (!q.empty())
		{
			curr = q.front();
			q.pop();
			if (curr != nullptr)
			{
				if (curr->left != nullptr)
				{
					q.push(curr->left);
					q2.push(curr->left);
				}
				if (curr->right != nullptr)
				{
					q.push(curr->right);
					q2.push(curr->right);
				}
			}
			else if (!q.empty())
			{
				q.push(nullptr);
				q2.push(nullptr);
			}
		}
		// 8 x 3 10 x 1 6 14 x 4 7 13 x in q2
		vector<int>v;
		int count = 0;
		while (!q2.empty())
		{
			curr = q2.front();
			q2.pop();
			if (curr != nullptr)
				count++;
			else
			{
				v.push_back(count);
				count = 0;
			}
		}
		int max = v[0];
		for (int i = 1; i < v.size(); i++)
		{
			if (v[i] > max)
				max = v[i];
		}
		return max;
	}

};





int main()
{
	BST<int> b;
	b.Insert(8);
	b.Insert(3);
	b.Insert(10);
	b.Insert(1);
	b.Insert(6);
	b.Insert(14);
	b.Insert(13);
	b.Insert(4);
	b.Insert(7);
	/// 
	///           8
	///          / \
	///         3  10
/// 	       /\    \
/// 	      1  6    14
/// 	         /\   /
/// 	        4  7 13
///  
	/// 

	cout << "\n----------------Data is inserted by default---------------------------\n";
	cout << "1.Search\n";
	cout << "2.Insert\n";
	cout << "3.Delete\n";
	cout << "4.LVR\n";
	cout << "5.VLR\n";
	cout << "6.LRV\n";
	cout << "7.LVR iterative\n";
	cout << "8.VLR iterative\n";
	cout << "9.LRV iterative\n";
	cout << "10. Level order\n";
	cout << "11.Update Key\n";
	cout << "12.Overloaded Assignement operator\n";
	cout << "13.== operator\n";
	cout << "14.Count nodes\n";
	cout << "15.Mirror BST\n";
	cout << "16.Find width\n";
	cout << "17.Path sum\n";
	cout << "18.Make skew\n";
	cout << "19. Is BST\n";
	cout << "20.Common ancestors\n";
	int choice;
	cin >> choice;
	while (choice != -1)
	{
		if (choice == 1)
		{
			int data;
			cout << "Enter element: ";
			cin >> data;
			cout << b.Search(data);
			cout << endl;
		}
		else if (choice == 2)
		{
			int data;
			cout << "Enter Data: ";
			cin >> data;
			b.Insert(data);
			cout << "New tree in level order: ";
			b.LevelOrder();
			cout << endl;
		}
		else if (choice == 3)
		{
			int data;
			cout << "Enter Data: ";
			cin >> data;
			b.Delete(data);
			cout << "New tree in level order: ";
			b.LevelOrder();
			cout << endl;
		}
		else if (choice == 4)
		{
			cout << endl;
			b.LVR();
			cout << endl;
		}
		else if (choice == 5)
		{
			cout << endl;
			b.VLR();
			cout << endl;
		}
		else if (choice == 6)
		{
			cout << endl;
			b.LRV();
			cout << endl;
		}
		else if (choice == 7)
		{
			cout << endl;
			b.LVR_iterative();
			cout << endl;
		}
		else if (choice == 8)
		{
			cout << endl;
			b.VLR_iterative();
			cout << endl;
		}
		else if (choice == 9)
		{
			cout << endl;
			b.LRV_iterative();
			cout << endl;
		}
		else if (choice == 10)
		{
			cout << endl;
			b.LevelOrder();
			cout << endl;
		}
		else if (choice == 11)
		{
			int k1, k2;
			cout << "enter the key you want to updata: ";
			cin >> k1;
			cout << "Enter the new key: ";
			cin >> k2;
			b.UpdateKey(k1, k2);
			cout << endl;
			cout << "New tree in level order: ";
			b.LevelOrder();
			cout << endl;
		}
		else if (choice == 12)
		{
			BST <int> a;
			cout << "a=b\n";
			a = b;
			cout << "a= ";
			a.LevelOrder();
			cout << endl;
			cout << "b= ";
			b.LevelOrder();
			cout << endl;
		}
		else if (choice == 13)
		{
			BST <int> a;
			cout << "a=b\n";
			a = b;
			cout << "a= ";
			a.LevelOrder();
			cout << endl;
			cout << "b= ";
			b.LevelOrder();
			cout << "\n a==b: " << (a == b);
			cout << endl;
		}

		else if (choice == 14)
		{
		    cout << "Total node: " << b.countNodes(); 
			cout << endl;

        }
		else if (choice == 15)
		{
		     cout << "Mirror version (a)";
			 BST<int> a;
			 a = b;
			 a.Mirror();
			 cout << "a= ";
			 a.LevelOrder();
			 cout << endl;
        }
		else if (choice == 16)
		{
		     cout << "Width = " << b.Width();
			 cout << endl;
		}
		else if (choice == 17)
		{
		     vector<int> sum;
			 b.pathSum(sum);
			 cout << endl;
			 for (int i = 0; i < sum.size(); i++)
				 cout << sum[i] << " ";
			 cout << endl;


		}
		else if (choice == 18)
		{
		   cout << "Skewed (a)";
		   BST<int> a;
		   a = b;
		   a.skew();
		   cout << "a= ";
		   a.LevelOrder();
		   cout << endl;
		}
		else if (choice == 19)
		{
		cout << "b.isBST() :" << b.isBST();
		cout << endl;

		}
		else if (choice == 20)
		{
		int k1, k2;
		cout << "enter the key1 ";
		cin >> k1;
		cout << "Enter the key2: ";
		cin >> k2;
		b.Common_Ancestors(k1, k2);
		cout << endl;
		}
		cin >> choice;
        
	}


//b.UpdateKey(8, 100);



//	b.LevelOrder();
	//b.skew();
	//cout << endl;
	//b.isBST();

	//BST b2;
	//b2.Insert(8);
	//b2.Insert(3);
	//b2.Insert(10);
	//b2.Insert(1);
	//b2.Insert(6);
	//b2.Insert(14);
	//b2.Insert(13);
	////b2.Insert(4);
	//b2.Insert(7);

	//b.Insert(50);
	//b.Insert(70);
	//b.Insert(40);
	//b.Insert(30);
	//b.Insert(45);
	//b.Delete(50);
	//cout << (b2 == b);
	//b.Delete(8);
	/*b.LRV();
	cout << endl;
	b.LRV_iterative();*/
	//vector<int> s;
	//b.pathSum(s);
//	b.LevelOrder();
	//b.Width();
	//BST<int> a;
	//a = b;
	//b.~BST();


}