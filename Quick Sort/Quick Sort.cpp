#include <iostream>
#include <vector>
using namespace std;

void quickSort(vector <int> &arr)
{
	//int size=arr.size();//size will change on each recurssion
	if (arr.size()<2)
		return;

	vector<int> left;
	vector<int> right;

	int pivot = arr[0];//the first element of both left anf right will be the privot number

	for (int x = 1; x<arr.size(); x++)
	{
		if (arr[x]<pivot)
			left.push_back(arr[x]);
		else if (arr[x] >= pivot)
			right.push_back(arr[x]);
	}
	//recursive ends when size is < 2
	quickSort(left);
	quickSort(right);

	int i = 0;
	//hold all the elements from the left
	for (int x = 0; x<left.size(); x++)
	{
		arr[i++] = left[x];
		cout << left[x] << " ";
	}

	//hold the pivot number
	arr[i++] = pivot;
	cout << pivot << " ";

	//hold the elements from the right
	for (int x = 0; x<right.size(); x++)
	{
		arr[i++] = right[x];
		cout << right[x] << " ";
	}

	cout << endl;


}
int main()
{
	int n;
	cin >> n;

	vector <int> arr(n);
	for (int i = 0; i < (int)n; ++i) {
		cin >> arr[i];
	}

	quickSort(arr);

	return 0;
}
