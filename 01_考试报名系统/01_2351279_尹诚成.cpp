#include <iostream>
#include <iomanip>
#include <cstring>
#include <iomanip>
#include <stdbool.h>
#include<conio.h>

#define MAX_SIZE 64
#define MEMORY_ALLOCATION_ERROR -1

struct ExamerIinfo
{
	char no[MAX_SIZE] = { 0 };//����
	char name[MAX_SIZE] = { 0 };//����
	bool sex = true;//�Ա�
	int age = 0;//����
	char category[MAX_SIZE] = { 0 };//��������
};

/*
 * Function Name:	operator <<
 * Function:		output examer_info to console
 * Input Parameters:std::ostream& out, const examer_info& examerinfo
 * Return Value:	out
 */
std::ostream& operator << (std::ostream& out, const ExamerIinfo& examerinfo)
{
	out << std::setiosflags(std::ios::left)
		<< "| " << std::setw(12) << examerinfo.no
		<< " | " << std::setw(24) << examerinfo.name
		<< " | " << (examerinfo.sex ? " �� " : " Ů ")
		<< " |  " << std::setw(3) << examerinfo.age
		<< " | " << std::setw(32) << examerinfo.category
		<< " |" << std::resetiosflags(std::ios::left);
	return out;
}


template<typename T>
struct LinkNode
{
	T data;
	LinkNode<T>* link;
	LinkNode(LinkNode<T>* ptr = NULL) { link = ptr; }
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
	bool insert(int i, T& item);
	bool remove(int i, T& item);
	bool isEmpty()const;
	void output()const;
	void addFront(T& item);
	void removeFront(T& item);
	List<T>& operator =(List<T>& L);
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
		std::cerr << "ִ�д���:�ڴ����ʧ�ܣ�" << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	last = first;
}

/*
 * Function Name:    List
 * Function:         Constructed function
 * Input Parameters: const Type& item
 * Notes:            Class external implementation of member functions
 */
template<typename T>
List<T>::List(const T& item)
{
	first = new(std::nothrow) LinkNode<T>(item);
	if (first == NULL) {
		std::cerr << "ִ�д���:�ڴ����ʧ�ܣ�" << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	last = first;
}

/*
 * Function Name:    List
 * Function:         Constructed function
 * Input Parameters: MyList<Type>& L
 * Notes:            Class external implementation of member functions
 */
template<typename T>
List<T>::List(List<T>& L)
{
	first = new(std::nothrow) LinkNode<T>;
	if (first == NULL) {
		std::cerr << "ִ�д���:�ڴ����ʧ�ܣ�" << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	last = first;
	LinkNode<T>* srcptr = L.first->link;
	LinkNode<T>* dstptr = first;
	while (srcptr != NULL)
	{
		dstptr->link = new(std::nothrow) LinkNode<T>(srcptr->data);
		if (dstptr->link == NULL) {
			std::cerr << "ִ�д���:�ڴ����ʧ�ܣ�" << std::endl;
			exit(MEMORY_ALLOCATION_ERROR);
		}
		srcptr = srcptr->link;
		dstptr = dstptr->link;
	}
	last = dstptr;
	last->link = NULL;
}

/*
 * Function Name:    ~List
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
 * Function Name:    search
 * Function:         Search for a node containing data x in the linked list, if the search is successful,
 *                   the function returns the address of that node, otherwise, it returns a NULL value
 * Input Parameters: Type item
 * Return Value:     the address of the node / NULL
 * Notes:            Class external implementation of member functions
 */
template<typename T>
LinkNode<T>* List<T>::search(T item)const
{
	LinkNode<T>* current = first->link;
	while (current != NULL)
	{
		if (current->data == item)
			break;
		else
			current = current->link;
	}
	return current;
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
 * Function Name:    findData
 * Function:         find the location of data item
 * Input Parameters: Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template<typename T>
int List<T>::findData(T& item)const
{
	int k = 1;
	LinkNode<T>* current = first->link;
	while (current != NULL)
	{
		if (current->data == item)
			return k;
		else
		{
			current = current->link;
			k++;
		}
	}
	return 0;
}

/*
 * Function Name:    getData
 * Function:         Return the value of the ith element in the linked list
 * Input Parameters: int i
 *                   Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template<typename T>
bool List<T>::getData(int i, T& item)
{
	if (i <= 0 || i > getLength())
		return false;
	LinkNode<T>* current = locate(i);
	if (current == NULL)
		return false;
	else
	{
		item = current->data;
		return true;
	}
}

/*
 * Function Name:    setData
 * Function:         Assign a value to the ith element in the linked list
 * Input Parameters: int i
 *                   Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template<typename T>
void List<T>::setData(int i, T& item)
{
	if (i <= 0 || i > getLength())
		return;
	LinkNode<T>* current = locate(i);
	if (current == NULL)
		return;
	else
		current->data = item;
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
		std::cerr << "ִ�д���:�ڴ����ʧ�ܣ�" << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	newNode->link = current->link;
	current->link = newNode;
	return true;
}

/*
 * Function Name:    remove
 * Function:         Remove the ith element from the linked list and return its value through a reference parameter
 * Input Parameters: int i
 *                   Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template<typename T>
bool List<T>::remove(int i, T& item)
{
	LinkNode<T>* current = locate(i - 1);
	if (current == NULL || current->link == NULL)
		return false;
	LinkNode<T>* del = current->link;
	current->link = del->link;
	item = del->data;
	delete del;
	return true;
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
		std::cout << current->data << std::endl;
		current = current->link;
	}
}

/*
 * Function Name:    addFront
 * Function:         Add a new element at the front of the linked list
 * Input Parameters: Type& item
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template<typename T>
void List<T>::addFront(T& item)
{
	LinkNode<T>* newNode = new(std::nothrow) LinkNode<T>(item);
	if (newNode == NULL) {
		std::cerr << "ִ�д���:�ڴ����ʧ�ܣ�" << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	newNode->link = first->link;
	first->link = newNode;
	if (last == first)
		last = newNode;
}

/*
 * Function Name:    removeFront
 * Function:         Remove the first element from the linked list and return its value through a reference parameter
 * Input Parameters: Type& item
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template<typename T>
void List<T>::removeFront(T& item)
{
	if (first->link != NULL) {
		LinkNode<T>* temp = first->link;
		first->link = temp->link;
		delete temp;
		if (first->link == NULL)
			last = first;
	}
}

/*
 * Function Name:    operator=
 * Function:         Overload operator =
 * Input Parameters: List<Type> L
 * Return Value:     *this
 * Notes:            Class external implementation of member functions
 */
template<typename T>
List<T>& List<T>::operator =(List<T>& L)
{
	if (this == &L)
		return *this;
	makeEmpty();
	LinkNode<T>* srcptr = L.first->link;
	LinkNode<T>* dstptr = first;
	while (srcptr != NULL)
	{
		LinkNode<T>* newNode = new(std::nothrow) LinkNode<T>(srcptr->data);
		if (newNode == NULL) {
			std::cerr << "ִ�д���:�ڴ����ʧ�ܣ�" << std::endl;
			exit(MEMORY_ALLOCATION_ERROR);
		}
		dstptr = dstptr->link;
		dstptr->link = newNode;
		srcptr = srcptr->link;
	}
	last = dstptr;
	return *this;
}


/*
 * Function Name:    truncateExamerInfo
 * Function:         truncate the string to the given length
 * Input Parameters: char* str
					 int length
 * Return Value:	 void
 */
void truncateExamerInfo(char* str, int length)
{
	if (static_cast<int>(strlen(str)) > length)
		str[length] = '\0';
}


 /*
  * Function Name:	  checkExamerNoValid
  * Function:		  check if the examer no is valid
  * Input Parameters: const char* no
  * Return Value:	  bool
  */
bool checkExamerNoValid(const char* no)
{
	while (*no != '\0')
	{
		if (!('0' <= *no && *no <= '9'))
			return false;
		no++;
	}
	return true;
}


 
 /*
  * Function Name:    checkExamerNoSame
  * Function:         check if the examer no is same
  * Input Parameters: List<examer_info>& examer_list
					  const char* no
  * Return Value:     true / false
  */
bool checkExamerNoSame(List<ExamerIinfo>& examer_list, const char* no)
{
	LinkNode<ExamerIinfo>* current = examer_list.getHead()->link;
	while (current != NULL)
	{
		if (strcmp(current->data.no, no) == 0)
			return true;
		current = current->link;
	}
	return false;
}


/*
 * Function Name:    checkListNotEmpty
 * Function:         check if the list is not empty
 * Input Parameters: List<examer_info>& examer_list
					 const char* prompt
 * Return Value:     true / false
 */
bool checkListNotEmpty(List<ExamerIinfo>& examer_list, const char* prompt)
{
	if (examer_list.isEmpty())
	{
		std::cerr << prompt << std::endl << std::endl;
		return false;
	}
	return true;
}

/*
 * Function Name:	 inputExamerInfo
 * Function:		 input examer info
 * Input Parameters: List<examer_info>& examer_list
 * Return Value:	 examer_info
 */
ExamerIinfo inputExamerInfo(List<ExamerIinfo>& examer_list)
{
	while (true)
	{
		// ���뿼��
		ExamerIinfo new_examer;
		std::cin >> new_examer.no;
		//�ضϲ���鿼�źϷ���
		truncateExamerInfo(new_examer.no, 12);
		if (!checkExamerNoValid(new_examer.no))
		{
			std::cerr << ">>> ����Ŀ��Ų��Ϸ�������������!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}
		else if (checkExamerNoSame(examer_list, new_examer.no))
		{
			std::cerr << ">>> ����Ŀ����Ѵ��ڣ�����������!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}

		// ��������
		std::cin >> new_examer.name;
		truncateExamerInfo(new_examer.name, 24);

		// �����Ա�
		char sex[MAX_SIZE] = { 0 };
		std::cin >> sex;
		//����Ա�Ϸ���
		if (!strcmp(sex, "��"))
			new_examer.sex = true;
		else if (!strcmp(sex, "Ů"))
			new_examer.sex = false;
		else
		{
			std::cerr << ">>> ������Ա𲻺Ϸ�������������!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}
		//��������
		double tempAge;
		std::cin >> tempAge;
		if (std::cin.fail()|| tempAge < 1 || tempAge > 99||static_cast<int>(tempAge)!= tempAge)
		{
			std::cerr << ">>> ��������䲻�Ϸ�������������!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}
		new_examer.age = tempAge;

		//���뱨�����
		std::cin >> new_examer.category;
		truncateExamerInfo(new_examer.category, 32);

		return  new_examer;
	}
}


/*
 * Function Name:	 outputInputRequirement
 * Function:		 output input requirement
 * Input Parameters: const char* prompt
 * Return Value:	 void
 */
void outputInputRequirement(const char* prompt)
{
	std::cout << prompt << std::endl;
	std::cout << ">>> �����ʽ������ ���� �Ա� ���� �������(�м��ÿո����)" << std::endl;
	std::cout << "    �����ʽҪ��" << std::endl;
	std::cout << "    [��    ��] ������ 12 �������ַ���ɵ��ַ������������ֽ����ض�" << std::endl;
	std::cout << "    [��    ��] ������ 24 ��Ӣ���ַ��� 12 �������ַ���ɵ��ַ������������ֽ����ض�" << std::endl;
	std::cout << "    [��    ��] �� / Ů" << std::endl;
	std::cout << "    [��    ��] �� 1 �� 99 ��Χ�ڵ���������" << std::endl;
	std::cout << "    [�������] ������ 32 ��Ӣ���ַ��� 16 �������ַ���ɵ��ַ������������ֽ����ض�" << std::endl << std::endl;
}

/*
 * Function Name:	 outputExamerInfo
 * Function:		 output all examer info
 * Input Parameters: const List<examer_info>& examer_list
 * Return Value:	 void
 */
void outputExamerInfo(const List<ExamerIinfo>& examer_list)
{
	if (examer_list.isEmpty())
	{
		std::cout << "| �޿�����Ϣ                                                                               |" << std::endl;
		std::cout << "+--------------+--------------------------+------+------+----------------------------------+" << std::endl << std::endl;
		return;
	}
	for (int num = 0; num < examer_list.getLength(); num++)
	{
		LinkNode<ExamerIinfo>* temp_examer = examer_list.locate(num + 1);
		std::cout << temp_examer->data << std::endl;
		std::cout << "+--------------+--------------------------+------+------+----------------------------------+" << std::endl;
	}
	std::cout << std::endl;
}

/* 
 * Function Name:	outputExamerInfo
 * Function:		output one examer info
 * Input Parameters:const examer_info examer
 * Return Value:	void
 */
void outputExamerInfo(const ExamerIinfo examer)
{
	std::cout << examer << std::endl;
	std::cout << "+--------------+--------------------------+------+------+----------------------------------+" << std::endl << std::endl;
}


/*
 * Function Name:	outputMeterHeader
 * Function:		output meter header 
 * Input Parameters:const char* prompt
 * Return Value:	void
 */
void outputMeterHeader(const char* prompt)
{
	std::cout << std::endl << prompt << std::endl;
	std::cout << "+--------------+--------------------------+------+------+----------------------------------+" << std::endl;
	std::cout << "| ����         | ����                     | �Ա� | ���� | �������                         |" << std::endl;
	std::cout << "+--------------+--------------------------+------+------+----------------------------------+" << std::endl;
}

/*
 * Function Name:	statisticSex
 * Function:		statistic sex information
 * Input Parameters:List<examer_info>& examer_list
					int male_count
 * Return Value:	void
 */
void statisticSex(List<ExamerIinfo>& examer_list, int male_count)
{
	int female_count = static_cast<int>(examer_list.getLength()) - male_count;
	double male_ratio = male_count * 100 / static_cast<double>(examer_list.getLength());
	double female_ratio = female_count * 100 / static_cast<double>(examer_list.getLength());

	std::cout << ">>> �Ա�ͳ��" << std::endl;
	std::cout << "+------+------+---------------+" << std::endl;
	std::cout << "| �Ա� | ���� | ����(%)       |" << std::endl;
	std::cout << "+------+------+---------------+" << std::endl;
	if (male_count)
	{
		std::cout << "|  ��  | " << std::setiosflags(std::ios::left) << std::setw(4) << male_count <<
			" | " << std::setprecision(6) << std::setw(13) << male_ratio << " |" << std::endl;
		std::cout << "+------+------+---------------+" << std::endl << std::resetiosflags(std::ios::left);
	}
	if (female_count)
		std::cout << "|  Ů  | " << std::setiosflags(std::ios::left) << std::setw(4) << female_count <<
		" | " << std::setw(13) << std::setprecision(6) << female_ratio << " |" << std::endl;
	std::cout << "+------+------+---------------+" << std::endl << std::resetiosflags(std::ios::left);
	std::cout << std::endl;
}

/*
 * Function Name:	statisticAge
 * Function:		statistic age information
 * Input Parameters:List<examer_info>& examer_list
					int age_num[]
 * Return Value:	void
 */
void statisticAge(List<ExamerIinfo>& examer_list, int age_num[])
{
	double age_ratio[100] = { 0 };
	std::cout << ">>> ����ͳ��" << std::endl;
	std::cout << "+------+------+---------------+" << std::endl;
	std::cout << "| ���� | ���� | ����(%)       |" << std::endl;
	std::cout << "+------+------+---------------+" << std::endl;
	for (int i = 0; i < 100; i++)
	{
		if (age_num[i] != 0)
		{
			std::cout << "| " << std::setiosflags(std::ios::left) << std::setw(4) << i <<
				" | " << std::setw(4) << age_num[i] <<
				" | " << std::setprecision(6) << std::setw(13) << age_num[i] * 100 / static_cast<double>(examer_list.getLength()) << " |" << std::endl;
			std::cout << "+------+------+---------------+" << std::endl << std::resetiosflags(std::ios::left);
		}
	}
	std::cout << std::endl;
}


/*
 * Function Name:	buildExamerList
 * Function:		build examer list
 * Input Parameters:List<examer_info>& examer_list
					int examer_num
 * Return Value:	void
 */
void buildExamerList(List<ExamerIinfo>& examer_list, int examer_num)
{
	outputInputRequirement(">>> ������¼�뿼����Ϣ");
	for (int num = 0; num < examer_num; num++)
	{
		ExamerIinfo examer = inputExamerInfo(examer_list);
		examer_list.insert(num, examer);
	}
	std::cout << ">>> ������Ϣϵͳ������� [��������: " << examer_num << "]" << std::endl;
	outputMeterHeader(">>> ������Ϣ");
	outputExamerInfo(examer_list);
}

/*
 * Function Name:	inputPeopleNum
 * Function:		input people number
 * Input Parameters:int min_num
					int max_num
					const char* promopt
 * Return Value:	int
 */
int inputPeopleNum(int min_num, int max_num, const char* promopt)
{
	while (true)
	{
		std::cout << "������" << promopt << "[���뷶Χ:" << min_num << "��" << max_num << "֮�������]" << std::endl;
		int examer_num;
		std::cout << ">>> ";
		std::cin >> examer_num;
		if (std::cin.good() && (min_num <= examer_num && examer_num <= max_num))
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			return static_cast<int>(examer_num);
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cerr << ">>> ���벻�Ϸ�������������" << std::endl;
		}
	}
}

/*
 * Function Name:	makeChoice
 * Function:		make choice
 * Input Parameters:const char* prompt
 * Return Value:	int
 */
int makeChoice(const char* prompt)
{
	std::cout << prompt;
	while (true) {
		char choice = _getch();
		if (choice == 0 || choice == 32)
			choice = _getch();
		if ('0' <= choice && choice <= '5') {
			std::cout << " [" << choice - '0' << "]" << std::endl << std::endl;
			return choice - '0';
		}
	}
}

/*
 * Function Name:	inputInsertLocation
 * Function:		input insert location
 * Input Parameters:const char* prompt
					int lower_bound
					int upper_bound
 * Return Value:	int
 */
int inputInsertLocation(const char* prompt, int lower_bound, int upper_bound)
{
	std::cout << prompt << "[�ɲ����λ�÷�Χ:" << lower_bound << "-" << upper_bound << "]" << std::endl;
	while (true)
	{
		int loaction;
		std::cin >> loaction;
		if (std::cin.good() && (lower_bound <= loaction && loaction <= upper_bound))
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			return loaction;
		}
		else
		{
			std::cerr << ">>> �����λ�ò��Ϸ�������������!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
	}
}

/*
 * Function Name:	findNoLocation
 * Function:		find location of examer by no
 * Input Parameters:List<examer_info>& examer_list
					const char* no
 * Return Value:	int
 */
int findNoLocation(List<ExamerIinfo>& examer_list, const char* no)
{
	LinkNode<ExamerIinfo>* current = examer_list.getHead()->link;
	int location = 1;
	while (current != NULL)
	{
		if (!strcmp(current->data.no, no))
			return location;
		current = current->link;
		location++;
	}
	return 0;
}

/*
 * Function Name:	getExmaerNoAndPos
 * Function:		get examer no and position
 * Input Parameters:List<examer_info>& examer_list
					const char* prompt
 * Return Value:	int
 */
int getExmaerNoAndPos(List<ExamerIinfo>& examer_list, const char* prompt)
{
	std::cout << prompt << " [������ 12 �������ַ���ɵ��ַ������������ֽ����ض�]: " << std::endl;
	char target_no[MAX_SIZE];
	while (true)
	{
		char examer_no[MAX_SIZE] = { 0 };
		std::cin >> examer_no;
		truncateExamerInfo(examer_no, 12);
		if (!checkExamerNoValid(examer_no))
		{
			std::cerr << ">>> ����Ŀ��Ų��Ϸ�������������!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		else if (!checkExamerNoSame(examer_list, examer_no))
		{
			std::cerr << ">>> δ��ѯ���ÿ���������������!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		strcpy_s(target_no, examer_no);
		break;
	}
	return findNoLocation(examer_list, target_no);
}

/*
 * Function Name:	insertExamer
 * Function:		insert examer
 * Input Parameters:List<examer_info>& examer_list
 * Return Value:	void
 */
void insertExamer(List<ExamerIinfo>& examer_list)
{
	//�������λ�úͿ�����Ϣ
	int location = inputInsertLocation(">>> ��������Ҫ����Ŀ�����λ��:", 1, examer_list.getLength() + 1);
	outputInputRequirement(">>> ��������Ҫ����Ŀ�����Ϣ");
	ExamerIinfo temp_examer = inputExamerInfo(examer_list);
	examer_list.insert(location - 1, temp_examer);
	//չʾ������Ϣ
	outputMeterHeader(">>> ������Ϣ:");
	outputExamerInfo(temp_examer);
	outputMeterHeader(">>> �����Ŀ�����Ϣ����:");
	outputExamerInfo(examer_list);
}

/*
 * Function Name:	removeExamer
 * Function:		remove examer
 * Input Parameters:List<examer_info>& examer_list
 * Return Value:	void
 */
void removeExamer(List<ExamerIinfo>& examer_list)
{
	//��鿼����Ϣϵͳ�Ƿ�Ϊ��
	if (!checkListNotEmpty(examer_list, ">>> �޿�����Ϣ�����ɽ���ɾ����������ѡ����������!"))
		return;
	//����Ҫɾ���Ŀ�����Ϣ
	ExamerIinfo temp_examer;
	int location = getExmaerNoAndPos(examer_list, ">>> ��������Ҫɾ���Ŀ����Ŀ���:");
	examer_list.remove(location, temp_examer);
	//չʾ������Ϣ
	outputMeterHeader(">>> ������Ϣ:");
	outputExamerInfo(temp_examer);
	outputMeterHeader(">>> ɾ����Ŀ�����Ϣ����:");
	outputExamerInfo(examer_list);
}

/*
 * Function Name:	findExamer
 * Function:		find examer
 * Input Parameters:List<examer_info>& examer_list
 * Return Value:	void
 */
void findExamer(List<ExamerIinfo>& examer_list)
{
	//��鿼����Ϣϵͳ�Ƿ�Ϊ��
	if (!checkListNotEmpty(examer_list, ">>> �޿�����Ϣ�����ɽ��в��Ҳ�������ѡ����������!"))
		return;
	//����Ҫ���ҵĿ�������
	ExamerIinfo temp_examer;
	int location = getExmaerNoAndPos(examer_list, ">>>��������Ҫ���ҵĿ����Ŀ���:");
	examer_list.getData(location, temp_examer);
	//չʾ������Ϣ
	outputMeterHeader(">>>������Ϣ:");
	outputExamerInfo(temp_examer);
	outputMeterHeader(">>>���ҵ��Ŀ�����Ϣ����:");
	outputExamerInfo(temp_examer);
}

/*
 * Function Name:	modifyExamer
 * Function:		modify examer
 * Input Parameters:List<examer_info>& examer_list
 * Return Value:	void
 */
void modifyExamer(List<ExamerIinfo>& examer_list)
{
	//��鿼����Ϣϵͳ�Ƿ�Ϊ��
	if (!checkListNotEmpty(examer_list, ">>> �޿�����Ϣ�����ɽ����޸Ĳ�������ѡ����������!"))
		return;
	//���뿼�ţ����ҿ���λ��
	int location = getExmaerNoAndPos(examer_list, ">>> ��������Ҫ�޸ĵĿ����Ŀ���:");
	ExamerIinfo temp_examer;
	//ɾ������ԭ������Ϣ
	examer_list.remove(location, temp_examer);
	outputMeterHeader(">>> �ÿ�����ԭʼ��Ϣ����:");
	outputExamerInfo(temp_examer);
	outputInputRequirement(">>> ��������Ҫ�޸ĵĿ�����Ϣ");
	temp_examer = inputExamerInfo(examer_list);
	//�ڿ���ԭ����λ�ò����޸ĺ����Ϣ
	examer_list.insert(location - 1, temp_examer);
	outputMeterHeader(">>> �޸ĺ�Ŀ�����Ϣ����:");
	outputExamerInfo(examer_list);
}



/*
 * Function Name:	statisticExamer
 * Function:		statistic examer information
 * Input Parameters:List<examer_info>& examer_list
 * Return Value:	void
 */
void statisticExamer(List<ExamerIinfo>& examer_list)
{
	if (examer_list.isEmpty())
	{
		std::cerr << ">>> �޿�����Ϣ�����ɽ���ͳ�Ʋ�������ѡ����������!" << std::endl << std::endl;
		return;
	}

	int not_output = 0, output = 1;
	int examer_nums = examer_list.getLength(), male_num = 0, age_num[100] = { 0 };
	LinkNode<ExamerIinfo>* current = examer_list.getHead()->link;
	std::cout << ">>> �������ͳ��" << std::endl;
	std::cout << "+----------------------------------+--------+--------------+" << std::endl;
	std::cout << "| �������                         |  ����  | ����(%)      |" << std::endl;
	std::cout << "+----------------------------------+--------+--------------+" << std::endl;

	//���붯̬�ڴ棬���ڼ�鱨������Ƿ񱻱���
	int position = 1;
	int* outer = new int[examer_nums + 2], * outer_start = outer;
	for (int i = 1; i < examer_nums + 2; i++, outer++)
		*outer = not_output;

	outer = outer_start;//ָ��ص���ʼ��

	while (current != NULL)
	{
		if (*outer == not_output)//����ñ������û�б����
		{
			*outer = output;//����Ϊ���
			outer++;//���±���
			LinkNode<ExamerIinfo>* inner = examer_list.locate(position);
			std::cout << "| " << std::setiosflags(std::ios::left) << std::setw(32) << inner->data.category;//��������������
			int category_count = 1;
			char current_category[MAX_SIZE] = { 0 };
			strcpy_s(current_category, current->data.category);
			while (inner->link != NULL)
			{
				inner++;
				if (!strcmp(inner->data.category, current_category))
					category_count++;
			}
			std::cout << " | " << std::setw(6) << category_count << " | " << std::setprecision(6) << std::setw(12) << category_count * 100 / static_cast<double>(examer_list.getLength()) << " |" << std::endl;
			std::cout << "+----------------------------------+--------+--------------+" << std::endl;
		}
		position++;//�����ƶ�һλ

		//ͳ�����Կ�������
		if (current->data.sex)
			male_num++;
		//ͳ�Ƹ����俼������
		age_num[current->data.age]++;
		current = current->link;
	}
	delete[]outer_start;
	statisticSex(examer_list, male_num);
	statisticAge(examer_list, age_num);
	std::cout << std::endl;
}


/*
 * Function Name:	examinationSystem
 * Function:		operate examination system
 * Input Parameters:void
 * Return Value:	void
 */
void examinationSystem()
{
	std::cout << "+----------------------------+" << std::endl;
	std::cout << "|        ���Ա���ϵͳ        |" << std::endl;
	std::cout << "|  Exam Registration System  |" << std::endl;
	std::cout << "+----------------------------+" << std::endl;
	std::cout << std::endl << ">>> �뽨��������Ϣϵͳ" << std::endl << std::endl;

	//���뿼������
	List<ExamerIinfo> examer_info;
	int examer_num = inputPeopleNum(1, INT_MAX, "��������");
	//����������Ϣϵͳ
	buildExamerList(examer_info, examer_num);

	while (true)
	{
		int choice = makeChoice(">>> ��ѡ����Ҫ���еĲ��� [1]Ϊ���� [2]Ϊɾ�� [3]Ϊ���� [4]Ϊ�޸� [5]Ϊͳ�� [0]Ϊȡ������");
		switch (choice)
		{
		case 1:
			insertExamer(examer_info);
			break;
		case 2:
			removeExamer(examer_info);
			break;
		case 3:
			findExamer(examer_info);
			break;
		case 4:
			modifyExamer(examer_info);
			break;
		case 5:
			statisticExamer(examer_info);
			break;
		case 0:
			return;
			break;
		default:
			break;
		}
	}
}

/*
 * Function Name:	main
 * Function:		main function
 * Return Value:	0
 */
int main()
{
	examinationSystem();
	/*wait for user input to quit*/
	std::cout << "Press Enter to Quit" << std::endl;
	while (_getch() != '\r')
		continue;
	return 0;
}