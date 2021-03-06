#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0


typedef void (*sort_func)(int*, int);

typedef void (*sort_func_div)(int*, int, int);

#define get_name(var) #var

#define MAX 100

int c[MAX];


int my_random(int bound)
{
	return rand()%bound;
}



// generate random array with given size and range
int* generate_random_array(int size, int max)
{
	if (size < 1)
	{
		printf("size error\n");
		return NULL;
	}
	int *array = (int*)malloc(size*sizeof(int));
	int i;
	for(i = 0; i < size; i++)
	{
		array[i] = my_random(max);
	}
	return array;
}


void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}


// reverse an array
void reverse(int *array, int n)
{
	if (n < 1)
	{
		printf("array size error\n");
		return;
	}
	int i;
	for (i =0; i < n/2; i++)
		swap(&array[i], &array[n-i-1]);
}

// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(n^2)
// 最优时间复杂度 ---- 如果能在内部循环第一次运行时,使用一个旗标来表示有无需要交换的可能,可以把最优时间复杂度降低到O(n)
// 平均时间复杂度 ---- O(n^2)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 稳定
void bubble_sort(int *array, int n)
{
	printf("bubble_sort\n");
	if (n < 1)
	{
		printf("array size error\n");
		return;
	}

	int i, j;
	for (i = n-1; i >= 0; i--)
	{
		int flag = 0;
		for (j = 0; j < i; j++)
		{
			if (array[j] > array[j+1])
			{
				flag = 1;
				swap(&array[j], &array[j+1]);
			}
		}
		if (!flag) break;
	}
}


// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(n^2)
// 最优时间复杂度 ---- 如果序列在一开始已经大部分排序过的话,会接近O(n)
// 平均时间复杂度 ---- O(n^2)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 稳定
void cocktail_sort(int *array, int n)
{
	printf("cocktail_sort\n");
	if (n < 1)
	{
		printf("array size error\n");
		return;
	}

	int left = 0;
	int right = n-1;
	int i;
	while (left < right)
	{
		for (i = left; i < right; i++)
		{
			if (array[i] > array[i+1])
				swap(&array[i], &array[i+1]);
		}
		right--;
		for (i = right; i > left; i--)
		{
			if (array[i-1] > array[i])
				swap(&array[i-1], &array[i]);
		}
		left++;
	}
}


// merge two sorted arrays
void merge(int *array, int left, int mid, int right)
{
	int len = right - left + 1;
	int *temp = (int*)malloc(len*sizeof(int));
	int index = 0;
	int i = left;
	int j = mid + 1;
	while (i <= mid && j<=right)
		temp[index++] = (array[i] <= array[j]) ? array[i++] : array[j++];
	while (i <= mid)
		temp[index++] = array[i++];
	while (j <= right)
		temp[index++] = array[j++];
	int k;
	for(k = 0; k < len; k++)
		array[left++] = temp[k];
	free(temp);
}

// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(nlogn)
// 最优时间复杂度 ---- O(nlogn)
// 平均时间复杂度 ---- O(nlogn)
// 所需辅助空间 ------ O(n)
// 稳定性 ------------ 稳定
void merge_sort_recursion(int *array, int left, int right)
{
	if (left == right)
		return;
	int mid = (left + right) / 2;
	merge_sort_recursion(array, left, mid);
	merge_sort_recursion(array, mid + 1, right);
	merge(array, left, mid, right);
}



//iteration version
void merge_sort_iteration(int *array, int len)
{
	printf("merge_sort_iteration\n");
	int left, mid, right, i;
	for (i = 1; i < len; i *= 2)
	{
		left = 0;
		while (left + i < len)
		{
			mid = left + i - 1;
			right = (mid + i) < len ? mid + i : len - 1;
			merge(array, left, mid, right);
			left = right + 1;
		}
	}
}


// 分类 ------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- 最坏情况为输入序列是降序排列的,此时时间复杂度O(n^2)
// 最优时间复杂度 ---- 最好情况为输入序列是升序排列的,此时时间复杂度O(n)
// 平均时间复杂度 ---- O(n^2)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 稳定
void insertion_sort(int *array, int n)
{
	printf("insertion_sort\n");
	if (n < 1)
	{
		printf("array size error\n");
		return;
	}
	int i, j;
	for (i = 1; i < n; i++)
	{
		int cur = array[i];
		j = i - 1;
		while(j >= 0 && array[j] > cur)
		{
			array[j+1] = array[j];
			j--;
		}
		array[j+1] = cur;
	}
}


// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(n^2)
// 最优时间复杂度 ---- O(nlogn)
// 平均时间复杂度 ---- O(n^2)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 稳定
void insertion_binary_search_sort(int *array, int n)
{
	printf("insertion_binary_search_sort\n");
	if (n < 1)
	{
		printf("array size error\n");
		return;
	}
	int i, j;
	for (i = 1; i < n; i++)
	{
		int cur = array[i];
		int left = 0;
		int right = i - 1;

		while (left <= right)
		{
			int mid = (left + right)/2;
			//printf("left: %d, right: %d, mid: %d\n", left, right, mid);
			if (array[mid] > cur)
				right = mid - 1;
			else
				left = mid + 1;
		}
		for (j = i - 1; j >= left; j--)
			array[j+1] = array[j];
		array[left] = cur;
	}
}



// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- 根据步长序列的不同而不同。已知最好的为O(n(logn)^2)
// 最优时间复杂度 ---- O(n)
// 平均时间复杂度 ---- 根据步长序列的不同而不同。
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 不稳定
void shell_sort(int *array, int n)
{
	printf("shell_sort\n");
	if (n < 1)
	{
		printf("array size error\n");
		return;
	}
	//generate initial 
	int h = 0;
	while (h <= n)
	{
		h = 3*h + 1;
	}
	while( h >= 1)
	{
		int i, j;
		for (i = h; i < n; i++)
		{
			int cur = array[i];
			j = i - h;
			while(j >= 0 && array[j] > cur)
			{
				array[j+h] = array[j];
				j -= h;
			}
			array[j+h] = cur;
		}
		h = (h-1)/3;
	}

}

// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(n^2)
// 最优时间复杂度 ---- O(n^2)
// 平均时间复杂度 ---- O(n^2)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 不稳定
void selection_sort(int *array, int n)
{
	printf("selection_sort\n");
	if (n < 1)
	{
		printf("array size error\n");
		return;
	}
	int i, j;
	for (i = 0; i < n; i++)
	{
		int min = i;
		for (j = i+1; j < n; j++)
		{
			if(array[j]<array[min])
				min = j;
		}
		if(min != i)
			swap(&array[min], &array[i]);
	}
}

void heapify(int *array, int i, int size)
{
	int left_child = 2 * i + 1;
	int right_child = 2 * i + 2;
	int max = i;
	if (left_child < size && array[left_child] > array[max])
		max = left_child;
	if (right_child < size && array[right_child] > array[max])
		max = right_child;

	if (max != i )
	{
		swap(&array[i], &array[max]);
		heapify(array, max, size);
	}
}


//build heap
int build_heap(int *array, int n)
{
	int heap_size = n;
	int i;
	for (i = heap_size/2 - 1; i >= 0; i--)
		heapify(array, i, heap_size);
	return heap_size;
}

// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(nlogn)
// 最优时间复杂度 ---- O(nlogn)
// 平均时间复杂度 ---- O(nlogn)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 不稳定
void heap_sort(int *array, int n)
{
	printf("heap_sort\n");
	if (n < 1)
	{
		printf("array size error\n");
		return;
	}
	int heap_size = build_heap(array, n);

	while(heap_size > 1)
	{
		swap(&array[0], &array[--heap_size]);
		heapify(array, 0, heap_size);
	}
}



// util function for quick sort
int partition(int *array, int left, int right)
{
	int pivot = array[right];
	int tail = left - 1;
	int i;
	for (i = left; i < right; i++)
	{
		if (array[i] <= pivot)
			swap(&array[i], &array[++tail]);
	}
	swap(&array[right], &array[tail + 1]);

	return tail + 1;
}

// 分类 ------------ 内部比较排序
// 数据结构 --------- 数组
// 最差时间复杂度 ---- 每次选取的基准都是最大（或最小）的元素，导致每次只划分出了一个分区，需要进行n-1次划分才能结束递归，时间复杂度为O(n^2)
// 最优时间复杂度 ---- 每次选取的基准都是中位数，这样每次都均匀的划分出两个分区，只需要logn次划分就能结束递归，时间复杂度为O(nlogn)
// 平均时间复杂度 ---- O(nlogn)
// 所需辅助空间 ------ 主要是递归造成的栈空间的使用(用来保存left和right等局部变量)，取决于递归树的深度，一般为O(logn)，最差为O(n)       
// 稳定性 ---------- 不稳定
void quick_sort(int *array, int left, int right)
{
	if (left >= right)
		return;
	int pivot = partition(array, left, right);
	quick_sort(array, left, pivot - 1);
	quick_sort(array, pivot + 1, right);
}


// 分类 ------------ 内部非比较排序
// 数据结构 --------- 数组
// 最差时间复杂度 ---- O(n + k)
// 最优时间复杂度 ---- O(n + k)
// 平均时间复杂度 ---- O(n + k)
// 所需辅助空间 ------ O(n + k)
// 稳定性 ----------- 稳定
void counting_sort(int *array, int n)
{
	printf("counting_sort\n");
	if (n < 1)
	{
		printf("array size error\n");
		return;
	}

	int i;
	for(i = 0; i < MAX; i++)
	{
		c[i] = 0;
	}

	for(i = 0; i < n; i++)
	{
		c[array[i]] ++;
	}

	for(i = 1; i < MAX; i++)
	{
		c[i] = c[i] + c[i-1];
	}

	int *temp = (int*) malloc(n*sizeof(int));

	for (i = n - 1; i >= 0; i--)
	{
		temp[--c[array[i]]] = array[i];
	}


	for(i = 0; i < n; i++)
	{
		array[i] = temp[i];
	}

	free(temp);

}



void lsd_radix_sort(int *array, int n)
{

}

void bucket_sort(int *array, int n)
{
	
}

// print array
void print_array(int *array, int n)
{
	int i;
	for(i=0;i<n;i++)
		printf("%d ",array[i]);
	printf("\n");
}



int main()
{
	// generate a random int array.
	int n = 30;
	int *b = generate_random_array(n, MAX);
	int* a = malloc(n*sizeof(int));
	print_array(b, n);

	// sort func ptrs:
	sort_func funcs[] = {bubble_sort, 
						cocktail_sort, 
						selection_sort, 
						insertion_sort, 
						insertion_binary_search_sort, 
						shell_sort, 
						merge_sort_iteration, 
						heap_sort,
						counting_sort};

	int size = sizeof(funcs) / sizeof(sort_func);

	sort_func_div funcs_div[] = {merge_sort_recursion,
								quick_sort};
	char* func_div_names[] = {"merge_sort_recursion",
							"quick_sort"};
	int size_div = sizeof(funcs_div) / sizeof(sort_func_div);

	int i;
	for(i = 0; i < size; i++)
	{
		memcpy(a, b, n*sizeof(int));
		funcs[i](a, n);
		print_array(a, n);
	}

	for(i = 0; i < size_div; i++)
	{
		memcpy(a, b, n*sizeof(int));
		funcs_div[i](a, 0, n - 1);
		printf("%s\n", func_div_names[i]);
		print_array(a, n);
	}


	free(a);
	free(b);


	return 0;
}
