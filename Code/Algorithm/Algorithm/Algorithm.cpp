// Algorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>

#include <algorithm>
#include <vector>
#include <string>

bool rotate1(char* lpVec, int n, int i);
bool rotate(char* lpVec, int n, int i);

void MaxSubArray(int vecNums[], int nlen);


void HeapSort(int vecNums[], int num);

void maxsubstr(std::string &fullstr);

int _tmain(int argc, _TCHAR* argv[])
{
	char szChars[10] = "abcdefgh";

	printf("Chars: %s\n", szChars);
	rotate(szChars, 8, 3);
	printf("Chars: %s\n", szChars);

	int vecNum[] = {31, -41, 59, 26, -53, 58, 97, -93, -23, 84,};
	MaxSubArray(vecNum, 10);

	for(int i = 0; i < 10; i++)
		printf("%d ", vecNum[i]);
	printf("\n");
	HeapSort(vecNum, 10);
	for(int i = 0; i < 10; i++)
		printf("%d ", vecNum[i]);
	printf("\n");

	//std::string fullstr;
	//fullstr = "Ask not what your country can do for you, but what you can do for your country";
	//maxsubstr(fullstr);

	system("pause");

	return 0;
}


//////////////////////////////////////////////////////////////////////////
// 一维向量旋转
// 
bool rotate1(char* lpVec, int n, int i)
{
	if(lpVec == NULL || n <= 0 || n < i)
		return false;

	if (n == i)
		return true;

	char * lpTemp = (char*)malloc(i);
	if (lpTemp == NULL)
		return false;
	for(int nI = 0; nI < i; nI++)
		lpTemp[nI] = lpVec[nI];

	for(int nI = i, nJ = 0; nI < n; nI++, nJ++)
		lpVec[nJ] = lpVec[nI];
	for(int nI = 0, nJ = n - i; nI < i; nI++, nJ++)
		lpVec[nJ] = lpTemp[nI];

	free(lpTemp);
	return true;
}


void revert(char* lpvec, int nlen)
{
	if (lpvec == NULL || nlen <= 0)
		return ;

	for(int i = 0; i < nlen / 2; i++)
	{
		char tmp = lpvec[i];
		lpvec[i] = lpvec[nlen - 1 - i];
		lpvec[nlen - 1 - i] = tmp;
	}
}

bool rotate(char* lpVec, int n, int i)
{
	if(lpVec == NULL || n <= 0 || n < i)
		return false;

	if (n == i)
		return true;

	revert(lpVec, i);
	revert(lpVec + i, n-i);
	revert(lpVec, n);

	return true;
}

//////////////////////////////////////////////////////////////////////////
void MaxSubArray1(int vecNums[], int nlen)
{
	int tI = -1, tJ = -1;
	int maxsum = 0;
	for (int i = 0; i < nlen; i++)
	{
		for(int j = i; j < nlen; j++)
		{
			int sum = 0;
			for(int k = i; k <= j; k++)
			{
				sum += vecNums[k];
			}

			if (maxsum < sum)
			{
				maxsum = sum;
				tI = i;
				tJ = j;
			}
		}
	}

	printf("maxsum: %d, i: %d, j: %d\n", maxsum, tI, tJ);
}

#define max(a, b) (a) > (b) ? (a) : (b)


void MaxSubArray(int vecNums[], int nlen)
{
	if (vecNums == NULL || nlen <= 0)
		return ;

	int maxsum = 0;
	int *lpMaxSum = (int*)malloc(nlen);
	if (NULL == lpMaxSum)
		return ;

	lpMaxSum[0] = vecNums[0];
	for (int i = 1; i < nlen; i++)
	{
		lpMaxSum[i] = max(lpMaxSum[i-1] + vecNums[i], vecNums[i]);
	}

	for(int i = 0; i < nlen; i++)
	{
		if(lpMaxSum[i] > maxsum)
			maxsum = lpMaxSum[i];
	}

	printf("maxsum: %d \n", maxsum);
}


void max_heap(int vecNums[], int start, int end)
{
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end)
	{
		// 判断有 右子节点， 如果有，判断左子节点是否小于右子节点
		// 用于判断 与 dad 节点进行对比的 子节点是哪个。
		if(son + 1 <= end && vecNums[son] < vecNums[son+1])
			son++;
		if(vecNums[dad] >= vecNums[son])
		{
			return ;
		}
		else
		{
			int temp = vecNums[son];
			vecNums[son] = vecNums[dad];
			vecNums[dad] = temp;

			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void HeapSort(int vecNums[], int num)
{
	if (vecNums == NULL || num <= 1)
		return ;

	for(int i = num / 2; i >= 0; i--)
		max_heap(vecNums, i, num - 1);

	for(int i = num - 1; i >= 0; i--)
	{
		int target = vecNums[0];
		vecNums[0] = vecNums[i];
		vecNums[i] = target;
		max_heap(vecNums, 0, i - 1);
	}
}

//////////////////////////////////////////////////////////////////////////

void maxsubstr(std::string &fullstr)
{
	std::string maxstr;
	std::vector<std::string> vecSubstrs;
	for(int i = 0; i < fullstr.length(); i++)
	{
		for(int j = i; j < fullstr.length(); j++)
		{
			std::string substr = fullstr.substr(i, j);
			if (vecSubstrs.end() != std::find(vecSubstrs.begin(), vecSubstrs.end(), substr))
			{
				if(substr.length() > maxstr.length())
					maxstr = substr;
			}
			else
			{
				vecSubstrs.push_back(substr);
			}
		}
	}

	printf("max sub string: %s\n", maxstr.c_str());
}