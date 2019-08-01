
# 算法总结 #

语言基础要有一到两个擅长，对语法要比较熟悉。

数据结构也是考察重点：

* 数组
* 链表
* 树（二叉树，红黑树）
* 栈
* 队列
* 哈希表
* 位数组/位操作

常用算法：

* 查找: 二分查找
* 排序：归并排序，快速排序，堆排序
* 递归
* 分治算法
* 动态规划：
* 贪婪算法
* 贪婪算法

在面对实际问题时，要采用画图，举例以及分解等方法帮助寻找思路。


## 算法示例 ##

《编程珠玑》第二版中题目汇总。

### 整数排序 ###

**输入**：所输入的是一个文件，至多包含n个整数，每个整数都要小于n，这里n=10^7。如果输入某个整数出现了两次，就导致错误。这些整数与任何数据都不关联。

**输出**：以增序形式输出经过排序的整数列表。

**约束**：至多只有1MB的可用主存；但是可用磁盘空间非常充足。运行时间至多只允许几分钟，10秒钟是最适宜的运行时间。

解法1：

1M内存可以存储250000个32位数字，所以可以将文件分为40次排序，第一次排0-249999之间的数，将它写入一个文件；然后依次排序后面39个区间。最后将排序完成的四十个文件拼接起来形成最终文件。

解法2：

其实这里要求所有的数组不出现重复，所以可以用位图的方式来进行。比如2M内存，就有足够的位来表示 10^7 的数，这样在O(n)时间内就可以完成排序。但是如果严格限制1M，而10^7最少需要 1.25M内存，所以这里可以参考解法1，将所有数据分为两个区间来排序—— 小于5000000依次排序，大于5000000的数一次排序即可。

### 查找不存在的数字 ###

**题目**: 给定一个包含32位整数的顺序文件，至多只能包含40亿个这样的整数，并且整数的次序随机。请查找一个此文件中不存在的32位整数（至少必有一个数不存在）。在足够主存情况下会如何解决问题？如果你可以使用若干外部临时文件但主存却只有上百个字节，如何解决这个问题？


###一维向量旋转###

请将一个具有n个元素的一维向量向左旋转i个位置。例如假设n=8，i=3，那么向量abcdefgh旋转之后得到向量defghabc。简单编码，使用一个具有n个元素的中间向量分n步完成此作业。你也可以仅使用几十字节微笑内存，花费与n成比例的时间来完成旋转该向量吗？


### 同位词 ###

给定一本英语单词词典，请找出所有的变位词集合。例如因为“pots”，“stop”，“tops”相互之间都是有另一个词的各个字母改变顺序构成，因此这些词相互之间就是变位词。


### 一维模式识别 ###

输入一个具有n个浮点数字的向量x，其输出是在输入的任何相邻子向量中找出最大和。例如，如果输入向量为如下10个元素，返回值则返回x[2..6]的总和。


```
31 -41 59 26 -53 58 97 -93 -23 84
```

> 四个算法，三阶，二阶，线性

### 排序算法 ###

**冒泡排序**

冒泡排序时间复杂度为O(n^2)。

**插入排序**

插入排序时间复杂度为O(n^2)。

**快速排序**

快速排序使用了分治法，将向量分为两个子向量，再递归对其进行排序。其时间复杂度为O(nlogn)。其实快速排序与性能最差的时候，即原始数组是逆序的时候，时间复杂度大到O(n^2)。

**堆排序**

使用类似二叉树的思想，将堆的高度限制为 logn，排序n个节点，时间复杂度最多也就是O(nlogn)，并且没有额外空间的使用，只需要n个空间的原始向量即可。

### 字符串最长子串 ###

给定一个输入文本文件，查找其中最常的重复子字符串。例如“Ask not what your country can do for you, but what you can do for your country”中最常的重复字符串就是“can do for you”，“your country”是第二长子串。如何编写解决这个问题的程序？

二次循环，计算出所有的子串，然后找到最常重复子串。时间复杂读为O(n^2)


使用后缀数组，时间复杂度为O(nlogn)。

### 字符串转整数 ###

将一个字符串转换成整数。

> 考察代码完整性，鲁棒性（边界值，输入参数检查，输入错误等）

```
int StrToInt(char* str)
```

### 求链表中倒数第K个节点 ###

给一个链表，求链表的倒数第k个节点。

> 这个题目使用快慢指针也比较简单，但是要考虑程序完整性与鲁棒性


'''
ListNode× FindKthToTail(ListNode* pListHead, unsigned int k)
'''


> 在解答简单题目时，一定考虑边界条件，特殊输入（NULL，空串，错误字符串等）以及错误处理。


### 递归算法 ###

斐波那契数列，典型的递归算法计算。

青蛙跳台问题，一只青蛙一次可以跳上一级台阶，也可以跳上2级台阶，请问这只青蛙跳上n级台阶总共有多少种跳法。

### 二维数组查找 ###

** 题目描述 **

在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

最坏的解决方法就是将整个数组进行遍历，二维数组，时间复杂度为 O(n^2)。

[

]

```
class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        bool bFind = false;
        int nX = 0;
        int nY = array[0].size() - 1;
        while(nX < array.size() && nY >= 0)
        {
            if(array[nX][nY] == target)
            {
                bFind = true;
                break;
            }

            if(array[nX][nY] < target)
            {
                nX++;
            }
            else if(array[nX][nY] > target)
            {
                nY--;
            }
        }

        return bFind;
    }
};
```

### 替换空格 ###

**题目描述**

请实现一个函数，将一个字符串中的每个空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。

```
class Solution {
public:
	void replaceSpace(char *str,int length) {
    	if (str == null)
        	return ;

        char * orgStr = str;
        int strLen = 0;
        int emptyNum = 0;
        while(*orgStr != 0)
        {
            strLen++;
            if (*orgStr == ' ')
                emptyNum++;
            orgStr++;
        }

        int newLen = strLen + emptyNum * 2;
        if (newLen > length)
            return ;

        orgStr = str + strLen;
        char * replStr = str + newLen;
        while (orgStr >= str)
        {
            if(*orgStr != ' ')
            {
                *replStr-- = *orgStr;
            }
            else
            {
                *replStr-- = '0';
                *replStr-- = '2';
                *replStr-- = '%';
            }
            orgStr--;
        }
	}
};
```

### 两数之和 ###

给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。

```
给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]
```

最简单的方法就是内外两个循环，一次将数组两个元素相加，如果等于target，则找到。但是这种方法的时间复杂度为O(n^2)。可以利用如下方法，额外占用空间，但是时间复杂度可以降低为O(n)。

将数组元素放到哈希表中，然后依次用target和数组元素的差搜索哈希表，这样可以将时间复杂度降低为O(n)。

```
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> vecRet;
        std::map<int, int> hashMap;

        int nNums = nums.size();
        for(int i = 0; i < nNums; i++)
        {
            hashMap.insert(std::pair<int,int>(nums[i], i));
        }

        for(int i = 0; i < nNums; i++)
        {
        	if (nums[i] > target)
            	continue;

            int diffVal = target - nums[i];
            if( hashMap.find(diffVal) != hashMap.end() && i != hashMap[diffVal])
            {
                vecRet.push_back(i);
                vecRet.push_back(hashMap[diffVal]);
                break;
            }
        }

        return vecRet;
    }
};
```

> 来源：力扣（LeetCode）























































