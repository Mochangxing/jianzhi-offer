#include <iostream>
#include <cstdio>


using namespace std;

#define MAX 100010

//Ҳ�����ö�̬�滮��˼������
// f(i) = numbers[i]           ,  i = 0 || f(i - 1) < 0 
//        f(i - 1) + numbers[i],  i != 0 && f(i - 1) >= 0
// ����=��λ�ÿ��Ը�����ĿҪ���������Ҫ��õ����ַ�����Ԫ���±���С���Ǹ�
// ��ô��Ҫ�������������
void FindGreatedstSumOfSubArray(int *numbers, int length)
{
	int sum = 0, start_max = 0, start = 0, end = 0;
	int max_sum = -2147483647 - 1; //������С���ķ���
	if (numbers == NULL || length <= 0)
		return ;
	for (int i = 0; i < length; i++)
	{
		if (sum < 0)
		{
			start = i;
			sum = numbers[i];
		}
		else
			sum += numbers[i];
		if (sum > max_sum)
		{
			end = i;
			start_max = start;
			max_sum = sum;
		}
	}
	printf("%d %d ", max_sum, start_max);
	printf("%d\n", end);
}


int main(void)
{
	int  n;
	scanf("%d", &n);
	while (n != 0)
	{
		int numbers[MAX];
		for (int i = 0; i < n; i++)
			scanf("%d", &numbers[i]);
		FindGreatedstSumOfSubArray(numbers, n);
		

		scanf("%d", &n);
	}

	system("pause");
	return 0;
}