#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

#define MAX 100000

void Swap(unsigned long *a, unsigned long *b)
{
	unsigned long tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}



//����������ŵĻ�׼���λ��
int Rand(int a, int b)
{
	return (int)(a + rand() % (b - a + 1));
}

//�����ڿӡ����ַ������ߡ�ͬʱ����ʼ�Ƚϵķ����������ķ���
//��Ҫһ������Ŀռ�O(1)�����׼ֵ
int QuickSortPartition1(unsigned long *arr, int left, int right)
{
	if (arr == NULL || left < 0 || right < 0 || left > right)
		return 0;
	int rand_num = Rand(left, right); //���������׼��
	//cout << rand_num << endl;
	//int rand_num = left;
	//����׼ֵ���ַ����ĵ�һ���ַ�������������һ��λ�õ��ַ���ɻ�׼ֵ��
	//��׼ֵ������ref�У����ڵ�һ��λ�ò����˿�ȱλ
	Swap(&arr[rand_num], &arr[left]);
	unsigned long ref = arr[left]; 
	int i, j;
	i = left;
	j = right;
	while (i < j)
	{
		//�ȴӺ�����ǰ��Ƚ� ����Ϊ��׼ֵ�����ַ����ĵ�һ������С�����׼ֵ�ģ�
		while (i < j && arr[j] >= ref)
			j--;
		//���ȱ
		if (i < j)
		{
			arr[i] = arr[j];
			i++;
		}
		//��ǰ����Ƚ�
		while (i < j && arr[i] <= ref)
			i++;
		if (i < j)
		{
			arr[j] = arr[i];
			j--;
		}
	}
	//���Ŀ�ȱ��i=j������ref��ֵ�ŵ����м䡱��ǰ��С�ڸ�ֵ������Ĵ��ڸ�ֵ
	arr[i] = ref;
	//iֵ������ַ�����Ϊ�������֣��������iֵ������֮����εĽ���
	return i;
}

bool CheckMoreThanHalf(unsigned long *numbers, int length, unsigned long result)
{
	int count = 0;
	for (int i = 0;i < length; i++)
	{
		if (numbers[i] == result)
			count ++;
	}
	if (count * 2 <= length)
		return false;
	else
		return true;
}


int MoreThanHalfNum1(unsigned long *numbers, int length)
{
	if (numbers == NULL || length <= 0)
	{
		printf("-1\n");
		return 0;
	}
	int middle = length >> 1;
	int left = 0, right = length - 1, index;
	index = QuickSortPartition1(numbers, left, right);
	while (index != middle)
	{
		if (index < middle)
			index = QuickSortPartition1(numbers, index + 1, right);
		else if(index > middle)
			index = QuickSortPartition1(numbers, left, index - 1);
	}
	unsigned long result = numbers[middle];

	int count = 0;
	for (int i = 0;i < length; i++)
	{
		if (numbers[i] == result)
			count ++;
	}
	if (count * 2 <= length)
		printf("-1\n");
	else
		printf("%lu\n", result);

	return 0;
}

int MoreThanHalfNum2(unsigned long *numbers, int length)
{
	int i;
	int count = 1;
	unsigned long num = numbers[0];
	for (i = 0; i < length; i++)
	{
		if (count == 0)
		{
			count = 1;
			num = numbers[i];
		}
		else if (numbers[i] != num)
			count --;
		else
			count ++;
	}
	if (!CheckMoreThanHalf(numbers, length, num))
		printf("-1\n");
	else
		printf("%lu\n", num);
	return 0;
}



int main(void)
{
	int  n;

	while (scanf("%d", &n) != EOF)
	{
		unsigned long numbers[MAX];
		for (int i = 0; i < n; i++)
			scanf("%lu", &numbers[i]);
		MoreThanHalfNum1(numbers, n);


	}

	system("pause");
	return 0;
}