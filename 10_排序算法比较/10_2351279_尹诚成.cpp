#include <iostream>
#include <conio.h>
#include <time.h>
#include <random>
#include <iomanip>
#include <chrono>
#define MEMORY_ALLOCATION_ERROR -1
typedef void (*SortFunction)(int*, int);

struct SortOption {
	SortFunction sortFunc;
	const char *name;
};

unsigned int compareCount = 0;

/*
 * Function Name:   inputInteger
 * Function:        input an integer within a range
 * Input Parameters:T minNum
 *                  T maxNum
 *                  const char* prompt
 * Return Value:    int
 */
template<typename T>
int inputInteger(T minNum, T maxNum, const char* prompt = "") {
	double num;
	while (true) {
			std::cout << "请输入" << prompt << "[范围" << minNum << "-" << maxNum << "]:";
		std::cin >> num;
		if (std::cin.fail()||static_cast<T>(num)!= num) {
			std::cout << "输入不是整数,请重新输入!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (num < minNum || num > maxNum) {
			std::cout << "输入值超出范围[" << minNum << "-" << maxNum << "],请重新输入!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
			return static_cast<int>(num);
	}
}


/*
 * Function Name:   makeChoice
 * Function:        Output a menu and get the user's choice
 * Input Parameters:const char* prompt
 * Return Value:    the user's choice
 */
int makeChoice(const char* prompt)
{
	std::cout << prompt;
	while (true) {
		char choice = _getch();;
		if (choice == 0 || choice == 32)
			choice = _getch();
		if ('0' <= choice && choice <= '8') {
			std::cout << "[" << choice - '0' << "] " << std::endl;
			return choice - '0';
		}
	}
}

/*
 * Function Name:    mySwap
 * Function:         Swap function
 * Input Parameters: Type& a
 *                   Type& b
 * Return Value:     void
 */
template <typename T>
void mySwap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

/*
 * Function Name:    bubbleSort
 * Function:         Bubble sort
 * Input Parameters: T arr[]
 *                   int n
 * Return Value:     void
 */
template <typename T>
void bubbleSort(T arr[], int n)
{
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++) {
			compareCount++;
			if (arr[j] > arr[j + 1])
				mySwap(arr[j], arr[j + 1]);
		}
}

/*
 * Function Name:	selectionSort
 * Function:        Selection sort
 * Input Parameters:T arr[]
 *                  int n
 * Return Value:    void
 */
template <typename T>
void selectionSort(T arr[], int n) {
	for (int i = 0; i < n-1; i++) {
		int k = i;
		for (int j = i + 1; j < n; j++) {
			compareCount++;
			if (arr[j] < arr[k]) {
				k = j;	
			}
		}
		if (k != i) {
			mySwap(arr[i], arr[k]);
		}
	}
}

/*
 * Function Name:   insertionSort
 * Function:        Insertion sort 
 * Input Parameters:T arr[]
 *                  int n
 * Return Value:    void
 */
template <typename T>
void insertionSort(T arr[], int n) {
	for (int i = 1; i < n; i++) {
		T temp = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > temp) {
			compareCount++;
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;
	}
}

/*
 * Function Name:	shellSort
 * Function:		Shell sort
 * Input Parameters:T arr[]
 *					int n
 * Return Value:	void
 */
template <typename T>
void shellSort(T arr[], int n) {
	int i, j, gap;
	for (gap = n / 2; gap > 0; gap /= 2) {
		for (i = gap; i < n; i++) {
			T temp = arr[i];
			for (j = i - gap; j >= 0 && arr[j] > temp; j -= gap) {
				compareCount++;
				arr[j + gap] = arr[j];
			}
			arr[j + gap] = temp;
		}
	}
}

/*
 * Function Name:	partition
 * Function:		find the pivot position and partition the array
 * Input Parameters:T arr[]
 *                  int low
 *					int high
 * Return Value:	int
 */
template <typename T>
int partition(T arr[], int low, int high) {
	int pivotpos = low;
	T pivot = arr[low];
	for (int i = low + 1; i <= high; i++) {
		compareCount++;
		if (arr[i] < pivot) {
			pivotpos++;
			if (pivotpos != i) {
				mySwap(arr[i], arr[pivotpos]);
			}
		}
	}
	arr[low] = arr[pivotpos];
	arr[pivotpos] = pivot;
	return pivotpos;
}

/*
 * Function Name:	quickSort
 * Function:		Quick sort
 * Input Parameters:T arr[]
 *                  int low	
 *                  int high
 * Return Value:	void
 */
template <typename T>
void quickSort(T arr[], int low, int high) {
	if (low < high) {
		int pivotpos = partition(arr, low, high);
		quickSort(arr, low, pivotpos - 1);
		quickSort(arr, pivotpos + 1, high);
	}
}

/*
 * Function Name:	quickSort
 * Function:		Quick sort
 * Input Parameters:T arr[]
 *					int n
 * Return Value:	void
 */
template <typename T>
void quickSort(T arr[], int n) {
	quickSort(arr, 0, n - 1);
}


/*
 * Function Name:	merge
 * Function:		merge two sorted subarrays
 * Input Parameters:T arr[]
 *                  int left
 *                  int mid
 *                  int right
 * Return Value:	void
 */
template <typename T>
void merge(T arr[], int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;
	/* create temp arrays */
	T* arr1 = new(std::nothrow) T[n1];
	if (arr1 == NULL) {
		std::cerr << "Error: Memory allocation failed." << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	T* arr2 = new(std::nothrow) T[n2];
	if (arr2 == NULL) {
		std::cerr << "Error: Memory allocation failed." << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	for (int i = 0; i < n1; i++)
		arr1[i] = arr[left + i];
	for (int j = 0; j < n2; j++)
		arr2[j] = arr[mid + 1 + j];

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		compareCount++;
		if (arr1[i] <= arr2[j])
			arr[k++] = arr1[i++];
		else
			arr[k++] = arr2[j++];
	}
	while (i < n1) {
		compareCount++;
		arr[k++] = arr1[i++];
	}
	while (j < n2) {
		compareCount++;
		arr[k++] = arr2[j++];
	}

	delete[] arr1;
	delete[] arr2;
}

/*
 * Function Name:	mergeSort
 * Function:		Merge sort
 * Input Parameters:T arr[]
 *					int left
 *					int right
 * Return Value:	void
 */
template <typename T>
void mergeSort(T arr[], int left, int right) {
	if (left < right) {
		/*avoid integer overflow*/
		int mid = left + (right - left) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

 /*
  * Function Name:	mergeSort
  * Function:		Merge sort
  * Input Parameters:T arr[]
  *					int n
  * Return Value:	void
  */
template <typename T>
void mergeSort(T arr[], int n) {
	mergeSort(arr, 0, n - 1);
}

/*
 * Function Name:	heapSiftDown
 * Function:		heap sift down
 * Input Parameters:T arr[]
 *                  int start
 *                  int end
 * Return Value:	void
 */
template<typename T>
void heapSiftDown(T arr[], int start, int end) {
	int i = start, j = 2 * i + 1;
	T temp = arr[i];
	while (j <= end) {
		compareCount++;
		if (j < end && arr[j] < arr[j + 1])
			j++;
		if (temp >= arr[j]) {
			break;
		}
		else {
			arr[i] = arr[j];
			i = j;
			j = 2 * i + 1;
		}
	}
	arr[i] = temp;
}

/*
 * Function Name:	heapSort
 * Function:		Heap sort
 * Input Parameters:T arr[]
 *                  int n
 * Return Value:	void
 */
template<typename T>
void heapSort(T arr[], int n) {
	for (int i = (n - 2) / 2; i >= 0; i--) {
		heapSiftDown(arr, i, n - 1);
	}
	for (int i = n - 1; i >= 0; i--) {
		mySwap(arr[0], arr[i]);
		heapSiftDown(arr, 0, i - 1);
	}
}

/*
 * Function Name:	getMaxValue
 * Function:		get the maximum value in the array
 * Input Parameters:T arr[]
 *                  int n
 * Return Value:	T
 */
template<typename T>
T getMaxValue(T arr[], int n) {
	T result = arr[0];
	for (int i = 0; i < n; i++) {
		compareCount++;
		if (arr[i] > result) {
			result = arr[i];
		}
	}
	return result;
}

/*
 * Function Name:	countSort
 * Function:		count sort
 * Input Parameters:T arr[]
 *                  int n
 *                  int exp
 * Return Value:	void
 */
template<typename T>
void countSort(T arr[], int n, int exp) {
	T *output = new(std::nothrow) T[n];
	if (output == NULL) {
		std::cerr << "Error: Memory allocation failed." << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	int count[10] = { 0 };
	for (int i = 0; i < n; i++){
		count[(arr[i] / exp) % 10]++;
	}
	for (int i = 1; i < 10; i++) {
		count[i] += count[i - 1];
	}
	for (int i = n - 1; i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}
	for (int i = 0; i < n; i++) {
		arr[i] = output[i];
	}
	delete[] output;
}

/*
 * Function Name:	radixSort
 * Function:		radix sort
 * Input Parameters:T arr[]
 *                  int n	
 * Return Value:	void
 */
template<typename T>
void radixSort(T arr[], int n) {
	T maxVal = getMaxValue(arr, n);
	for (int exp = 1; maxVal / exp > 0; exp *= 10) {
		countSort(arr, n, exp);
	}
}


/*define the sort options*/
SortOption sortOptions[] = {
	{bubbleSort,	"冒泡排序"},
	{selectionSort,	"选择排序"},
	{insertionSort,	"插入排序"},
	{shellSort,		"希尔排序"},
	{quickSort,		"快速排序"},
	{heapSort,		"堆 排 序"},
	{mergeSort,		"归并排序"},
	{radixSort,		"基数排序"}
};


/*
 * Function Name:	choiceSort
 * Function:		sort the array using the selected sort function
 * Input Parameters:SortFunction sortFunc
 *                  T arr[]
 *                  int n
 *                  int choice
 * Return Value:	void
 */
template<typename T>
void choiceSort(SortFunction sortFunc, T arr[], int n, int choice) {
	compareCount = 0;

	std::cout << std::endl << ">>> 排序算法:" << sortOptions[choice - 1].name << std::endl;

	int* copyArr = new(std::nothrow) int[n];
	if (copyArr == NULL) {
		std::cerr << "Error: Memory allocation failed." << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}

	std::copy(arr, arr + n, copyArr);

	auto start = std::chrono::high_resolution_clock::now();

	sortFunc(copyArr, n);

	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> duration = end - start;
	
	std::cout << ">>> 比较次数:" << compareCount << std::endl << std::endl;

	std::cout << ">>> 函数运行时间: " <<std::fixed<<std::setprecision(6) << duration.count() / 1000 << "s" << std::endl;

	//std::cout<<"排序结果:"<<std::endl;
	//for (int i = 0; i < n; i++) {
	//	std::cout << copyArr[i] << " ";
	//}
	//std::cout << std::endl;
	delete[] copyArr;
}


int main() {
	/* Generate random number seed */
	srand((unsigned int)(time(0)));

	std::cout << "+----------------------------------------+" << std::endl;
	std::cout << "|           八种排序算法的比较           |" << std::endl;
	std::cout << "| Comparison of eight sorting algorithms |" << std::endl;
	std::cout << "+----------------------------------------+" << std::endl << std::endl;

	std::cout<<">>> 排序算法:"<<std::endl;
	for (int i = 0; i < 8; i++) {
		std::cout <<"    ["<< i + 1 << "] " << sortOptions[i].name << std::endl;
	}
	std::cout << "    [0] 退出程序" << std::endl << std::endl;

	int intNum = inputInteger(1, INT_MAX, "随机生成的整数数量");
	int* arr = new(std::nothrow) int[intNum];
	if (arr == NULL) {
		std::cerr << "Error: Memory allocation failed." << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	for (int i = 0; i < intNum; i++) {
		arr[i] = rand();
	}

	std::cout << std::endl << ">>> 随机数生成成功（随机数数量: " << intNum << "）" << std::endl << std::endl;

	while (true) {
		int choice = makeChoice(">>> 请选择排序算法: ");
		if (choice == 0) 
			return 0;
		else
			choiceSort(sortOptions[choice - 1].sortFunc, arr, intNum, choice);
	}
	return 0;
}