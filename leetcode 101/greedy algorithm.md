# 贪心算法

思想：采用贪心的策略，保证每次操作都是局部最优的，从而使最后得到的结果是全局最优的。


# 分配问题

## 455. 分发糖果

输入两个数组，分别代表孩子的饥饿度和饼干的大小。输出最多有多少孩子可以吃饱的数量。

Input: [1,2], [1,2,3]

Output: 2

```cpp
int findContentChildren(vector<int>& children, vector<int>& cookies)
{
	sort(children.begin(), children.end());
	sort(cookies.begin(), cookies.end());
	int child, cookie;
	for (child = 0, cookie = 0; child < children.size() && cookie < cookies.size(); ++cookie)
	{
		if (cookies[cookie] >= children[child]) ++child;
	}
	return child;
}
```


## 135. 分发饼干

一群孩子站成一排，每一个孩子有自己的评分。现在需要给这些孩子发糖果，规则是如果一个孩子的评分比自己身旁的一个孩子要高，那么这个孩子就必须得到比身旁孩子更多的糖果；所有孩子至少要有一个糖果。求解最少需要多少个糖果。

输入是一个数组，表示孩子的评分。输出是最少糖果的数量。

Input: [1,0,2]

Output: 5

在这个样例中，最少的糖果分法是 [2,1,2]。

```cpp
int candy(vector<int>& ratings)
{
	vector<int> candy(ratings.size(), 1);
	for (int i = 1; i < candy.size(); ++i)
	{
		if (ratings[i] > ratings[i - 1]) candy[i] = candy[i - 1] + 1;
	}
	for (int i = candy.size() - 2; i >= 0; --i)
	{
		if (ratings[i] > ratings[i + 1]) candy[i] = max(candy[i], candy[i + 1] + 1);
	}
	return accumulate(candy.begin(), candy.end(), 0);
}
```


# 区间问题

## 435. 无重叠区间

给定多个区间，计算让这些区间互不重叠所需要移除区间的最少个数。起止相连不算重叠。

输入是一个数组，数组由多个长度固定为 2 的数组组成，表示区间的开始和结尾。输出一个整数，表示需要移除的区间数量。

Input: [[1,2], [2,4], [1,3]]

Output: 1

```cpp
int eraseOverlapIntervals(vector<vector<int>>& intervals)
{
	sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {return a[1] < b[1];});
	int result = 0;
	int end = intervals[0][1];
	for (int i = 1; i < intervals.size(); ++i)
	{
		if (intervals[i][0] < end) ++result;
		else end = intervals[i][1];
	}
	return result;
}
```


# 练习

## 605. 种花问题 (Easy)

假设有一个很长的花坛，一部分地块种植了花，另一部分却没有。可是，花不能种植在相邻的地块上，它们会争夺水源，两者都会死去。

给你一个整数数组flowerbed表示花坛，由若干0和1组成，其中0表示没种植花，1表示种植了花。另有一个数能否在不打破种植规则的情况下种入n朵花？能则返回true ，不能则返回false。

Input：flowerbed = [1,0,0,0,1], n = 1

Output：true

Input：flowerbed = [1,0,0,0,1], n = 2

Output：false

```cpp
bool canPlaceFlowers(vector<int>& flowerbed, int n)
{
	for (int i = 0; i < flowerbed.size(); i += 2)
	{
		if (flowerbed[i] == 0)
		{
			if (i == flowerbed.size() - 1 || flowerbed[i + 1] == 0) --n;
			else ++i;
		}
	}
	return n <= 0;
}
```


## 452. 用最少量的箭引爆气球 (Medium)

有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组points，其中points[i] = [xstart, xend]表示水平直径在xstart和xend之间的气球。你不知道气球的确切 y 坐标。

一支弓箭可以沿着x轴从不同点完全垂直地射出。在坐标x处射出一支箭，若有一个气球的直径的开始和结束坐标为xstart，xend，且满足xstart≤x≤xend，则该气球会被引爆。可以射出的弓箭的数量没有限制 。 弓箭一旦被射出之后，可以无限地前进。

给你一个数组points，返回引爆所有气球所必须射出的最小弓箭数。

Input：points = [[10,16],[2,8],[1,6],[7,12]]

Output：2

```cpp
int findMinArrowShots(vector<vector<int>>& points)
{
	sort(points.begin(), points.end(), [](vector<int>& a, vector<int>& b) {return a[0] < b[0];});
	int result = 1;
	int end = points[0][1];
	for (int i = 1; i < points.size(); ++i)
	{
		if (points[i][0] > end)
		{
			++result;
			end = points[i][1];
		}
		else
		{
			end = min(end, points[i][1]);
		}
	}
	return result;
}
```


## 763. 划分字母区间 (Medium)

**贪心的预处理**

字符串 S 由小写字母组成。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。返回一个表示每个字符串片段的长度的列表。

Input：S = "ababcbacadefegdehijhklij"

Output：[9,7,8]

```cpp
vector<int> partitionLabels(string s)
{
	vector<int> count(27, -1);
	for (int i = 0; i < s.size(); ++i)
	{
		count[s[i] - 'a'] = i;
	}
	vector<int> result;
	int begin = 0;
	int max_end = count[s[0] - 'a'];
	for (int i = 0; i < s.size(); ++i)
	{
		if (i == max_end)
		{
			result.push_back(max_end - begin + 1);
			if (i + 1 < s, size())
			{
				begin = i + 1;
				max_end = count[s[i + 1] - 'a'];
			}
		}
		else
		{
			max_end = max(max_end, count[s[i] - 'a']);
		}
	}
	return result;
}
```


## 122. 买卖股票的最佳时机Ⅱ (Easy)

给你一个整数数组 prices ，其中prices[i] 表示某支股票第 i 天的价格。

在每一天，你可以决定是否购买和或出售股票。你在任何时候最多只能持有一股股票。你也可以先购买，然后在同一天出售。返回你能获得的最大利润。

input：prices = [7,1,5,3,6,4]

Output：7

```cpp
int maxProfit(vector<int>& prices)
{
	int result = 0;
	for (int i = 1; i < prices.size(); ++i)
	{
		result += max(prices[i] - prices[i - 1], 0);
	}
	return result;
}
```


## 406. 根据身高重建队列 (Medium)

假设有打乱顺序的一群人站成一个队列,数组people表示队列中一些人的属性（不一定按顺序）。每个people[i] = [hi, ki] 表示第i个人的身高为hi,前面正好有ki个身高大于或等于hi的人。

请你重新构造并返回输入数组people所表示的队列。返回的队列应该格式化为数组queue，其中queue[j] = [hj, kj] 是队列中第j个人的属性（queue[0] 是排在队列前面的人）。

Input：people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]

Output：[[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]

```cpp
vector<vector<int>> reconstructQueue(vector<vector<int>>& people)
{
	sort(people.begin(), people.end(), [](vector<int>& a, vector<int>& b) {if (a[0] != b[0]) return a[0] > b[0]; else return a[1] < b[1];});
	list<vector<int>> queue;
	for (int i = 0; i < people.size(); ++i)
	{
		list<vector<int>>::iterator it = queue.begin();
		int pos = people[i][1];
		while (pos-- > 0) ++it;
		queue.insert(it, people[i]);
	}
	return  vector<vector<int>>(queue.begin(), queue.end());
}
```


## 665. 非递减数列 (Medium)

给你一个长度为n的整数数组nums，请你判断在最多改变1个元素的情况下，该数组能否变成一个非递减数列。

我们是这样定义一个非递减数列的：对于数组中任意的i (0 <= i <= n-2)，总满足 nums[i] <= nums[i + 1]。

Input: nums = [4,2,3]

Output: true

Input: nums = [4,2,1]

Output: false

```cpp
bool checkPossibility(vector<int>& nums)
{
	int count = 0;
	for (int i = 1; i < nums.size(); ++i)
	{
		if (nums[i] < nums[i - 1])
		{
			++count;
			if (count > 1) return false;
			if (i - 2 >= 0 && nums[i] < nums[i - 2]) nums[i] = nums[i - 1];
			else nums[i - 1] = nums[i];
		}
	}
	return true;
}
```