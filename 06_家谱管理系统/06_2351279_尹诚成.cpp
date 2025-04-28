#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <limits>
#include <sstream>
#include <cstring>
#include <conio.h>

#define MEMORY_ALLOCATION_ERROR -1
#define MAX_NAME_LENGTH 32
#define MAX_GENERATION_NUM 16


template<typename T>
struct LinkNode
{
    T data;
    LinkNode<T>* link;
    LinkNode(LinkNode<T>* ptr = NULL) { link = ptr; }
    LinkNode(T item, LinkNode<T>* ptr = NULL) : data(item), link(ptr) {}
};

template<typename T>
class LinkedQueue
{
private:
    LinkNode<T>* front, * rear;
public:
    LinkedQueue() { front = rear = NULL; }
    ~LinkedQueue() { makeEmpty(); }
    bool EnQueue(const T item);
    bool DeQueue(T& item);
    bool getFront(T& item) const;
    void makeEmpty();
    bool IsEmpty() const { return front == NULL; }
    int getSize() const;
};

/*
 * Function Name:    makeEmpty
 * Function:         Clear the queue
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template<typename T>
void LinkedQueue<T>::makeEmpty()
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
bool LinkedQueue<T>::EnQueue(const T item)
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
bool LinkedQueue<T>::DeQueue(T& item)
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
bool LinkedQueue<T>::getFront(T& item) const
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
int LinkedQueue<T>::getSize() const
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

template <typename T>
struct BinTreeNode {
    T data;
    BinTreeNode<T>* leftChild;
    BinTreeNode<T>* rightChild;
    BinTreeNode() :
        data(T()), leftChild(NULL), rightChild(NULL) {}
    BinTreeNode(T item, BinTreeNode<T>* l = NULL, BinTreeNode<T>* r = NULL) :
        data(item), leftChild(l), rightChild(r) {}
};

template <typename T>
class BinaryTree {
private:
    BinTreeNode<T>* copy(const BinTreeNode<T>* subTree);
    void outputNode(BinTreeNode<T>* subTree) { if (subTree != NULL)std::cout << subTree->data << " "; }
    void (BinaryTree::* visitFunc)(BinTreeNode<T>*);
protected:
    BinTreeNode<T>* root;
public:
    BinaryTree() : root(NULL), visitFunc(&BinaryTree::outputNode){}
    BinaryTree(T& item);
    BinaryTree(BinaryTree<T>& other) { root = copy(other.root); }
    ~BinaryTree() { destroy(root); }
    void destroy(BinTreeNode<T>*& subTree);
    bool isEmpty(void) { return root == NULL; }
    int getHeight(BinTreeNode<T>* subTree) { return (subTree == NULL) ? 0 : (std::max(getHeight(subTree->leftChild), getHeight(subTree->rightChild)) + 1); }
    int getSize(BinTreeNode<T>* subTree) { return (subTree == NULL) ? 0 : (getSize(subTree->leftChild) + getSize(subTree->rightChild) + 1); }
    BinTreeNode<T>* getRoot(void) { return root; }
    BinTreeNode<T>* getParent(BinTreeNode<T>* current, BinTreeNode<T>* subTree);
    BinTreeNode<T>* getLeftChild(BinTreeNode<T>* current) { return current == NULL ? NULL : current->leftChild; }
    BinTreeNode<T>* getRightChild(BinTreeNode<T>* current) { return current == NULL ? NULL : current->rightChild; }
    BinTreeNode<T>* findNode( T& item, BinTreeNode<T>* subTree);
    void inOrder(BinTreeNode<T>* subTree, void (BinaryTree::* visitFunc)(BinTreeNode<T>*));
    void preOrder(BinTreeNode<T>* subTree, void (BinaryTree::* visitFunc)(BinTreeNode<T>*));
    void postOrder(BinTreeNode<T>* subTree, void (BinaryTree::* visitFunc)(BinTreeNode<T>*));
    void levelOrder(BinTreeNode<T>* subTree, void (BinaryTree::* visitFunc)(BinTreeNode<T>*));
    bool insertFrontLeft(BinTreeNode<T>*& subTree, const T& item);
    bool insertFrontRight(BinTreeNode<T>*& subTree, const T& item);
    void inOrderOutput(BinTreeNode<T>* subTree) { inOrder(subTree, &BinaryTree::outputNode); }
    void preOrderOutput(BinTreeNode<T>* subTree) { preOrder(subTree, &BinaryTree::outputNode); }
    void postOrderOutput(BinTreeNode<T>* subTree) { postOrder(subTree, &BinaryTree::outputNode); }
    void levelOrderOutput(BinTreeNode<T>* subTree) { levelOrder(subTree, &BinaryTree::outputNode); }
    bool modifyNode(BinTreeNode<T>*& subTree,  T& oldItem,  T& newItem);
    BinaryTree<T>& operator=(const BinaryTree<T>& other);
};


/*
 * Function Name:    BinaryTree
 * Function:         Constructed function
 * Input Parameters: T& item
 * Notes:            Class external implementation of member functions
 */
template <typename T>
BinaryTree<T>::BinaryTree(T& item)
{
    root = new(std::nothrow) BinTreeNode<T>(item);
    if (root == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
}

/*
 * Function Name:    copy
 * Function:         Copy a subtree
 * Input Parameters: const BinTreeNode<Type>* subTree
 * Return Value:     a new subtree / NULL
 * Notes:            Class external implementation of member functions
 */
template<typename T>
BinTreeNode<T>* BinaryTree<T>::copy(const BinTreeNode<T>* subTree)
{
    if (subTree == NULL)
        return NULL;
    BinTreeNode<T>* newNode = new(std::nothrow) BinTreeNode<T>(subTree->data);
    if (newNode == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    newNode->leftChild = copy(subTree->leftChild);
    newNode->rightChild = copy(subTree->rightChild);
    return newNode;
}


/*
 * Function Name:    destroy
 * Function:         Destroy a subtree
 * Input Parameters: BinTreeNode<T>*& subTree
 * Notes:            Class external implementation of member functions
 * Return Value:     void
 */
template <typename T>
void BinaryTree<T>::destroy(BinTreeNode<T>*& subTree)
{
    if (subTree) {
        destroy(subTree->leftChild);
        destroy(subTree->rightChild);
        //delete subTree;
        subTree = NULL;
    }
}

/*
 * Function Name:    getParent
 * Function:         Find the parent of a given node
 * Input Parameters: BinTreeNode<T>* current
 *                   BinTreeNode<T>* subTree
 * Return Value:     the parent of a given node / NULL
 * Notes:            Class external implementation of member functions
 */
template <typename T>
BinTreeNode<T>* BinaryTree<T>::getParent(BinTreeNode<T>* current, BinTreeNode<T>* subTree)
{
    if (subTree == NULL || current == NULL)
        return NULL;
    if (subTree->leftChild == current || subTree->rightChild == current)
        return subTree;
    BinTreeNode<T>* foundParent = getParent(current, subTree->leftChild);
    if (foundParent == NULL)
        foundParent = getParent(current, subTree->rightChild);
    return foundParent;
}

/*
 * Function Name:    findNode
 * Function:         Find a node with a given value
 * Input Parameters: const Type& item
 *                   MyBinTreeNode<Type>* subTree
 * Return Value:     the node / NULL
 * Notes:            Class external implementation of member functions
 */
template <typename T>
BinTreeNode<T>* BinaryTree<T>::findNode( T& item, BinTreeNode<T>* subTree)
{
    if (subTree == NULL)
        return NULL;
    if (subTree->data == item)
        return subTree;
    BinTreeNode<T>* found = findNode(item, subTree->leftChild);
    if (found != NULL)
        return found;
    return findNode(item, subTree->rightChild);
}

/*
 * Function Name:   inOrder
 * Function:        Traverse a subtree in in-order
 * Input Parameters:BinTreeNode<T>* subTree
 *                  void (BinaryTree::* visitFunc)(BinTreeNode<T>*)
 * Return Value:    void
 * Notes:           class external implementation of member functions
 */
template <typename T>
void BinaryTree<T>::inOrder(BinTreeNode<T>* subTree, void(BinaryTree::* visitFunc)(BinTreeNode<T>*))
{
    if (subTree != NULL) {
        inOrder(subTree->leftChild);
        (this->*visitFunc)(subTree);
        inOrder(subTree->rightChild);
    }
}


/*
 * Function Name:   preOrder
 * Function:        Traverse a subtree in pre-order
 * Input Parameters:BinTreeNode<T>* subTree
 *                  void (BinaryTree::* visitFunc)(BinTreeNode<T>*)
 * Return Value:    void
 * Notes:           class external implementation of member functions
 */
template <typename T>
void BinaryTree<T>::preOrder(BinTreeNode<T>* subTree,void(BinaryTree::* visitFunc)(BinTreeNode<T>*))
{
    if (subTree != NULL) {
        (this->*visitFunc)(subTree);
        preOrder(subTree->leftChild );
        preOrder(subTree->rightChild);
    }
}

/*
 * Function Name:   postOrder
 * Function:        Traverse a subtree in post-order
 * Input Parameters:BinTreeNode<T>* subTree
 *                  void (BinaryTree::* visitFunc)(BinTreeNode<T>*)
 * Return Value:    void
 * Notes:           class external implementation of member functions
 */
template <typename T>
void BinaryTree<T>::postOrder(BinTreeNode<T>* subTree, void(BinaryTree::* visitFunc)(BinTreeNode<T>*))
{
    if (subTree != NULL) {
        postOrder(subTree->leftChild);
        postOrder(subTree->rightChild);
        (this->*visitFunc)(subTree);
    }
}


/*
 * Function Name:    levelOrder
 * Function:         Traverse a subtree in level-order
 * Input Parameters: BinTreeNode<T>* subTree
 *                   void (BinaryTree::* visitFunc)(BinTreeNode<T>*)
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename T>
void BinaryTree<T>::levelOrder(BinTreeNode<T>* subTree, void(BinaryTree::* visitFunc)(BinTreeNode<T>*))
{
    if (subTree != NULL) {
        LinkedQueue<BinTreeNode<T>*> queue;
        queue.EnQueue(subTree);
        while (!queue.IsEmpty()) {
            BinTreeNode<T>* current;
            if (!queue.DeQueue(current))
                return;
            (this->*visitFunc)(subTree);
            if (current->leftChild != NULL)
                queue.EnQueue(current->leftChild);
            if (current->rightChild != NULL)
                queue.EnQueue(current->rightChild);
        }
    }
}

/*
 * Function Name:   insertFrontLeft
 * Function:        insert a node as the left child of the current node
 * Input Parameters:BinTreeNode<T>*& subTree
 *                  const T& item
 * Return Value:    void
 * Notes:           class external implementation of member functions
 */
template <typename T>
bool BinaryTree<T>::insertFrontLeft(BinTreeNode<T>*& subTree, const T& item)
{
    if (subTree == NULL || subTree->leftChild != NULL)
        return false;
    subTree->leftChild = new(std::nothrow) BinTreeNode<T>(item);
    if (subTree->leftChild == NULL)
    {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    return true;
}

/*
 * Function Name:   insertFrontRight
 * Function:        insert a node as the right child of the current node
 * Input Parameters:BinTreeNode<T>*& subTree
 *                  const T& item
 * Return Value:    void
 * Notes:           class external implementation of member functions
 */
template <typename T>
bool BinaryTree<T>::insertFrontRight(BinTreeNode<T>*& subTree, const T& item)
{
    if (subTree == NULL || subTree->rightChild != NULL)
        return false;
    subTree->rightChild = new(std::nothrow) BinTreeNode<T>(item);
    if (subTree->rightChild == NULL)
    {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    return true;
}

/*
 * Function Name:   modifyNode
 * Function:        Modify the value of a node
 * Input Parameters:BinTreeNode<T>*& subTree
 *                  const T& oldItem
 *                  const T& newItem
 * Return Value:    true / false
 * Notes:           class external implementation of member functions
 */
template <typename T>
bool BinaryTree<T>::modifyNode(BinTreeNode<T>*& subTree,  T& oldItem, T& newItem)
{
    BinTreeNode<T>* node = findNode(oldItem, subTree);
    if (node == NULL)
        return false;
    else {
        node->data = newItem;
        return true;
    }
    return true;
}

/*
 * Function Name:    operator=
 * Function:         Overload operator =
 * Input Parameters: const BinaryTree<T>& other
 * Return Value:     *this
 * Notes:            Class external implementation of member functions
 */
template <typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other)
{
    if (this != &other) {
        destroy(root);
        root = copy(other.root);
    }
    return *this;
}


struct Person {
    char name[MAX_NAME_LENGTH + 1];
    Person() { strcpy(name, ""); }
    Person(const char* prompt) { strcpy(name, prompt); }
    Person operator =(const Person& person) { if (this != &person)strcpy(name, person.name); return *this; }
    bool operator ==(Person& person) { return !strcmp(name, person.name); }
    friend std::ostream& operator <<(std::ostream& out, Person& person);
    friend std::istream& operator >>(std::istream& in, Person& person);
};

/* 
 * Function Name:   operator <<
 * Function:        Output a person
 * Input Parameters:std::ostream& out
 *                  Person& person
 * Return Value:    out
 */
std::ostream& operator <<(std::ostream& out, Person& person) {
    out << person.name;
    return out;
}

/*
 * Function Name:   operator >>
 * Function:        Input a person
 * Input Parameters:std::istream& in
 *                  Person& person
 * Return Value:    in
 */
std::istream& operator >>(std::istream& in, Person& person) {
    std::cin >> person.name;
    person.name[MAX_NAME_LENGTH] = '\0';
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return in;
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
    while (true){
        char choice = _getch();;
        if (choice == 0 || choice == 32)
            choice = _getch();
        if ('0' <= choice && choice <= '5') {
            std::cout << " [" << choice - '0' << "]" << std::endl << std::endl;
            return choice - '0';
        }
    }
}


 /*
  * Function Name:   outputGeneration
  * Function:        output the generation of the person
  * Input Parameters:BinTreeNode<Person>* current
  *                  const char* prompt
  * Return Value:    void
  */
void outputGeneration(BinTreeNode<Person>* current,  const char* prompt,int generationCount) {
    std::cout << ">>> " << prompt << "�ĵ�" << generationCount << "һ��������:";
    current = current->leftChild;
    std::cout << current->data.name << " ";
    while (current->rightChild != NULL) { 
        current = current->rightChild;
        std::cout << current->data.name << " ";
    }
    std::cout << std::endl;
}

/*
 * Function Name:   addOnePerson
 * Function:        add A person to genealogy
 * Input Parameters:BinaryTree<Person>& genealogy
 *                  BinTreeNode<Person>* current
 *                  Person person
 * Return Value:    void
 */
void addOnePerson(BinaryTree<Person>& genealogy,BinTreeNode<Person>* current, Person person) {
    if (current->leftChild == NULL) {
        genealogy.insertFrontLeft(current, person);
    }
    else {
        current = current->leftChild;
        while (current->rightChild != NULL) {
            current = current->rightChild;
        }
         genealogy.insertFrontRight(current, person);
    }
}

/*
 * Function Name:   findPersoninGenealogy
 * Function:        find a person in genealogy
 * Input Parameters:BinaryTree<Person>& genealogy
 *                  const char* prompt
 * Return Value:    BinTreeNode<Person>* :the node of the person / NULL
 */
BinTreeNode<Person>* findPersoninGenealogy(BinaryTree<Person>& genealogy,const char *prompt) {
    Person ancestor;
    BinTreeNode<Person>* current;
    while (true) {
        std::cout << prompt;
        std::cin >> ancestor;
        current = genealogy.findNode(ancestor, genealogy.getRoot());
        if (current == NULL) {
            std::cerr << "����ļ�ͥ��Ա������,����������!" << std::endl;
            std::cin.clear();
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return NULL;
        }
        else
            break;
    }
    std::cout << std::endl;
    return current;
}

/*
 * Function Name:   buildFamliy
 * Function:        build a family tree
 * Input Parameters:BinaryTree<Person>& genealogy
 * Return Value:    void
 */
void buildFamliy(BinaryTree<Person>& genealogy) {
    Person generation;
    BinTreeNode<Person>* current;
    /*find the ancestor*/
    while (true) {
        current = findPersoninGenealogy(genealogy, ">>> ������Ҫ������ͥ���˵�����:");
        if (current != NULL && current->leftChild != NULL) {
            std::cerr << current->data.name << "�Ѿ�������ͥ" << std::endl;
            std::cin.clear();
            std::cout << std::endl;
            return;
        }
        else if (current != NULL)
            break;
        else if (current == NULL)
            return;
    }

    /*input the generation num*/
    int generationNum = 0;
    while (true) {
        std::cout << ">>> ������" << current->data.name << "�Ķ�Ů����[������Χ1-" << MAX_GENERATION_NUM << "]:";
        std::cin >> generationNum;
        if (std::cin.fail()) {
            std::cerr << "���벻������,����������!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (generationNum <= 0 || generationNum > MAX_GENERATION_NUM) {
            std::cerr << "��������ֳ�����Χ[" << 0 << "," << MAX_GENERATION_NUM << "],����������!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
            break;
    }
    std::cout << std::endl;
    /*create the generation tree*/
    std::cout << ">>> ����������" << current->data.name << "�Ķ�Ů������:" << std::endl;
    int count = 0;
    while (count < generationNum) {
        std::cout << "�������" << count + 1 << "����Ů������:";
        std::cin >> generation;
        if (genealogy.findNode(generation, genealogy.getRoot())) {
            std::cerr << generation.name << "�ڼ������Ѿ�����,����������!" << std::endl;
            std::cin.clear();
            continue;
        }
        addOnePerson(genealogy, current, generation);
        count++;
    }

    std::cout << std::endl;
    /*output the generation tree*/
    outputGeneration(current, current->data.name,1);
    std::cout << std::endl;
}

/*
 * Function Name:   addFamilyMenber
 * Function:        add a family member to genealogy    
 * Input Parameters:BinaryTree<Person>& genealogy
 * Return Value:    void                    
 */
void addFamilyMenber(BinaryTree<Person>& genealogy) {
    Person  generation;
    BinTreeNode<Person>* current;
    /*find the ancestor*/
    current = findPersoninGenealogy(genealogy, ">>> ������Ҫ���Ӷ�Ů���˵�����:");
    if (current == NULL) {
        std::cerr << "δ�ڼ������ҵ��ó�Ա!" <<std::endl;
        return;
    }
    /*input the generation num*/
    while (true) {
        std::cout << ">>> ������" << current->data.name << "Ҫ���ӵĶ�Ů������:";
        std::cin >> generation;
        if (genealogy.findNode(generation, genealogy.getRoot())) {
            std::cerr << generation.name << "�ڼ������Ѿ�����,����������!" << std::endl;
            return;
        }
   
        addOnePerson(genealogy, current, generation);
        break;
    }

    std::cout << std::endl;
    /*output the generation tree*/
    outputGeneration(current, current->data.name,1);
    std::cout << std::endl ;
}

/*
 * Function Name:   destoryLocalFamily
 * Function:        destory a local family
 * Input Parameters:BinaryTree<Person>& genealogy
 * Return Value:    void
 */
void destoryLocalFamily(BinaryTree<Person>& genealogy) {
    Person ancestor;
    BinTreeNode<Person>* current;
    /*find the ancestor*/
    current = findPersoninGenealogy(genealogy, ">>> ������Ҫ��ɢ��ͥ���˵�����:");
    if (current->leftChild == NULL) {
        std::cerr << "�ó�Աû����Ů!" << std::endl;
        std::cin.clear();
        return;
    }
    /*destory the local family*/
    outputGeneration(current, current->data.name,1);
    std::cout << current->data.name << "�ļ�ͥ�ѽ�ɢ" << std::endl;
    genealogy.destroy(current->leftChild);

}

/*
 * Function Name:   modifyFamilyMember
 * Function:        modify a family member's name
 * Input Parameters:BinaryTree<Person>& genealogy
 * Return Value:    void
 */
void modifyFamilyMember(BinaryTree<Person>& genealogy) {
    BinTreeNode<Person>* current;
    Person newPersonName;
    /*find the ancestor*/
    current = findPersoninGenealogy(genealogy, ">>> ������Ҫ�����������˵�Ŀǰ����:");
    if (current == NULL)
        return;
    while (true) {
        std::cout << ">>> ��������ĺ������:";
        std::cin >> newPersonName;
        if (genealogy.findNode(newPersonName, genealogy.getRoot())) {
            std::cerr << newPersonName.name << "�ڼ������Ѿ�����,����������!" << std::endl;
            return;
        }
        break;
    }
    std::cout << current->data.name;
   genealogy.modifyNode(current, current->data, newPersonName);
   std::cout << "�Ѹ���Ϊ" << current->data.name << std::endl << std::endl;
}

/*
 * Function Name:   statisticFamilyMembers
 * Function:        statistic the number of family members
 * Input Parameters:BinaryTree<Person>& genealogy
 * Return Value:    void
 */
void statisticFamilyMembers(BinaryTree<Person>& genealogy) {
    BinTreeNode<Person>* current;
    Person newPersonName;
    int generationCount = 0;
    /*find the ancestor*/
    current = findPersoninGenealogy(genealogy, ">>> ������Ҫͳ�Ƶļ�ͥ��Ա������:");
    if (current == NULL)
        return;
    BinTreeNode<Person>* travsel = current;
    /*count the generation*/
    while (travsel->leftChild != NULL) {
        generationCount++;
        travsel = travsel->leftChild;
    }
    /*output the generation tree*/
    if (generationCount == 0) 
        std::cout << current->data.name << "û�к��" << std::endl;
    else {
        for (int count = 0; count < generationCount; count++) {
            outputGeneration(current, current->data.name, count + 1);
            current = current->leftChild;
        }
    }
    std::cout << std::endl;
}


/*
 * Function Name:   outputStart
 * Function:        Output the start message of the program 
 * Input Parameters:void
 * Return Value:    void
 */
void outputStart() {
    std::cout << "+-----------------------------+" << std::endl;
    std::cout << "|        ���׹���ϵͳ         |" << std::endl;
    std::cout << "| Genealogy Management System |" << std::endl;
    std::cout << "+-----------------------------+" << std::endl << std::endl;

    std::cout << "��������Ҫ��:�������Ȳ��ܳ���32���ַ���16������,�������ֽ����ض�" << std::endl<<std::endl;

    std::cout << ">>> ���Ƚ���һ������" << std::endl << std::endl;
}

/*
 * Function Name:	main
 * Function:		main function
 * Return Value:	0
 */
int main() {
    /*start the program*/
    outputStart();

    /*create the root node*/
    Person ancestor;
    std::cout << ">>> ���������ȵ�����:";
    std::cin >> ancestor;
    BinaryTree<Person> genealogy(ancestor);
    BinTreeNode<Person>* root = genealogy.getRoot();
    std::cout << std::endl;
    std::cout << ">>> �˼��׵�������:" << ancestor << std::endl << std::endl;

    
    while (true) {
        switch (makeChoice(">>> ��ѡ��Ҫִ�еĲ���\n[1]���Ƽ��� [2]���Ӽ�ͥ��Ա [3]��ɢ�ֲ���ͥ [4]���ļ�ͥ��Ա���� [5]ͳ�ƺ����Ա [0]�˳�����")) {
        case 1:
            buildFamliy(genealogy);
            break;
        case 2:
            addFamilyMenber(genealogy);
            break;
        case 3:
            destoryLocalFamily(genealogy);
            break;
        case 4: 
            modifyFamilyMember(genealogy);
            break;
        case 5:
            statisticFamilyMembers(genealogy);
            break;
        case 0:
            return 0;
        }
    }   
    /*wait for user input to quit*/
    std::cout << "Press Enter to Quit" << std::endl;
    while (_getch() != '\r')
        continue;
    return 0;
}
