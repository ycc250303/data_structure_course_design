#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <climits>
#include<conio.h>

#define MAZE_WALL 0   
#define MAZE_BLANK 1
#define MAZE_PATH 2
#define MAZE_START 3
#define MAZE_END 4

#define MAX_SIZE 49
#define MIN_SIZE 7

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define MEMORY_ALLOCATION_ERROR -1
 
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
		std::cerr << "Ö´ÐÐ´íÎó:ÄÚ´æ·ÖÅäÊ§°Ü£¡" << std::endl;
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
		std::cerr << "Ö´ÐÐ´íÎó:ÄÚ´æ·ÖÅäÊ§°Ü£¡" << std::endl;
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
		std::cerr << "Ö´ÐÐ´íÎó:ÄÚ´æ·ÖÅäÊ§°Ü£¡" << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	last = first;
	LinkNode<T>* srcptr = L.first->link;
	LinkNode<T>* dstptr = first;
	while (srcptr != NULL)
	{
		dstptr->link = new(std::nothrow) LinkNode<T>(srcptr->data);
		if (dstptr->link == NULL) {
			std::cerr << "Ö´ÐÐ´íÎó:ÄÚ´æ·ÖÅäÊ§°Ü£¡" << std::endl;
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
		std::cerr << "Ö´ÐÐ´íÎó:ÄÚ´æ·ÖÅäÊ§°Ü£¡" << std::endl;
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
		std::cerr << "Ö´ÐÐ´íÎó:ÄÚ´æ·ÖÅäÊ§°Ü£¡" << std::endl;
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
			std::cerr << "Ö´ÐÐ´íÎó:ÄÚ´æ·ÖÅäÊ§°Ü£¡" << std::endl;
			exit(MEMORY_ALLOCATION_ERROR);
		}
		dstptr = dstptr->link;
		dstptr->link = newNode;
		srcptr = srcptr->link;
	}
	last = dstptr;
	return *this;
}

template <typename T>
class Stack {
private:
    LinkNode<T>* top;
public:
    Stack() : top(NULL) {}
    ~Stack() { makeEmpty(); }
    void push(T item);
    bool pop(T& item);
    bool getTop(T& item) const;
    bool isEmpty() const { return top == NULL; }
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
void Stack<T>::push(T item) {
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
bool Stack<T>::pop(T& item) {
    if (isEmpty())
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
    if (isEmpty())
        return false;
    item = top->data;
    return true;
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
    while (!isEmpty()) {
        LinkNode<T>* temp = top;
        top = top->link;
        delete temp;
    }
}

/*create a point*/
struct Point {
    int x;
    int y;
    int type = MAZE_BLANK;
	int direction = 0;
    Point(int a = 0, int b = 0, int t = MAZE_BLANK, int d = 0) :x(a), y(b), type(t), direction(d) {}
};

/*create a maze*/
class Maze {
private:
	int** mazeMap;
	int** mazeMapMark;
    int row;
    int col;
    int startRow;
    int startCol;
    int endRow ;
    int endCol ;
    int currentRow;
    int currentCol;
	List<Point> blankPointsList;
	Stack<Point> path;
	Point move[4] = { {0,-1,MAZE_BLANK,LEFT}, {0,1,MAZE_BLANK,RIGHT}, {-1,0,MAZE_BLANK,UP}, {1,0,MAZE_BLANK,DOWN} };
	bool isVaildPoint(int x, int y);
	void findNearWalls();
    void createMaze();
public:
    Maze(int _row, int _col, int _startRow , int _startCol, int _endRow, int _endCol);
    ~Maze() { delete[] mazeMap,delete[] mazeMapMark; }
    void outputMaze();
	void outputPath();
	bool recursive();
};



/*
 * Function Name:   Maze
 * Function:        the constructor of the Maze class
 * Input Parameters:int _row
 *					int _col
 *					int _startRow
 *					int _startCol
 *					int _endRow
 *					int _endCol
 * Return Value:    void
 * Notes:           Class external implementation of member functions
 */
Maze::Maze(int _row, int _col, int _startRow, int _startCol, int _endRow, int _endCol) {
    row = _row;
    col = _col;
    startRow = _startRow;
    startCol = _startCol;
    endRow = _endRow;
    endCol = _endCol;
    currentRow = startRow;
    currentCol = startCol;
    mazeMap = new(std::nothrow) int* [row];
	mazeMapMark = new(std::nothrow) int* [row];
    if (mazeMap == NULL||mazeMapMark == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    for (int i = 0; i < row; i++) {
        mazeMap[i] = new(std::nothrow) int[col];
		mazeMapMark[i] = new(std::nothrow) int[col];
        if (mazeMap[i] == NULL||mazeMapMark[i] == NULL) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
    }
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			mazeMap[i][j] = MAZE_WALL;
    createMaze();
	mazeMap[startRow][startCol] = MAZE_START;
	mazeMap[endRow][endCol] = MAZE_END;
	currentRow = startRow;
	currentCol = startCol;
}

/*
 * Function Name:	isVaildPoint
 * Function:		check if the point is vaild
 * Input Parameters:int x
 *					int y
 * Return Value:	true / false
 * Notes:           Class external implementation of member functions
 */
bool Maze::isVaildPoint(int x, int y) {
	return x >= 0 && x < row && y >= 0 && y < col;
}

/*
 * Function Name:	findNearWalls
 * Function:		find the near walls of the current point
 * Input Parameters:void
 * Return Value:	void
 * Notes:           Class external implementation of member functions
 */
void Maze::findNearWalls() {
	if (currentRow < row - 1 && mazeMap[currentRow + 1][currentCol] == MAZE_WALL) {
		Point wallPoint = { currentRow + 1, currentCol, MAZE_WALL ,DOWN };
		blankPointsList.insert(blankPointsList.getLength(), wallPoint);
	}
	if (currentRow > 1 && mazeMap[currentRow - 1][currentCol] == MAZE_WALL) {
		Point wallPoint = { currentRow - 1, currentCol, MAZE_WALL ,UP };
		blankPointsList.insert(blankPointsList.getLength(), wallPoint);
	}
	if (currentCol < col - 1 && mazeMap[currentRow][currentCol + 1] == MAZE_WALL) {
		Point wallPoint = { currentRow, currentCol + 1, MAZE_WALL ,RIGHT };
		blankPointsList.insert(blankPointsList.getLength(), wallPoint);
	}
	if (currentCol > 1 && mazeMap[currentRow][currentCol - 1] == MAZE_WALL) {
		Point wallPoint = { currentRow, currentCol - 1, MAZE_WALL ,LEFT };
		blankPointsList.insert(blankPointsList.getLength(), wallPoint);
	}
}


/*
 * Function Name:	createMaze
 * Function:		create a maze
 * Input Parameters:void
 * Return Value:	void
 * Notes:           Class external implementation of member functions
 */
void Maze::createMaze() {
	findNearWalls();
	while (!blankPointsList.isEmpty()) {
		int index = rand() % blankPointsList.getLength()+1;
		Point currentPoint = blankPointsList.locate(index)->data;
		currentRow = currentPoint.x;
		currentCol = currentPoint.y;
		if (currentPoint.direction == UP)
			currentRow--;
		else if (currentPoint.direction == DOWN)
			currentRow++;
		else if (currentPoint.direction == LEFT)
			currentCol--;
		else if (currentPoint.direction == RIGHT)
			currentCol++;
		if ( isVaildPoint(currentRow, currentCol)&&mazeMap[currentRow][currentCol] == MAZE_WALL) {
			mazeMap[currentRow][currentCol] = MAZE_BLANK;
			mazeMap[currentPoint.x][currentPoint.y] = MAZE_BLANK;
			findNearWalls();
		}
		blankPointsList.remove(index, currentPoint);
	}
}

/*
 * Function Name:	outputMaze
 * Function:		output the maze
 * Input Parameters:void
 * Return Value:	void
 * Notes:           Class external implementation of member functions
 */
void Maze::outputMaze() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
			if (mazeMap[i][j] == MAZE_BLANK)
				std::cout << "  ";
			else if (mazeMap[i][j] == MAZE_WALL)
				std::cout << "¡ö";
			else if (mazeMap[i][j] == MAZE_PATH)
				std::cout << "¡õ";
            else if (mazeMap[i][j] == MAZE_START)
                std::cout << "Ê¼";
            else if (mazeMap[i][j] == MAZE_END)
                std::cout << "ÖÕ";
        }
        std::cout << std::endl;
    }
	std::cout << std::endl;
}

/*
 * Function Name:	outputPath
 * Function:		output the path
 * Input Parameters:void
 * Return Value:	void
 * Notes:           Class external implementation of member functions
 */
void Maze::outputPath() {
	std::cout << "Â·¾¶: ";
	std::cout << "(" << startRow << "," << startCol << ")->";
	while (!path.isEmpty()) {
		Point currentPoint;
		path.pop(currentPoint);
		std::cout << "(" << currentPoint.x << "," << currentPoint.y << ")->";
	}
	std::cout << "(" << endRow << "," << endCol << ")";
}

/*
 * Function Name:	inputMazeSize
 * Function:		intput the size of the maze
 * Input Parameters:const char* prompt
 *					int minSize
 *					int maxSize
 * Return Value:	int
 */
int inputMazeSize(const char* prompt, int minSize = MIN_SIZE, int maxSize = MAX_SIZE) {
	double size;
	std::cout << "ÇëÊäÈë" << prompt << "ÕûÊý·¶Î§[" << minSize << ',' << maxSize << "]:";
	std::cin >> size;
	if (std::cin.fail()||static_cast<int>(size)!= size) {
		std::cout << "ÊäÈë²»ÊÇÕûÊý,ÇëÖØÐÂÊäÈë!" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return 0;
	}
	else if (size<minSize || size>maxSize) {
		std::cout << "ÊäÈë³¬³ö·¶Î§[" << minSize << ',' << maxSize << "],ÇëÖØÐÂÊäÈë!" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return 0;
	}
	return static_cast<int>(size);
}

/*
 * Function Name:	recursive
 * Function:		recursive function to find the path
 * Input Parameters:void
 * Return Value:	true / false
 * Notes:           Class external implementation of member functions
 */
bool Maze::recursive() {
	if (currentRow == endRow && currentCol == endCol)
		return true;
	mazeMapMark[currentRow][currentCol] = MAZE_PATH;

	/*try each direction*/
	for (int count = 0; count < 4; count++) {
		 int nextPointRow = currentRow + move[count].x;
		 int nextPointCol = currentCol + move[count].y;
		 /*check if the next point is vaild and not visited*/
		if (isVaildPoint(nextPointRow, nextPointCol) && mazeMap[nextPointRow][nextPointCol] != MAZE_WALL && mazeMapMark[nextPointRow][nextPointCol] != MAZE_PATH) {
			mazeMapMark[nextPointRow][nextPointCol] = MAZE_PATH;
			currentRow = nextPointRow;
			currentCol = nextPointCol;
			/*if the next point is the end point, return true*/
			if (recursive()) {	
				if(mazeMap[currentRow][currentCol] != MAZE_END){
					path.push(Point(currentRow, currentCol, mazeMap[currentRow][currentCol]));
					mazeMap[currentRow][currentCol] = MAZE_PATH;
				}
				/*backtrack*/
				currentRow = nextPointRow - move[count].x;
				currentCol = nextPointCol - move[count].y;
				return true;
			}
			else {
				/*backtrack*/
				currentRow = nextPointRow - move[count].x;
				currentCol = nextPointCol - move[count].y;
			}
		}
	}
	return false;
}

/*
 * Function Name:	main
 * Function:		main function
 * Return Value:	0
 */
int main() {
	/*seed the random number generator*/
    srand(static_cast<unsigned int>(time(0))); 
	std::cout << "+--------------------+" << std::endl;
	std::cout << "|   ÓÂ´³ÃÔ¹¬ÓÎÏ·     |" << std::endl;
	std::cout << "|     Maze Game      |" << std::endl;
	std::cout << "+--------------------+" << std::endl;
	int row = 0, col = 0;
	do {
		row = inputMazeSize("ÃÔ¹¬ÐÐÊý");
		col = inputMazeSize("ÃÔ¹¬ÁÐÊý");
	} while (!(row && col));
	Maze maze(row, col, 1, 1, row - 2, col - 2);
	std::cout << std::endl<<"ÃÔ¹¬µØÍ¼:"<<std::endl<<std::endl;
    maze.outputMaze();
	
	if (maze.recursive()){
		maze.outputMaze();
		/*maze.
			();*/
	}
	else {
		std::cout << "Î´ÕÒµ½ÃÔ¹¬Â·¾¶!" << std::endl;
	}
	
	std::cout << std::endl;
	/*wait for user input to quit*/
	std::cout << "Press Enter to Quit" << std::endl;
	while (_getch() != '\r')
		continue;
    return 0;
}


