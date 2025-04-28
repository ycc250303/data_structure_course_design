#include <iostream>
#include <limits>
#include<conio.h>

#define EXPRESSION_MAX_LEN 20//the maximum length of expression
#define EXPRESSION_MAX_CHAR 256
#define EXPRESSION_MAX_OPERAND_LENGTH 8//the maxinum digits 
#define CALCULATE_ERROR 1E-6//the error of calculation

#define MEMORY_ALLOCATION_ERROR -1


union Expression
{
    char type;
    double value;
};

/*
 * Function Name:   operator<<
 * Function:        overload the output operator for Expression class
 * Input Parameters:std::ostream& os, const Expression& exp
 * Return Value:    os
 */

std::ostream& operator<<(std::ostream& os, const Expression& exp) {
    if (exp.type == '\0') {//output operand
        os << exp.value;
    }
    else {//output operator
        os << exp.type;
    }
    return os;
}

template<typename T>
struct LinkNode
{
    T data;
    LinkNode<T>* link;
    LinkNode(LinkNode<T>* ptr = NULL) { link = ptr; }
    LinkNode(T item, LinkNode<T>* ptr = NULL) : data(item), link(ptr) {}
};


template <typename T>
class Stack {
private:
    LinkNode<T>* top;
public:
    Stack() : top(NULL) {}
    ~Stack() { makeEmpty(); }
    void Push(T item);
    bool Pop(T& item);
    bool getTop(T& item) const;
    T Top() const;
    bool IsEmpty() const { return top == NULL; }
    int getSize() const;
    void makeEmpty();
};

/*
 * Function Name:   Push
 * Function:        push an item onto the top of the stack
 * Input Parameters:const T& item
 * Return Value:    void
 * Notes:           Class external implementation of member functions
 */
template <typename T>
void Stack<T>::Push(T item) {
    LinkNode<T>* newNode = new LinkNode<T>(item);
    if (newNode == NULL)
    {
        std::cerr << "Memory allocation failed in Push()." << std::endl;
        exit(1);
    }
    newNode->link = top;
    top = newNode;
}

/*
 * Function Name:   Pop
 * Function:        remove and return the top item from the stack
 * Input Parameters:const T& item
 * Return Value:    void
 * Notes:           Class external implementation of member functions
 */
template <typename T>
bool Stack<T>::Pop(T& item) {
    if (IsEmpty())
        return false;
    LinkNode<T>* temp = top;
    top = top->link;
    item = temp->data;
    delete temp;
    return true;
}

/*
 * Function Name:   getTop
 * Function:        get the top item from the stack without removing it
 * Input Parameters:T& item
 * Return Value:    true / false
 * Notes:           Class external implementation of member functions
 */
template <typename T>
bool Stack<T>::getTop(T& item) const {
    if (IsEmpty())
        return false;
    item = top->data;
    return true;
}

template <typename T>
T Stack<T>::Top() const {
    if (IsEmpty())
        return std::numeric_limits<T>::max();
    return top->data;
}

/*
 * Function Name:   getSize
 * Function:        get the size of the stack
 * Input Parameters:void
 * Return Value:    int
 * Notes:           Class external implementation of member functions
 */
template <typename T>
int Stack<T>::getSize() const {
    int size = 0;
    LinkNode<T>* temp = top;
    while (temp != NULL) {
        size++;
        temp = temp->link;
    }
    return size;
}

/*
 * Function Name:   makeEmpty
 * Function:        make the stack empty
 * Input Parameters:void
 * Return Value:    void
 * Notes:           Class external implementation of member functions
 */
template <typename T>
void Stack<T>::makeEmpty() {
    while (!IsEmpty()) {
        LinkNode<T>* temp = top;
        top = top->link;
        delete temp;
    }
}

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
    BinTreeNode() : data(T()),leftChild(NULL), rightChild(NULL) {}
    BinTreeNode(T item, BinTreeNode<T>* l = NULL, BinTreeNode<T>* r = NULL) : data(item), leftChild(l), rightChild(r) {}
};

template <typename T>
class BinaryTree {
private:
    BinTreeNode<T>* copy(const BinTreeNode<T>* subTree);
protected:
    BinTreeNode<T>* root;
public:
    BinaryTree() : root(NULL) {}
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
    BinTreeNode<T>* findNode(const T& item, BinTreeNode<T>* subTree);
    void inOrder(BinTreeNode<T>* subTree);
    void preOrder(BinTreeNode<T>* subTree, bool lastNode);
    void postOrder(BinTreeNode<T>* subTree);
    void levelOrder(BinTreeNode<T>* subTree);
    bool insertFrontLeft(BinTreeNode<T>*& subTree, const T& item);
    bool insertFrontRight(BinTreeNode<T>*& subTree, const T& item);
    void inOrderOutput(BinTreeNode<T>* subTree) { inOrder(subTree); }
    void preOrderOutput(BinTreeNode<T>* subTree) { preOrder(subTree, false); }
    void postOrderOutput(BinTreeNode<T>* subTree) { postOrder(subTree); }
    void levelOrederOutput(BinTreeNode<T>* subTree) { levelOrder(subTree); }
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
        delete subTree;
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
BinTreeNode<T>* BinaryTree<T>::findNode(const T& item, BinTreeNode<T>* subTree)
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
 * Return Value:    void
 * Notes:           class external implementation of member functions
 */
template <typename T>
void BinaryTree<T>::inOrder(BinTreeNode<T>* subTree)
{
    if (subTree != NULL) {
        inOrder(subTree->leftChild);
        std::cout << subTree->data << " ";
        inOrder(subTree->rightChild);
    }
}


/*
 * Function Name:   preOrder
 * Function:        Traverse a subtree in pre-order
 * Input Parameters:BinTreeNode<T>* subTree
 *                  bool lastNode
 * Return Value:    void
 * Notes:           class external implementation of member functions
 */
template <typename T>
void BinaryTree<T>::preOrder(BinTreeNode<T>* subTree, bool lastNode)
{
    static int count = 0;
    if (subTree != NULL) {
        if (count == getSize(root)-1)
            std::cout << subTree->data;
        else
            std::cout << subTree->data << " ";
        count++;
        preOrder(subTree->leftChild, false);
        preOrder(subTree->rightChild, true);
    }
}

/*
 * Function Name:   postOrder
 * Function:        Traverse a subtree in post-order
 * Input Parameters:BinTreeNode<T>* subTree
 * Return Value:    void
 * Notes:           class external implementation of member functions
 */
template <typename T>
void BinaryTree<T>::postOrder(BinTreeNode<T>* subTree)
{
    if (subTree != NULL) {
        postOrder(subTree->leftChild);
        postOrder(subTree->rightChild);
        if (subTree == root)
            std::cout << subTree->data;
        else
            std::cout << subTree->data << " ";
    }
}


/*
 * Function Name:    levelOrder
 * Function:         Traverse a subtree in level-order
 * Input Parameters: BinTreeNode<T>* subTree
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename T>
void BinaryTree<T>::levelOrder(BinTreeNode<T>* subTree)
{
    if (subTree != NULL) {
        LinkedQueue<BinTreeNode<T>*> queue;
        queue.EnQueue(subTree);
        while (!queue.IsEmpty()) {
            BinTreeNode<T>* current;
            if (!queue.DeQueue(current))
                return;
            std::cout << current->data << " ";
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
    if (subTree == NULL || subTree->leftChild == NULL)
        return false;
    subTree->leftChild = new(std::nothrow) BinTreeNode<T>(item);
    if (subTree->leftChild = NULL)
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
    if (subTree == NULL || subTree->rightChild == NULL)
        return false;
    subTree->rightChild = new(std::nothrow) BinTreeNode<T>(item);
    if (subTree->rightChild = NULL)
    {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
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


class ExpressionTree :public BinaryTree<Expression> {
private:
    Stack<char> operatorStack;
    Stack<BinTreeNode< Expression>*> operandStack;
    int setPriority(char op);
    double calculateExpression(BinTreeNode<Expression>* node);
    void processOperatorStack();
public:
    void createExpressionTree(union Expression* expressionStruct);
    double calculate() { return calculateExpression(this->root); }
};

/*
 * Function Name:   setPriority
 * Function:        set the priority of the operator
 * Input Parameters:char op
 * Return Value:    int
 * Notes:           class external implementation of member functions
 */
int ExpressionTree::setPriority(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

/*
 * Function Name:   processOperatorStack
 * Function:        process the operator stack
 * Input Parameters:void
 * Return Value:    void
 * Notes:           class external implementation of member functions
 */
void ExpressionTree::processOperatorStack() {
    if (operatorStack.IsEmpty()) return; // Avoid popping if empty
    BinTreeNode <Expression>* tempExp;
    char op;
    operatorStack.Pop(op);

    BinTreeNode<Expression>* right = operandStack.Top();
    operandStack.Pop(tempExp);
    BinTreeNode<Expression>* left = operandStack.Top();
    operandStack.Pop(tempExp);

    BinTreeNode<Expression>* node = new(std::nothrow) BinTreeNode<Expression>();
    if (node == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    node->data.type = op;
    // node->data.value = 0.0;
    node->leftChild = left;
    node->rightChild = right;
    operandStack.Push(node); // Push the newly created node back
}

/*
 * Function Name:   createExpressionTree
 * Function:        create the expression tree
 * Input Parameters:union Expression* expressionStruct
 * Return Value:    void
 * Notes:           class external implementation of member functions
 */
void ExpressionTree::createExpressionTree(union Expression* expressionStruct) {
    for (int i = 0; expressionStruct[i].type != '\0' || expressionStruct[i].value != 0.0; i++) {
        char type = expressionStruct[i].type;
        double value = expressionStruct[i].value;

        if (type == '\0') { // Current node is an operand
            BinTreeNode<Expression>* node = new(std::nothrow) BinTreeNode<Expression>();
            if (node == NULL) {
                std::cerr << "Error: Memory allocation failed." << std::endl;
                exit(MEMORY_ALLOCATION_ERROR);
            }
            node->data.type = '\0';
            node->data.value = value;
            operandStack.Push(node);
        }
        else if (setPriority(type) > 0) { // Current node is an operator
            while (!operatorStack.IsEmpty() && setPriority(operatorStack.Top()) >= setPriority(type)) {
                processOperatorStack(); // Simplified operator processing...
            }
            operatorStack.Push(type);
        }
        else if (type == '(') {
            operatorStack.Push(type);
        }
        else if (type == ')') {
            char tmpOp;
            while (!operatorStack.IsEmpty() && operatorStack.Top() != '(') {
                processOperatorStack();
            }
            // Check for matching '('
            if (operatorStack.IsEmpty()) {
                std::cerr << "Error: Unmatched parenthesis." << std::endl;
                exit(MEMORY_ALLOCATION_ERROR);
            }
            operatorStack.Pop(tmpOp); // Pop the '('
        }
    }

    while (!operatorStack.IsEmpty()) {
        processOperatorStack();
    }

    operandStack.getTop(this->root); // Safe pull from stack to assign root
}


/*
 * Function Name:   calculateExpression
 * Function:        calculate the value of the expression
 * Input Parameters:BinTreeNode<Expression>* node
 * Return Value:    double
 * Notes:           class external implementation of member functions
 */
double ExpressionTree::calculateExpression(BinTreeNode<Expression>* node) {
    if (node == NULL)
        return 0;
    if (node->leftChild == NULL && node->rightChild == NULL)
        return node->data.value;
    double leftValue = calculateExpression(node->leftChild);
    double rightValue = calculateExpression(node->rightChild);
    switch (node->data.type) {
    case '+':
        return leftValue + rightValue;
    case '-':
        return leftValue - rightValue;
    case '*':
        return leftValue * rightValue;
    case '/':
        return leftValue / rightValue;
    default:
        return 0;
    }
}

/*
 * Function Name:   maeExpressionEmpty
 * Function:        make the expression empty
 * Input Parameters:struct Expression* expression
 * Return Value:    void
 */
void makeExpressionEmpty(union Expression* expression)
{
    for (int i = 0; i < EXPRESSION_MAX_LEN + 1; i++) {
        expression[i].type = '\0';
        expression[i].value = 0.0;
    }
}

/*
 * Function Name:   outputErrorInfo
 * Function:        output the imformation of error input
 * Input Parameters:const char* message
 * Return Value:    void
 */
void outputErrorInfo(const char* message) {
    std::cout << message << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/*
 * Function Name:   is_operator
 * Function:        check if the character is an operator
 * Input Parameters:char c
 * Return Value:    true / false
 */
bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

/*
 * Function Name:   is_parenthesis
 * Function:        check if the character is a parenthesis
 * Input Parameters:char c
 * Return Value:    true / false
 * Notes:
 */
bool isParenthesis(char c)
{
    return c == '(' || c == ')';
}


/*
 * Function Name:   isDigit
 * Function:        check if the character is a digit
 * Input Parameters:char c
 * Return Value:    true / false
 */
bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}


/*
 * Function Name:   isValidCharacter
 * Function:        check if the character is a valid character
 * Input Parameters:char ch
 * Return Value:    true / false
 */
bool isValidCharacter(char ch) {
    return isDigit(ch) || isParenthesis(ch) || isOperator(ch) || ch == '.' || ch == ' ';
}



/*
 * Function Name:   calculateOperand
 * Function:        calculate the value of the operand
 * Input Parameters:const char* operand
 * Return Value:    double
 */
double calculateOperand(const char* operand)
{
    double value = 0.0;
    double decimal_place = 1.0;
    bool is_decimal = false;
    while (*operand != ' ' && *operand != '\0') {
        if (isDigit(*operand)) {
            if (is_decimal) {
                decimal_place *= 0.1;
                value += (*operand - '0') * decimal_place;
            }
            else {
                value = value * 10 + (*operand - '0');
            }
        }
        else if (*operand == '.') {
            is_decimal = true;
        }
        operand++;
    }
    return value;
}


/*
 * Function Name:   inputExpression
 * Function:        input the expression from the user
 * Input Parameters:char* expression
 *                  struct Expression* expressionStruct
 * Return Value:    true / false
 */

bool inputExpression(char* expression, union Expression* expressionStruct) {
    std::cin.getline(expression, EXPRESSION_MAX_CHAR + 1);
    int Traversal = 0, operandLen = 0, expressionNum = 0, expressionLen = 0;
    bool lastIsOperator = false, lastIsOperand = false, lastIsDecimal = false;
    bool isNegative = false;//judge if the operand is negative
    while (expression[Traversal] != '\0') {//traverse the expression
        while (expression[Traversal] == ' ' || expression[Traversal] == '\n') {
            if (lastIsOperand) {
                if (isNegative)
                    expressionStruct[expressionNum].value = -calculateOperand(expression + Traversal - operandLen);
                else
                    expressionStruct[expressionNum].value = calculateOperand(expression + Traversal - operandLen);
                expressionNum++;
            }
            lastIsOperand = false;
            lastIsOperator = false;
            lastIsDecimal = false;
            isNegative = false;
            operandLen = 0;
            Traversal++;
        }
        if (expression[Traversal] == '\0')
            break;

        if (!isValidCharacter(expression[Traversal])) {
            outputErrorInfo(">>> 表达式中存在非法字符, 请重新输入!");
            return false;
        }

        if (isParenthesis(expression[Traversal]) || isOperator(expression[Traversal])) {//operator or parenthesis
            if (lastIsOperand || lastIsOperator) {
                outputErrorInfo(">>> 运算符,运算数中间要用空格隔开, 请重新输入!");
                return false;
            }
            else if (isDigit(expression[Traversal + 1])) {//if the next character is a digit, it is an operand
                if (expression[Traversal] == '+' || expression[Traversal] == '-') {
                    lastIsOperand = true;
                    lastIsOperator = false;
                    if (expression[Traversal] == '-')
                        isNegative = true;
                }
            }
            else {//store the operator
                expressionStruct[expressionNum].type = expression[Traversal];
                expressionNum++;
                lastIsOperator = true;
                lastIsOperand = false;
            }
            expressionLen++;
        }
        else {
            if (lastIsOperator) {
                outputErrorInfo(">>> 运算符,运算数中间要用空格隔开, 请重新输入!");
                return false;
            }
            else if (expression[Traversal] == '.') {//handle decimal point
                if (!lastIsOperand) {
                    outputErrorInfo(">>> 运算数不能以小数点开头,请重新输入!");
                    return false;
                }
                if (lastIsDecimal) {
                    outputErrorInfo(">>> 一个运算数只能有一个小数点,请重新输入!");
                    return false;
                }
                lastIsDecimal = true;
            }
            else if (isDigit(expression[Traversal])) {
                lastIsOperand = true;
            }
            expressionLen++;
            operandLen++;
        }
        if (operandLen > EXPRESSION_MAX_OPERAND_LENGTH) {
            outputErrorInfo(">>> 单个运算数不能超过8位数, 请重新输入!");
            return false;
        }
        Traversal++;
    }

    if (expressionLen > EXPRESSION_MAX_LEN) {
        outputErrorInfo(">>> 表达式长度超过20个字符,请重新输入!");
        return false;
    }
    else if (expressionLen == 0) {
        outputErrorInfo(">>> 表达式为空,请重新输入!");
        return false;
    }
    else {
        if (lastIsOperand) {//store the last operand
            if (isNegative)
                expressionStruct[expressionNum].value = -calculateOperand(expression + Traversal - operandLen);
            else
                expressionStruct[expressionNum].value = calculateOperand(expression + Traversal - operandLen);
            expressionStruct[expressionNum].type = '\0';
            expressionNum++;
        }
        expressionStruct[expressionNum].type = '\0';
        return true;
    }
}


/*
 * Function Name:   checkExpressionIsVaild
 * Function:        check if the expression is valid
 * Input Parameters:struct Expression* expressionStruct
 * Return Value:    true / false
 */
bool checkExpressionIsVaild(union Expression* expressionStruct) {
    Stack<char> expressionStack;
    bool lastIsOperand = false, lastIsOperator = false;
    for (int i = 0; expressionStruct[i].type != '\0' || expressionStruct[i].value != 0.0; i++) {//traverse the expression
        char ch = expressionStruct[i].type;

        if (i == 0 && isOperator(ch)) {
            std::cout << ">>> 表达式不能以运算符开始，请重新输入！" << std::endl;
            return false;
        }

        if (ch == '(') {
            if (expressionStruct[i + 1].type == ')') {
                std::cout << ">>> 表达式中存在空括号，请重新输入!" << std::endl;
                return false;
            }
            expressionStack.Push(ch);
            lastIsOperand = false;
            lastIsOperator = false;
        }
        else if (ch == ')') {
            char temp;
            expressionStack.getTop(temp);
            if (expressionStack.IsEmpty() || temp != '(') {
                std::cout << ">>> 表达式括号不匹配，请重新输入！" << std::endl;
                return false;
            }
            expressionStack.Pop(temp);
        }

        if (ch == '\0') {
            if (lastIsOperand) {
                std::cout << ">>> 表达式中每个运算符前后必须连接数字，请重新输入！" << std::endl;
                return false;
            }
            lastIsOperand = true;
            lastIsOperator = false;
        }
        else if (isOperator(ch)) {
            if (lastIsOperator) {
                std::cout << ">>> 表达式中每个运算符前后必须连接数字，请重新输入！" << std::endl;
                return false;
            }
            lastIsOperand = false;
            lastIsOperator = true;
        }

        if (expressionStruct[i].type == '/' && std::fabs(expressionStruct[i + 1].value) < CALCULATE_ERROR) {
            std::cout << ">>> 除数不能为0，请重新输入!" << std::endl;
            return false;
        }
    }
    if (!expressionStack.IsEmpty()) {
        std::cout << ">>> 表达式括号不匹配，请重新输入！" << std::endl;
        return false;
    }
    if (lastIsOperator) {
        std::cout << ">>> 表达式不能以运算符结尾，请重新输入！" << std::endl;
        return false;
    }
    return true;
}



/*
 * Function Name:   outputStart
 * Function:        output the start of the program
 * Input Parameters:void
 * Return Value:    void
 */
void outputStart()
{
    std::cout << "+----------------------------+" << std::endl;
    std::cout << "|         表达式转换         |" << std::endl;
    std::cout << "|   expression conversion    |" << std::endl;
    std::cout << "+----------------------------+" << std::endl;
    std::cout << ">>> 表达式输入要求" << std::endl;
    std::cout << "    [1] 输入在一行中以空格分隔不同对象的中缀表达式" << std::endl;
    std::cout << "    [2] 表达式只能包含数字,+,-,*,/,.,以及左右括号" << std::endl;
    std::cout << "    [3] 表达式不超过" << EXPRESSION_MAX_CHAR << "个字符(不包括空格), 单个运算数不能超过8位数" << std::endl;
    std::cout << "    [4] 表达式中的括号嵌套匹配" << std::endl;
    std::cout << "    [5] 表达式中每个运算符前后必须连接数字，\"-n\"请改写成\"0-n\" " << std::endl;
    std::cout << "    [6] 表达式请在一行中输入，按回车键表示输入结束" << std::endl << std::endl;
}

/*
 * Function Name:   main
 * Function:        main function
 * Return Value:    0
 */
int main()
{
    outputStart();
    char expression[EXPRESSION_MAX_CHAR + 1];
    union Expression expressionSimplified[EXPRESSION_MAX_LEN + 1];

    do {
        std::cout << ">>> 请输入表达式：";
        makeExpressionEmpty(expressionSimplified);
    } while (!inputExpression(expression, expressionSimplified) || !checkExpressionIsVaild(expressionSimplified));


    ExpressionTree expressionTree;
    expressionTree.createExpressionTree(expressionSimplified);
    std::cout << std::endl;
    expressionTree.createExpressionTree(expressionSimplified);
    std::cout << ">>> 表达式运算结果          :" << expressionTree.calculate() << std::endl;
    std::cout << ">>> 前缀表达式(波兰表达式)  :";
    expressionTree.preOrderOutput(expressionTree.getRoot());
    //std::cout << "#";
    std::cout << std::endl;
    std::cout << ">>> 中缀表达式              :" << expression << std::endl;

    std::cout << ">>> 后缀表达式(逆波兰表达式):";
    expressionTree.postOrderOutput(expressionTree.getRoot());
    //std::cout << "#";
    std::cout << std::endl;

    /*wait for user input to quit*/
    std::cout << "Press Enter to Quit" << std::endl;
    while (_getch() != '\r')
        continue;
    return 0;
}
