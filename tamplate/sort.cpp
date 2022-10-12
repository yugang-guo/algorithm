#include <iostream>
using namespace std;
#include<string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

// 交换
void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void swap(int& a, int& b)
{
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

// 冒泡排序 O(n^2)

// 1-原始
void Bubble_Sort_1(vector<int>& nums)
{
	for (int end = nums.size() - 1; end > 0; end--)
	{
		for (int i = 0; i < end; i++)
		{
			if (nums[i] > nums[i + 1])
			{
				swap(nums[i], nums[i + 1]);
			}
		}
	}
}

// 2-isSort:是否已经有序
void Bubble_Sort_2(vector<int>& nums)
{
	for (int end = nums.size() - 1; end > 0; end--)
	{
		bool isSort = true;
		for (int i = 0; i < end; i++)
		{
			if (nums[i] > nums[i + 1])
			{
				swap(nums[i], nums[i + 1]);
				isSort = false;
			}
		}
		if (isSort) break;
	}
}

// 3-border:记录上一次最后交换的位置，下一轮交换只需要进行到这个位置即可
void Bubble_Sort_3(vector<int>& nums)
{
	for (int end = nums.size() - 1; end > 0; end--)
	{
		int border = 0;
		for (int i = 0; i < end; i++)
		{
			if (nums[i] > nums[i + 1])
			{
				swap(nums[i], nums[i + 1]);
				border = i + 1;
			}
		}
		end = border;
	}
}

// 4-鸡尾酒排序：定向冒泡排序，同时的冒泡两边
void Bubble_Sort_4(vector<int>& nums)
{
	int left = 0, right = nums.size() - 1;
	while (left < right)
	{
		for (int i = left; i < right; i++)
		{
			if (nums[i] > nums[i + 1])
			{
				swap(nums[i], nums[i + 1]);
			}
		}
		right--;

		for (int i = right; i > left; i--)
		{
			if (nums[i] < nums[i - 1])
			{
				swap(nums[i - 1], nums[i]);
			}
		}
		left++;
	}
}

// 选择排序 O(n^2)

// 每次从待排序列中选出一个最小值，然后放在序列的起始位置，直到全部待排数据排完即可

void Select_Sort(vector<int>& nums)
{
	for (int i = 0; i < nums.size(); i++)
	{
		int start = i, min = i;
		while (start < nums.size())
		{
			if (nums[start] < nums[min]) min = start;
			start++;
		}
		if (min != i) swap(nums[i], nums[min]);
	}
}

// 插入排序 O(n^2)

// 在待排序的元素中，假设前n-1个元素已有序，现将第n个元素插入到前面已经排好的序列中，使得前n个元素有序。按照此法对所有元素进行插入，直到整个序列有序。

void Insert_Sort(vector<int>& nums)
{
	for (int i = 1; i < nums.size(); i++)
	{
		int insert_value = nums[i];
		int insert_pos = i;
		while (insert_pos > 0 && nums[insert_pos - 1] > insert_value)
		{
			nums[insert_pos] = nums[insert_pos - 1];
			insert_pos--;
		}
		nums[insert_pos] = insert_value;
	}
}

// 归并排序 O(nlogn)

// 将已有序的子序合并，从而得到完全有序的序列，即先使每个子序有序，再使子序列段间有序。

void merge(vector<int>& nums, int left, int mid, int right) // 左闭右闭
{
	vector<int> left_nums;
	vector<int> right_nums;

	for (int i = left; i <= right; i++)
	{
		if (i <= mid) left_nums.push_back(nums[i]);
		else right_nums.push_back(nums[i]);
	}

	int i = 0, j = 0, k = left;
	while (i < left_nums.size() && j < right_nums.size())
	{
		if (left_nums[i] < right_nums[j])
		{
			nums[k] = left_nums[i];
			k++;
			i++;
		}
		else
		{
			nums[k] = right_nums[j];
			k++;
			j++;
		}
	}
	while (i < left_nums.size())
	{
		nums[k] = left_nums[i];
		k++;
		i++;
	}
	while (j < right_nums.size())
	{
		nums[k] = right_nums[j];
		k++;
		j++;
	}
}

void Merge_Sort(vector<int>& nums, int left, int right) // 左闭右闭
{
	if (left == right) return;
	else
	{
		int mid = left + (right - left) / 2;
		Merge_Sort(nums, left, mid);
		Merge_Sort(nums, mid + 1, right);
		merge(nums, left, mid, right);
	}
}

// 堆排序 O(nlogn)

void heapify(vector<int>& nums, int nums_size, int root)
{
	if (root >= nums_size) return;
	int left_child = root * 2 + 1;
	int right_child = root * 2 + 2;
	int max = root;
	if (left_child < nums_size && nums[left_child] > nums[max])
	{
		max = left_child;
	}
	if (right_child < nums_size && nums[right_child] > nums[max])
	{
		max = right_child;
	}
	if (max != root)
	{
		swap(nums[root], nums[max]);
		heapify(nums, nums_size, max);
	}
}

void Heap_Sort(vector<int>& nums)
{
	// build heap
	int last_node = nums.size() - 1;
	int parent = (last_node - 1) / 2;
	for (int i = parent; i >= 0; i--)
	{
		heapify(nums, nums.size(), i);
	}

	// sort
	for (int i = nums.size() - 1; i >= 0; i--)
	{
		swap(nums[i], nums[0]);
		heapify(nums, i, 0);
	}
}

// 希尔排序

void Shell_Sort(vector<int>& nums)
{
	// 初始增量gap=len/2，每一趟之后除以二
	for (int gap = nums.size() / 2; gap > 0; gap /= 2)
	{
		//插入排序
		for (int i = gap; i < nums.size(); i++)
		{
			int insert_value = nums[i];
			int insert_pos = i;
			while (insert_pos >= gap && nums[insert_pos - gap] > insert_value)
			{
				nums[insert_pos] = nums[insert_pos - gap];
				insert_pos -= gap;
			}
			nums[insert_pos] = insert_value;
		}
	}
}

// 快速排序 O(nlogn)

int partition(vector<int>& nums, int left, int right) // 左闭右闭
{
	int pivot = nums[right];
	int i = left;
	for (int j = left; j < right; j++)
	{
		if (nums[j] <= pivot)
		{
			swap(nums[i], nums[j]);
			i++;
		}
	}
	swap(nums[i], nums[right]);
	return i;
}

void Quick_Sort(vector<int>& nums, int left, int right) // 左闭右闭
{
	if (left < right)
	{
		int mid = partition(nums, left, right);
		Quick_Sort(nums, left, mid - 1);
		Quick_Sort(nums, mid + 1, right);
	}
}