#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <limits>
#include<conio.h>

#define MAXN 10000
#define MAX_LEN 256

#define MEMORY_ALLOCATION_ERROR -1

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
		if (prompt != "")
			std::cout << "请输入" << prompt << "[范围" << minNum << "-" << maxNum << "]:";
		std::cin >> num;
		if (std::cin.fail() || static_cast<int>(num) != num) {
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


/*create the HFNode class to create the HFTree*/
template<typename T, typename E>
struct HFNode {
	T key;
	E data;
	int left, right, parent;
	HFNode(){ key = 0; data = 0; left = right = parent = -1; }
};


/*create the Ranch class to create the HFTree*/
template<typename T, typename E>
class HFTree {
private:
	HFNode<T, E>* root,*elem;
	int N;
	HFNode<T, E>* elemList;
public:
	HFTree();
	void createHFTree();
	int calulateTotalMoney();
	void outputEachStep(HFNode<T, E>* node);
	HFNode<T, E>* getRoot(){ return root; }
};

/*
 * Function Name:	Ranch
 * Function:		the constructor of Ranch
 * Input Parameters:void
 * Return Value:	void
 * Notes:			Class external implementation of member functions
 */
template<typename T, typename E> 
HFTree<T, E>::HFTree() {
	root = NULL;
	/*input the number of timber*/
	N = inputInteger<int>(1, MAXN, "要修理的牧场的木头的数量");
	
	/*input the length of each timber*/
	int count = 0;
	elem = new(std::nothrow) HFNode<T, E>[N];
	elemList = new(std::nothrow) HFNode<T, E>[2 * N - 1];
	if (elemList == NULL|| elem == NULL) {
		std::cerr << "Error: Memory allocation error!" << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}

	std::cout<<std::endl<< ">>> 请依次输入"<<N<<"快木头的长度" << std::endl;
	while (count < N) {
		char temp[64];
		sprintf(temp, "请输入第%d块木头的长度", count + 1);
		elem[count].key = inputInteger<int>(1, MAX_LEN, temp);
		elem[count].data = elem[count].key;
		count++;
	}
}


/*
 * Function Name:	createHFTree
 * Function:		make the element list and create the HFTree
 * Input Parameters:void
 * Return Value:	void
 * Notes:			Class external implementation of member functions
 */
template<typename T, typename E>
void HFTree<T, E>::createHFTree() {
	int min1, min2;
	int index1, index2;
	/*initialize the elemList*/
	for (int i = 0; i < N; i++) {
		elemList[i] = elem[i];
	}
	for (int i = N; i < 2 * N - 1; i++) {
		elemList[i].key = 0;
		elemList[i].data = 0;
		elemList[i].left = elemList[i].right = elemList[i].parent = -1;
	}
	/*create the HFTree*/
	for (int i = N; i < 2 * N - 1; i++) {
		min1 = min2 = MAX_LEN;
		index1 = index2 = -1;
		/*find the two smallest elements key and index in the elemList*/
		for (int j = 0; j < i; j++) {
			if (elemList[j].parent == -1 && elemList[j].key < min1 && elemList[j].key>0) {
				min2 = min1;
				index2 = index1;
				min1 = elemList[j].key;
				index1 = j;
			}
			else if (elemList[j].parent == -1 && elemList[j].key < min2 && elemList[j].key>0) {
				min2 = elemList[j].key;
				index2 = j;
			}
		}
		/*set the parent of the two smallest elements*/
		elemList[index1].parent = elemList[index2].parent = i;
		elemList[i].left =  index1;
		elemList[i].right = index2;
		elemList[i].key = elemList[index1].key + elemList[index2].key;
		elemList[i].data = elemList[index1].data + elemList[index2].data;
	}
	root = elemList + (2 * N - 2);
}

/*
 * Function Name:	calulateTotalMoney
 * Function:		calculate the total money of repairing the ranch
 * Input Parameters:void
 * Return Value:	int
 * Notes:			Class external implementation of member functions
 */
template<typename T, typename E>
int HFTree<T, E>::calulateTotalMoney() {
	int totalMoney = 0;
	for (int i = N; i < 2 * N - 1; i++) {
		totalMoney += elemList[i].key;
	}
	return totalMoney;
}


/*
 * Function Name:	outputEachStep
 * Function:		output the each step of repairing the ranch
 * Input Parameters:void
 * Return Value:	void
 * Notes:			Class external implementation of member functions
 */
template<typename T, typename E>
void HFTree<T, E>::outputEachStep(HFNode<T, E> *node) {
	static int step = 1;
	if (step == 1) {
		std::cout << std::endl;
		std::cout<<">>> 修理牧场的最小花费为:"<<calulateTotalMoney()<<"元"<<std::endl << std::endl;
		std::cout << ">>> 修理牧场的过程如下:" << std::endl;
		std::cout << ">>> 木头的总长度为 " << root->key << std::endl;
	}
	if ((node->left == -1 && node  ->right == -1))
		return;
	/*output the current step*/
	std::cout << ">>> 第" << step << "步:";
	std::cout<<"将长度为 "<<node->key<<" 的木头分割成长度为 "<<
		elemList[node->left].key<<" 和 "<<elemList[node->right].key<<" 的两块,本次切割花费为 "<<node->key<<" 元"<<std::endl;
	step++;
	outputEachStep(elemList + node->left);
	outputEachStep(elemList + node->right);
}



/*
 * Function Name:	outputStart
 * Function:		output the start of the program
 * Input Parameters:void
 * Return Value:	void
 */
void outputStart() {
	std::cout << "+---------------------+" << std::endl;
	std::cout << "|       修理牧场      |" << std::endl;
	std::cout << "| Repairing the ranch |" << std::endl;
	std::cout << "+---------------------+" << std::endl << std::endl;

	std::cout << ">>> 输入格式要求:" << std::endl;
	std::cout << "[1] 第一行输入正整数N[整数范围1-" << MAXN << "], 表示要将木头锯成N块" << std::endl;
	std::cout << "[2] 之后输入N个整数[整数范围1-" << MAX_LEN << "],表示每块木头的长度,中间用空格隔开" << std::endl << std::endl;
}

/*
 * Function Name:	main
 * Function:		Main function of the program
 * Return Value:    0
 */
int main() {
	outputStart();
	HFTree<int, int> ranch;
	ranch.createHFTree();
	ranch.outputEachStep(ranch.getRoot());
	/*wait for user input to quit*/
	std::cout << "Press Enter to Quit" << std::endl;
	while (_getch() != '\r')
		continue;
	return 0;
}