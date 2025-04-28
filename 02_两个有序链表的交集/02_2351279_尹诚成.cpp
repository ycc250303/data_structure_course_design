#include<iostream>
#include<conio.h>
#define MEMORY_ALLOCATION_ERROR -1
#define END_NUM -1

template<typename T>
struct LinkNode
{
	T data;
	LinkNode<T>* link;
	LinkNode(LinkNode<T>* ptr = NULL) :data(T()), link(ptr) {}
	LinkNode(const T& item, LinkNode<T>* ptr = NULL) { data = item; link = ptr; }
};

template<typename T>
class List
{
private:
	LinkNode<T>* first;
	LinkNode<T>* last;
public:
	List();
	List(const T& item);
	List(List<T>& L);
	~List();
	void makeEmpty();
	int getLength()const;
	LinkNode<T>* getHead()const;
	LinkNode<T>* getTail()const;
	LinkNode<T>* search(T item)const;
	LinkNode<T>* locate(int i)const;
	int findData(T& item)const;
	bool getData(int i, T& item);
	void setData(int i, T& item);
	bool insert(int i,  T& item);
	bool remove(int i, T& item);
	bool isEmpty()const;
	void output()const;
};

/*
 * Function Name:    List
 * Function:         Constructed function
 * Notes:            Class external implementation of member functions
 */
template<typename T>
List<T>::List()
{
	first = new(std::nothrow) LinkNode<T>;
	if (first == NULL) {
		std::cerr << "执行错误:内存分配失败！" << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	last = first;
}

/*
 * Function Name:    List
 * Function:         Constructed function
 * Input Parameters: const T& item
 * Notes:            Class external implementation of member functions
 */
template<typename T>
List<T>::List(const T& item)
{
	first = new(std::nothrow) LinkNode<T>(item);
	if (first == NULL) {
		std::cerr << "执行错误:内存分配失败！" << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	last = first;
}

/*
 * Function Name:    List
 * Function:         Constructed function
 * Input Parameters: List<T>& L
 * Notes:            Class external implementation of member functions
 */
template<typename T>
List<T>::List(List<T>& L)
{
	first = new(std::nothrow) LinkNode<T>;
	if (first == NULL) {
		std::cerr << "执行错误:内存分配失败！" << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	last = first;
	LinkNode<T>* srcptr = L.first->link;
	LinkNode<T>* dstptr = first;
	while (srcptr != NULL)
	{
		dstptr->link = new(std::nothrow) LinkNode<T>(srcptr->data);
		if (dstptr->link == NULL) {
			std::cerr << "执行错误:内存分配失败！" << std::endl;
			exit(MEMORY_ALLOCATION_ERROR);
		}
		srcptr = srcptr->link;
		dstptr = dstptr->link;
	}
	last = dstptr;
	last->link = NULL;
}

/*
 * Function Name:    ~MyList
 * Function:         Destructor
 * Notes:            Class external implementation of member functions
 */
template<typename T>
List<T>::~List()
{
	makeEmpty();
}

/*
 * Function Name:    makeEmpty
 * Function:         Set the linked list to an empty list
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template<typename T>
void List<T>::makeEmpty()
{
	LinkNode<T>* current;
	while (first->link != NULL)
	{
		current = first->link;
		first->link = current->link;
		delete current;
	}
}

/*
 * Function Name:    getLength
 * Function:         Calculate the length of a singly linked list with an appended head node
 * Input Parameters: void
 * Return Value:     the length of a singly linked list with an appended head node
 * Notes:            Class external implementation of member functions
 */
template<typename T>
int List<T>::getLength()const
{
	int length = 0;
	LinkNode<T>* current = first->link;
	while (current != NULL)
	{
		length++;
		current = current->link;
	}
	return length;
}

/*
 * Function Name:    locate
 * Function:         Return the address of the ith element in the list, if i < 0
 *                   or exceeds the number of nodes in the list, return NULL
 * Input Parameters: int i
 * Return Value:     the address of the ith element / NULL
 * Notes:            Class external implementation of member functions
 */
template<typename T>
LinkNode<T>* List<T>::locate(int i) const
{
	if (i < 0)
		return NULL;
	LinkNode<T>* current = first;
	int k = 0;
	while (current != NULL && k < i) {
		current = current->link;
		k++;
	}
	return current;
}

/*
 * Function Name:    insert
 * Function:         Insert the new element after the ith node in the linked list
 * Input Parameters: int i
 *                   Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template<typename T>
bool List<T>::insert(int i, T& item)
{
	LinkNode<T>* current = locate(i);
	if (current == NULL)
		return false;
	LinkNode<T>* newNode = new(std::nothrow) LinkNode<T>(item);
	if (newNode == NULL) {
		std::cerr << "执行错误:内存分配失败！" << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	newNode->link = current->link;
	current->link = newNode;
	return true;
}

/*
 * Function Name:    getHead
 * Function:         Return the address of the appended head node
 * Input Parameters: void
 * Return Value:     the address of the appended head node
 * Notes:            Class external implementation of member functions
 */
template<typename T>
LinkNode<T>* List<T>::getHead()const
{
	return first;
}

/*
 * Function Name:    getTail
 * Function:         Return the address of the tail node of a singly linked list with an appended head node
 * Input Parameters: void
 * Return Value:     the address of the tail node
 * Notes:            Class external implementation of member functions
 */
template<typename T>
LinkNode<T>* List<T>::getTail()const
{
	return last;
}


/*
 * Function Name:    isEmpty
 * Function:         Check if the linked list is empty
 * Input Parameters: void
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template<typename T>
bool List<T>::isEmpty()const
{
	return first->link == NULL;
}

/*
 * Function Name:    output
 * Function:         Output all data in the singly linked list in logical order
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template<typename T>
void List<T>::output()const
{
	LinkNode<T>* current = first->link;
	while (current != NULL)
	{
		if (current->link != NULL)
			std::cout << current->data << " ";
		else
			std::cout << current->data;
		current = current->link;
	}
}

/*
 * Function Name:    check_list_is_ordered
 * Function:         check if the list is ordered
 * Input Parameters: List<int>& list
 * Return Value:     true: the list is ordered
 *					 false: the list is not ordered
 */
bool check_list_is_ordered(List<int>& list)
{
	if (list.isEmpty())
		return true;
	LinkNode<int>* current = list.getHead()->link;
	int previous = current->data;
	while (current != NULL)
	{
		if (current->data < previous)
			return false;
		previous = current->data;
		current = current->link;
	}
	return true;
}



/*
 * Function Name:    input_list
 * Function:         input a ordered list
 * Input Parameters: List<int>& list
 *					 int maxNum
 *					 int minNum
 * Return Value:     void
 */
void input_list(List<int>& list,int maxNum,int minNum)
{
	double num;
	std::cout<<"请输入链表的元素,输入范围["<<minNum<<"-"<<maxNum<<"]"<<",输入"<<END_NUM<<"结束输入:"<<std::endl;
	while (true)
	{
		std::cin >> num;
		if (num == -1)
			break;
		else if (std::cin.fail()||static_cast<int>(num)!=num)//check if input is not an integer
		{
			std::cerr << "输入不是整数，请重新输入!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			list.makeEmpty();
			continue;
		}
		else if (num<minNum  || num>maxNum)//check if input is not a positive integer
		{
			std::cerr << "输入超出范围[" << minNum << "-" << maxNum << "],请重新输入!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			list.makeEmpty();
			continue;
		}
		int item = static_cast<int>(num);
		list.insert(list.getLength(), item);
		if (!check_list_is_ordered(list))//check if the list is ordered
		{
			std::cerr << "输入的序列不是非降序序列,请重新输入!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			list.makeEmpty();
			continue;
		}
	}
}


/*
 * Function Name:	find_the_intersection_of_two_ordered_lists
 * Function:		find the intersection of two ordered linked lists
 * Input Parameters:List<int>& list1
 *					List<int>& list2
 *					List<int>& intersection
 * Return Value:	void
 */
void find_the_intersection_of_two_ordered_lists(List<int>& list1, List<int>& list2,List<int>& intersection)
{
	LinkNode<int>* current1 = list1.getHead()->link;
	LinkNode<int>* current2 = list2.getHead()->link;
	while (current1 != NULL && current2 != NULL)
	{
		if (current1->data == current2->data)
		{
			intersection.insert(intersection.getLength(), current1->data);
			current1 = current1->link;
			current2 = current2->link;
		}
		else if (current1->data < current2->data)
			current1 = current1->link;
		else
			current2 = current2->link;
	}
}

/*
 * Function Name:	two_ordered_lists_intersection
 * Function:		build two ordered linked lists and find their intersection
 * Input Parameters:void
 * Return Value:	void
 */
void two_ordered_lists_intersection()
{
	std::cout << "+--------------------------------------------+" << std::endl;
	std::cout << "|            两个有序链表的交集              |" << std::endl;
	std::cout << "|  Intersection of Two Ordered Linked Lists  |" << std::endl;
	std::cout << "+--------------------------------------------+" << std::endl << std::endl;
	std::cout << ">>> 请输入两个有序链表" << std::endl;
	std::cout << "[输入说明]  输入分2行,分别在每行给出由若干个正整数构成的非降序序列" << std::endl;
	std::cout << "            用"<<END_NUM<<"表示序列的结尾("<<END_NUM<<"不属于这个序列),数字用空格间隔" << std::endl;
	List<int> list1, list2, intersection;
	input_list(list1,INT_MAX,1);
	input_list(list2,INT_MAX,1);
	LinkNode<int>* current1 = list1.getHead()->link;
	LinkNode<int>* current2 = list2.getHead()->link;
	//std::cout << ">>> 两个链表的交集为:" << std::endl;
	find_the_intersection_of_two_ordered_lists(list1, list2, intersection);
	if (intersection.isEmpty())
		std::cout << "NULL" << std::endl;
	else {
		std::cout << ">>> 两个有序链表的交集为:" << std::endl;
		intersection.output();
	}
		
	std::cout << std::endl;
}


/*
 * Function Name:
 * Function:
 * Input Parameters:
 * Return Value:
 */
int main()
{
	two_ordered_lists_intersection();
	/*wait for user input to quit*/
	std::cout << "Press Enter to Quit" << std::endl;
	while (_getch() != '\r')
		continue;
	return 0;
}