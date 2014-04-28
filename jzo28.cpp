#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

#define MAX 10

void Swap(char *a, char *b)
{
	char tmp;
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
int QuickSortPartition1(char *arr, int left, int right)
{
	if (arr == NULL || left < 0 || right < 0 || left > right)
		return 0;
	int rand_num = Rand(left, right); //���������׼��
	//cout << rand_num << endl;
	//int rand_num = left;
	//����׼ֵ���ַ����ĵ�һ���ַ�������������һ��λ�õ��ַ���ɻ�׼ֵ��
	//��׼ֵ������ref�У����ڵ�һ��λ�ò����˿�ȱλ
	Swap(&arr[rand_num], &arr[left]);
	char ref = arr[left]; 
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

//����һ���ǿ�����ָoffer����Ŀ��ŷ�������������һ�ֲ��ȶ��������㷨��
//ֻ����һ��ѭ�������ַ�����ͷ�������ַ���β�����Ǹ�֮ǰһ�����߱���
int QuickSortPartition2(char *arr, int left, int right)
{
	if (arr == NULL || left < 0 || right < 0 || left >= right)
		return 0;
	int rand_num = Rand(left, right);
	//����׼ֵ�ŵ��ַ���β������֮���ѭ���Ƚ���λ�û���
	Swap(&arr[rand_num], &arr[right]);
	
	//ע��smallλ��ָ�����Ҫ����
	//��ָ���Ѿ������������Ǹ�λ��
	int small = left - 1;
	for (int i = left; i < right; i++)
	{
		//���Ȼ�׼ֵ����ַ��Ź�����������С�����������smallָ���λ�ý��н���
		//��small֮ǰ���ַ����ǽ������ģ�Ҳ���ǱȻ�׼ֵС�ģ���small֮��i֮ǰ���ַ�
		//����û�н������ұȻ�׼ֵ��ģ��������ܱ�֤ÿ�ν�����ʱ�򣬶����ҵ���С��
		//�ַ���֮ǰ����ַ����н������ﵽ�����ǵ�Ŀ��
		if (arr[i] < arr[right])
		{
			++small;
			//���ٲ���Ҫ�Ľ���
			if (small != i)
				Swap(&arr[small], &arr[i]);
		}
	}
	++small; 
	//small��ɴ�����ĵ�һ��λ�ã������ͻ�׼ֵ����
	Swap(&arr[small], &arr[right]);
	return small;
}



void QuickSort(char *arr, int left, int right)
{
	if (arr == NULL || left < 0 || right < 0 || left >= right)
		return;
	int i = QuickSortPartition1(arr, left, right);
	//int i = QuickSortPartition2(arr, left, right);
	if (i > left)
		QuickSort(arr, left, i - 1);
	if (i < right)
		QuickSort(arr, i + 1, right);
}

//�ж�������arr�е�[n��end)λ֮���Ƿ�����arr[end]�ظ����ַ�
bool IsSwap(char *arr, int begin, int end)
{
	for (int k = begin; k < end; k++)
	if (*(arr + k) == *(arr + end))
		return false;
	return true;
}

//ȫ���о��Ǵӵ�һ��������ÿ�����ֱ�������������ֽ���
//�ݹ��㷨������������ַ����ظ������!
void FullPermutation(char *arr, int len, int index)
{
	int i;
	if (index == len)
	{
		printf("%s\n", arr);
		return;
	}
	for (i = index; i <= len; i++)
	{
		//arr[index..i)֮��û�к�arr[i]�ظ����ַ�����Ϊtrue
		if (IsSwap(arr, index, i))
		{
			Swap(arr + index, arr + i);
			FullPermutation(arr, len, index + 1);
			Swap(arr + index, arr + i);
		}
	}
}






void sub(char *arr, vector<char> &path, vector<bool> &used)
{
	int len = strlen(arr);
	if (path.size() == len)
	{
		for (int i = 0; i < len; i++)
			printf("%c", path[i]);
		printf("\n");
		return;
	}

	for (int i = 0; i < len; i++)
	{
		//����ʹ���Ѿ��õ��˵����֡��������ͬ�����������ڵ���,Ϊ�˱����ظ������
		if (used[i] || (i != 0 && arr[i] == arr[i - 1] && used[i - 1]))
			continue;
		used[i] = true;
		path.push_back(arr[i]);
		sub(arr, path, used);
		used[i] = false;
		path.pop_back();
	}
}

//��ͨ����ȫ���еĵݹ��㷨���ݹ��ӡ��һ�����У����԰��ֵ����ӡ
void FullPermutation3(char *arr)
{
	vector<bool> used(strlen(arr), false);
	vector<char> path;
	sub(arr, path, used);
}







void Reverse(char *arr, int start, int end)
{
	while (start < end)
	{
		Swap(&arr[start], &arr[end]);
		start++;
		end--;
	}
}

//������һ��ȫ���У��������õ�ȫ����
//�Ӻ���ǰɨ�裬ֱ���������ڵ������ǽ���ģ����ҵ���������ģ���С���Ǹ�����������Ҫ�ҵģ��滻����
//�ٽ������ʹ��ҵ���ı�����ĵ�һ�����������ٰ��滻��֮������ֵߵ���������һ������
bool NextPermutation(char *arr)
{
	if (arr == NULL)
		return false;
	int end = strlen(arr) - 1;
	int bigger;
	for (int i = end; i > 0;)
	{
		int j = i;
		i--;
		//�ҵ��������������С����Ϊ�滻��
		if (arr[i] < arr[j])
		{
			//������Ҫ�滻�����������������һ�����滻�������
			//�ҿ϶�����
			bigger = end;
			while (bigger > i && arr[bigger] <= arr[i])
				--bigger;
			Swap(&arr[bigger], &arr[i]);
			//���滻��֮������ַ�ת
			Reverse(arr, j, end);
			return true;
		}
	}
	Reverse(arr, 0, end);
	return false;
}

//ȫ���еķǵݹ��㷨
void FullPermutation2(char *arr)
{
	if (arr == NULL)
		return;
	do
	{
		printf("%s\n", arr);
	} while (NextPermutation(arr));
}



int main(void)
{
	char arr[MAX];

	while (cin >> arr)
	{
		if (arr == NULL)
			continue;
		
		//�õݹ�ⷨ���޷��õ��ֵ��򣬾����Ƚ�������Ҳ�޷��õ�
		//FullPermutation(arr, strlen(arr) - 1, 0);
		//�ǵݹ�ⷨ
		//Ҫ�õ��ֵ����ȶ��ַ�����������ʹ�õĿ���
		QuickSort(arr, 0, strlen(arr) - 1);
		//FullPermutation2(arr);
		//�ݹ��㷨��������Եõ��ֵ���
		FullPermutation3(arr);
	}

	system("pause");
	return 0;
}