#include<iostream>
#include<conio.h>


template<typename T>
struct LinkNode
{
    T data;
    LinkNode<T>* link;
    LinkNode(LinkNode<T>* ptr = NULL) :data(T()), link(ptr) {}
    LinkNode(T item, LinkNode<T>* ptr = NULL) : data(item), link(ptr) {}
};

template<typename T>
class Queue
{
private:
    LinkNode<T>* front, * rear;
public:
    Queue() { front = rear = NULL; }
    ~Queue() { makeEmpty(); }
    bool enQueue(const T item);
    bool deQueue(T& item);
    bool getFront(T& item) const;
    LinkNode<T>* getFront() const { return front; }
    void makeEmpty();
    bool IsEmpty() const { return front == NULL; }
    int getSize() const;
    void outputNode(LinkNode<T>* p, bool lastCunstomer = false);
};

/*
 * Function Name:    makeEmpty
 * Function:         Clear the queue
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template<typename T>
void Queue<T>::makeEmpty()
{
    LinkNode<T>* p;
    while (front != NULL)
    {
        p = front;
        front = front->link;
        delete p;
    }
}

/*
 * Function Name:    EnQueue
 * Function:         Add item to the queue
 * Input Parameters: const T item
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template<typename T>
bool Queue<T>::enQueue(const T item)
{
    if (front == NULL)
    {
        front = rear = new LinkNode<T>;
        if (front == NULL)
            return false;
    }
    else
    {
        rear->link = new LinkNode<T>(item);
        if (rear->link == NULL)
            return false;
        rear = rear->link;
    }
    rear->data = item;
    return true;
}

/*
 * Function Name:    DeQueue
 * Function:         Remove the front element and return its value by reference
 * Input Parameters: T& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template<typename T>
bool Queue<T>::deQueue(T& item)
{
    if (IsEmpty())
        return false;
    LinkNode<T>* p = front;
    item = front->data;
    front = front->link;
    delete p;
    return true;
}

/*
 * Function Name:    getFront
 * Function:         Get the value of the front element
 * Input Parameters: Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template<typename T>
bool Queue<T>::getFront(T& item) const
{
    if (IsEmpty())
        return false;
    item = front->data;
    return true;
}

/*
 * Function Name:    getSize
 * Function:         Calculate the number of elements in the queue
 * Input Parameters: void
 * Return Value:     the number of elements in the queue
 * Notes:            Class external implementation of member functions
 */
template<typename T>
int Queue<T>::getSize() const
{
    int size = 0;
    LinkNode<T>* p = front;
    while (p != NULL)
    {
        size++;
        p = p->link;
    }
    return size;
}

/*
 * Function Name:   outputNode
 * Function:        output the infomation of node
 * Input Parameters:LinkNode<T>* p
 *                  bool lastCunstomer
 * Return Value:    void
 * Notes:           class external implementation of member functions
 */
template<typename T>
void Queue<T>::outputNode(LinkNode<T>* p,bool lastCunstomer)
{
    if (p != NULL) {
        if (lastCunstomer)
            std::cout << p->data ;
        else
            std::cout << p->data << " ";
    }
}

/*
 * Function Name:   inputCustomerInfo
 * Function:        input the infomation of customer
 * Input Parameters:Queue<int>& A
 *                  Queue<int>& B
 *                  int& N
 * Return Value:    true / false 
 */
bool inputCustomerInfo(Queue<int>& A, Queue<int>& B, int& N) {
    double temp;
    std::cin >> temp;
    if (std::cin.fail() || temp <= 0 || temp > 1000||static_cast<int>(temp)!=temp) {
        std::cerr << ">>> 顾客总数N值输入有误,请重新输入！" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    N = static_cast<int>(temp);
    for (int i = 0; i < N; i++) {
        int num;
        std::cin >> num;
        if (std::cin.fail()||num<=0) {
            std::cerr << ">>> 顾客编号必须为正整数,请重新输入！" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
        else if(num>=1e9) {
            std::cerr << ">>> 顾客编号不能超过九位数,请重新输入！" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
        if (num % 2 == 1)
            A.enQueue(num);
        else
            B.enQueue(num);
    }

    return true;
}

/*
 * Function Name:   outputCustomerNo
 * Function:        output the infomation of customer
 * Input Parameters:Queue<int>& A
 *                  Queue<int>& B
 *                  int& N
 * Return Value:    void
 */
void outputCustomerNo(Queue<int>& A, Queue<int>& B,int &N) {
    LinkNode<int>* currentA ;
    LinkNode<int>* currentB ;
    bool lastCunstomer = false;
    int cunstomerNum = 0;
    std::cout << std::endl;
    std::cout << ">>> 顾客业务完成的顺序为: ";
    while (!A.IsEmpty() && !B.IsEmpty()) {
        currentA = A.getFront();
        cunstomerNum++;
        if (cunstomerNum == N)
            lastCunstomer = true;
        A.outputNode(currentA, lastCunstomer);
        A.deQueue(currentA->data);
        if (!A.IsEmpty()) {
            currentA = A.getFront();
            cunstomerNum++;
            if (cunstomerNum == N)
                lastCunstomer = true;
            A.outputNode(currentA, lastCunstomer);
            A.deQueue(currentA->data);
        }
        currentB =B.getFront();
        cunstomerNum++;
        if (cunstomerNum == N)
            lastCunstomer = true;
        B.outputNode(currentB, lastCunstomer);
        B.deQueue(currentB->data);
    }
    while (!A.IsEmpty()) {
        currentA = A.getFront();
        cunstomerNum++;
        if (cunstomerNum == N)
            lastCunstomer = true;
        A.outputNode(currentA, lastCunstomer);
        A.deQueue(currentA->data);
    }
    while (!B.IsEmpty()) {
        currentB = B.getFront();
        cunstomerNum++;
        if (cunstomerNum == N)
            lastCunstomer = true;
        B.outputNode(currentB, lastCunstomer);
        B.deQueue(currentB->data);
    }
    std::cout << std::endl;
}

/*
 * Function Name:   outputStart
 * Function:        output the start information of the program
 * Input Parameters:void
 * Return Value:    void
 */
void outputStart() {
    std::cout << "+------------------------+" << std::endl;
    std::cout << "|        银行业务        |" << std::endl;
    std::cout << "|    Banking Business    |" << std::endl;
    std::cout << "+------------------------+" << std::endl << std::endl;

    std::cout << ">>> 输入要求说明:" << std::endl;
    std::cout << "[1] 输入为一行正整数" << std::endl;
    std::cout << "[2] 输入的第一个数字表示顾客的总数N,后面的数字表示N位顾客的编号" << std::endl;
    std::cout << "[3] N<=1000,且每个顾客的编号不能超过9位数,不同顾客之间的编号用空格隔开" << std::endl << std::endl;

}

/*
 * Function Name:   main
 * Function:        main function 
 * Return Value:    0
 */
int main(){
	outputStart();
    Queue<int> A;
    Queue<int> B;
    int N;
    do {
        std::cout << ">>> 请输入顾客的总数N和每位顾客的编号: ";
        A.makeEmpty();
        B.makeEmpty();
    } while (!inputCustomerInfo(A, B, N));
    outputCustomerNo(A, B, N);
    /*wait for user input to quit*/
    std::cout << "Press Enter to Quit" << std::endl;
    while (_getch() != '\r')
        continue;
	return 0;
}