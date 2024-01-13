#include <iostream>
using namespace std;
int grid[15][15];
int chessboard[8][8];
int size2 = 15;
int reverseDigits(int n, int power)
{
	if (power == 1)
		return n;
	else
	{
		power--;
		return reverseDigits(n/10,power) + ((n % 10) * pow(10, power));
	}

}
void evenOdd(int* A, int size)
{
	if (size - 1 == 0)
		return;
	if (A[size - 1] % 2 == 0)
	{
		int temp = A[0];
		A[0] = A[size - 1];
		A[size - 1] = temp;
		A++;
		evenOdd(A, size );
 	}
	else
		evenOdd(A, size - 1);

}

bool check_sum(int* A, int size)
{
	if (size - 1 == 2)
	{
		if (A[size - 1] == A[size - 2] + A[size - 3])
			return true;
		else
			return false;
	}
	bool correct=check_sum(A, size - 1);
	if (correct)
	{
		if (A[size - 1] == A[size - 2] + A[size - 3])
			return true;
		else
			return false;
	}
	else 
		return false;
}
int countPaths(int n, int m)
{
	if (n >= size2)
		return 0;
	if (m < 0)
		return 0;

	if (grid[n][m] == -1)
		return 1;
	else
		return countPaths(n + 1, m) + countPaths(n, m - 1);
	
}

template <typename T>
bool binSearch(T *arr, int low, int high,T key)
{
	if (low >= high)
		return false;
	int middle = (low + high) / 2;
	if (arr[middle] == key)
		return true;
	else if (arr[middle] < key)
		return binSearch(arr, low, middle - 1, key);
	else
		return binSearch(arr, middle + 1, high, key);
}

void MergeSort(int arr[], int low, int high)
{
	if (low >= high)
		return;
	else
	{
		/*for (int i = low; i <= high; i++)
			cout << arr[i] << " ";
		cout << endl;*/
		int middle = (low + high) / 2;
		MergeSort(arr, low, middle);
		//cout << "\n********************\n";
		MergeSort(arr, middle + 1, high);

		//merging
		int size1 = middle-low+1;
		int* arr1 = new int[size1];
		int I = 0;
		for (int i = low; i <= middle; i++)
		{
			arr1[I] = arr[i];
			I++;
		}
		int size2 = high - middle;
		int* arr2 = new int[size2];
		int j = 0;
		for (int i = middle + 1; i <= high; i++)
		{
			arr2[j] = arr[i];
			j++;
		}
		
		int i = 0;
		j = 0;
		int k = low;

		while (i < size1 && j < size2)
		{
			if (arr1[i] < arr2[j])
			{
				arr[k] = arr1[i];
				k++;
				i++;
			}
			else
			{
				arr[k] = arr2[j];
				k++;
				j++;
			}
		}

		if (i < size1)
		{
			for (int x = i; x < size1; x++)
			{
				arr[k] = arr1[x];
				k++;
			}
		}
		if (j < size2)
		{
			for (int x = j; x < size2; x++)
			{
				arr[k] = arr2[x];
				k++;
			}
		}

		delete[]arr1;
		arr1 = nullptr;
		delete[]arr2;
		arr2 = nullptr;
	}
}


int factorial(int x)
{
	int fact=1;
	for (int i = 2; i <= x; i++)
		fact = fact * i;
	return fact;
}

int nCr(int n, int r)
{
	return factorial(n) / (factorial(r) * factorial(n - r));
}


void Subset(int*S,int size,int k,int Sindex,int Subsetindex,int& ith,int*singlesubset,int** allsubsets)
{
	if (Subsetindex == k)
	{
		for (int i = 0; i < k; i++)
		{
			allsubsets[ith][i] = singlesubset[i];
		}
		ith++;
		return;
	}
	if (Sindex >= size)
		return;
	singlesubset[Subsetindex] = S[Sindex];
	Subset(S, size, k, Sindex + 1, Subsetindex + 1, ith, singlesubset, allsubsets);
	Subset(S, size, k, Sindex + 1, Subsetindex, ith, singlesubset, allsubsets);
	
}

int** ComputeSubset(int* S, int size, int k)
{
	int size2 = nCr(size, k);
	int* single = new int[k];
	int** all = new int* [size2];
	for (int i = 0; i < size2; i++)
		all[i] = new int[k];
	int x = 0;
	Subset(S, size, k, 0, 0, x, single, all);
	delete[]single;


	return all;

}

void placeQueens(int** chessboard, int j=-1)
{
	if (j >= 8)
		return;
	else
	{
		for (int i = 0; i < 8; i++)
		{
			if (j != -1)
			{

			}
			placeQueens(chessboard, j + 1);
		}
	}
}

bool isSafe(int i, int j)
{
	int r = i;
	int c = j;
	if (i == -1 && j == -1)
		return true;
	if (i < 0 || i >= 8 || j < 0 || j >= 8)
		return false;
	while (r >= 0)
	{
		if (chessboard[r][c] == 1)
			return false;
		r--;
	}
	r = i;
	c = j;
	while (r < 8 && c < 8)
	{
		if (chessboard[r][c] == 1)
			return false;
		r++;
		c++;
	}
	r = i;
	c = j;
	while (r >= 0 && c >= 0)
	{
		if (chessboard[r][c] == 1)
			return false;
		r--;
		c--;
	}
	r = i;
	c = j;
	while (r < 8 && c >= 0)
	{
		if (chessboard[r][c] == 1)
			return false;
		r++;
		c--;
	}
	r = i;
	c = j;
	while (r >= 0 && c < 8)
	{
		if (chessboard[r][c] == 1)
			return false;
		r--;
		c++;
	}
	return true;
}

bool placeQueens(int i, int j)
{
	if (i >= 8)
		return true;
	else
	{
		int x = 0;
		if (chessboard[i][j-1] == 1)
		{
			x = j;
			chessboard[i][j-1] = 0;
		}
		bool safe = isSafe(i, x);
		while (!safe && x < 8)
		{
			x++;
			safe = isSafe(i, x);
		}
		if (safe)
		{
			chessboard[i][x] = 1;
			j = x;
		}
		else
			return false;
		
	}
	//j = 0;
	bool placed=placeQueens(i + 1, j);
	if (!placed)
	{
		//chessboard[i][j] = 0;
		placeQueens(i, j + 1);
	}
	
}


int main()
{

	cout << "------------------------------------ASSIGNMENT 4--------------------------------------\n";
	cout << "1.Reverse digits\n";
	cout << "2.Even odd sort\n";
	cout << "3.Check sum\n";
	cout << "4.Count paths\n";
	cout << "5.Binary Search\n";
	cout << "6.MergeSort\n";
	cout << "7.Place Queens\n";
	cout << "8.Find subsets\n";
	int choice = 0;
	cin >> choice;
	while (choice != 0)
	{
		if (choice == 1)
		{
			int x, power;
			cout << "Enter number: ";
			cin >> x;
			cout << "Enter length: ";
			cin >> power;
			
			cout << reverseDigits(x, power);
			cout << "\n---------------------------------------\n";
		}
		else if (choice == 2)
		{
			int size;
			cout << "Enter Size: ";
			cin >> size;
			int* arr = new int[size];
			cout << "Enter data: ";
			for (int i = 0; i < size; i++)
				cin >> arr[i];
			evenOdd(arr, size);
			for (int i = 0; i < size; i++)
			{
				cout << arr[i] << " ";
			}
			delete[]arr;
			arr = nullptr;
			cout << "\n---------------------------------------\n";
		}
		else if (choice == 3)
		{
			int size;
			cout << "Enter Size: ";
			cin >> size;
			int* arr = new int[size];
			cout << "Enter data: ";
			for (int i = 0; i < size; i++)
				cin >> arr[i];
			cout << check_sum(arr, size);
			delete[]arr;
			arr = nullptr;
			cout << "\n---------------------------------------\n";
		}
		else if (choice == 4)
		{
			for (int i = 0; i < size2; i++)
			{
				for (int j = 0; j < size2; j++)
					grid[i][j] = 0;
			}
			int i, j;
			
			cout << "enter starting point: ";
			int x, y;
			cin >> x >> y;
			cout << "enter the destination: ";
			cin >> i >> j;
			grid[i][j] = -1;
			cout << countPaths(x, y);
			cout << "\n---------------------------------------\n";
		}
		else if (choice == 5)
		{
			int size;
			cout << "Enter Size: ";
			cin >> size;
			int* arr = new int[size];
			cout << "Enter data: ";
			for (int i = 0; i < size; i++)
				cin >> arr[i];
			int key;
			cout << "Enter Key: ";
			cin >> key;
			cout << binSearch(arr, 0, size - 1, key);
			delete[]arr;
			arr = nullptr;
			cout << "\n---------------------------------------\n";
		}
		else if (choice == 6)
		{
			int size;
			cout << "Enter Size: ";
			cin >> size;
			int* arr = new int[size];
			cout << "Enter data: ";
			for (int i = 0; i < size; i++)
				cin >> arr[i];
			MergeSort(arr, 0, size - 1);
			for (int i = 0; i < size; i++)
				cout << arr[i] << " ";
			delete[]arr;
			arr = nullptr;
			cout << "\n---------------------------------------\n";
		}
		else if (choice == 7)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
					chessboard[i][j] = 0;
			}
			int j = 0;
			placeQueens(0, j);
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
					cout << chessboard[i][j] << " ";
				cout << endl;
			}
			cout << "\n---------------------------------------\n";
		}
		else if (choice == 8)
		{
		     int size;
		     cout << "Enter Size: ";
		     cin >> size;
		     int* arr = new int[size];
		     cout << "Enter data: ";
		     for (int i = 0; i < size; i++)
			     cin >> arr[i];
			 int k;
			 cout << "Enter the size of subsets: ";
			 cin >> k;
			 int** subsets = ComputeSubset(arr,size, k);
			 int size2 = nCr(size, k);
			 for (int i = 0; i < size2; i++)
			 {
				 for (int j = 0; j < k; j++)
					 cout << subsets[i][j] << " ";
				 cout << endl;
			 }
			 cout << "\n---------------------------------------\n";

        }
		else
		   cout << "\nwrong input\n";
		cin >> choice;
	}

	//cout << reverseDigits(12345, 5);
	//cout << "\n---------------------------------------\n";
	//
	//const int size = 7;
	//int arr[size] = { 1,2,5,3,6,8,9 };  //  
	//evenOdd(arr, size);
	//for (int i = 0; i < size; i++)
	//{
	//	cout << arr[i] << " ";
	//}

	//cout << "\n---------------------------------------\n";

	//int arr2[7] = { 2,3,5,8,13,21,34 };
	//cout << check_sum(arr2, 7);

	//cout << "\n---------------------------------------\n";
	//
	//
	//
	//for (int i = 0; i < size2; i++)
	//{
	//	for (int j = 0; j < size2; j++)
	//		grid[i][j] = 0;
	//}
	//grid[14][0] = -1;//destination
	////cout << countPaths(0, 14); //starting point

	//cout << "\n---------------------------------------\n";
	//cout << binSearch(arr, 0, 6, 1);

	//cout << "\n---------------------------------------\n";
	//int arr3[8] = { 0,3,5,1,8,2,4,7 };
	//MergeSort(arr3, 0, 7);
	//for (int i = 0; i < 8; i++)
	//	cout << arr3[i] << " ";

	//cout << "\n---------------------------------------\n";
	//int S[5] = { 1,2,3,4,6 };
	//int x = 0;
	//int** subsets = ComputeSubset(S, 5, 3);
	//for (int i = 0; i < 10; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//		cout << subsets[i][j] << " ";
	//	cout << endl;
	//}
	//cout << "\n---------------------------------------\n";
	//for (int i = 0; i < 8; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//		chessboard[i][j] = 0;
	//}
	//int j = 0;
	//placeQueens(0, j);
	//for (int i = 0; i < 8; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//		cout<<chessboard[i][j]<<" ";
	//	cout << endl;
	//}
    

}

