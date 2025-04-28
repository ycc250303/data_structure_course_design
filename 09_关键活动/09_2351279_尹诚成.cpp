#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <limits>

#define MEMORY_ALLOCATION_ERROR -1
#define MAX_NUM_OF_ACTIVITY_NODE 20
#define MAX_NUM_OF_ACTIVITY 100
#define MAX_TIME 256 

/*define the struct of Vertex and Edge*/
template<typename T, typename E>
struct Edge {
	int otherVertex;
	E cost;
	Edge<T, E>* link;
	Edge() :otherVertex(-1), cost(0), link(NULL) {}
	Edge(int num, E weight) :otherVertex(num), cost(weight), link(NULL) {}
};

template<typename T, typename E>
struct Vertex {
	T data;
	Edge<T, E>* firstEdge;
};

/*define the class of Graph*/
template<typename T, typename E>
class Graphlnk {
protected:
	Vertex<T,E>* nodeTable;
	int numVertices;
	int numEdges;
public:
	Graphlnk(int n);	
	~Graphlnk();
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v1,int v2);
	int getWeight(int v1, int v2);
	bool insertVertex(T vertex);
	bool insertEdge(int v1, int v2, E weight);
};


/*
 * Function Name:	Graphlnk
 * Function:		the constructor of Graphlnk
 * Input Parameters:int n
 * Return Value:	void
 * Notes:			Class external implementation of member functions
 */
template<typename T, typename E>
Graphlnk<T, E>::Graphlnk(int n) {
	numVertices = n;
	numEdges = 0;
	nodeTable = new(std::nothrow) Vertex<T, E>[numVertices];
	if (nodeTable == NULL) {
		std::cerr << "Memory allocation failed in constructor." << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	for (int i = 0; i < numVertices; i++) {
		nodeTable[i].data = i;
		nodeTable[i].firstEdge = NULL;
	}
}


/*
 * Function Name:	~Graphlnk
 * Function:		the destructor of Graphlnk
 * Input Parameters:void
 * Return Value:	void
 * Notes:			Class external implementation of member functions
 */
template<typename T, typename E>
Graphlnk<T, E>::~Graphlnk() {
	for (int i = 0; i < numVertices; i++) {
		Edge<T, E>* current = nodeTable[i].firstEdge;
		while (current != NULL) {
			nodeTable[i].firstEdge = current->link;
			delete current;
			current = nodeTable[i].firstEdge;
		}
	}
}

/*
 * Function Name:	getFirstNeighbor
 * Function:		get the first neighbor of vertex v
 * Input Parameters:int v
 * Return Value:	int
 * Notes:			Class external implementation of member functions
 */
template<typename T, typename E>
int Graphlnk<T, E>::getFirstNeighbor(int v) {
	if (0 <= v && v < numVertices) {
		Edge<T, E>* p = nodeTable[v].firstEdge;
		if (p != NULL)
			return p->otherVertex;
	}
	return -1;
}

/*
 * Function Name:	getNextNeighbor
 * Function:		get the next neighbor of vertex v1 and v2
 * Input Parameters:int v1
 *					int v2
 * Return Value:	int
 * Notes:			Class external implementation of member functions
 */
template<typename T, typename E>
int Graphlnk<T, E>::getNextNeighbor(int v1,int v2) {
	if ((0 <= v1 && v1 < numVertices)&& (0 <= v2 && v2 < numVertices)) {
		Edge<T, E>* p = nodeTable[v1].firstEdge;
		while (p != NULL && p->otherVertex != v2)
			p = p->link;
		if (p != NULL && p->link != NULL)
			return p->link->otherVertex;
	}
	return -1;
}

template<typename T, typename E>
int Graphlnk<T, E>::getWeight(int v1, int v2) {
	if ((0 <= v1 && v1 < numVertices) && (0 <= v2 && v2 < numVertices)) {
		Edge<T, E>* p = nodeTable[v1].firstEdge;
		while (p != NULL && p->otherVertex != v2)
			p = p->link;
		if (p != NULL)
			return p->cost;
	}
	return 0;
}
/*
 * Function Name:	insertVertex
 * Function:		insert a new vertex into the graph
 * Input Parameters:T vertex
 * Return Value:	true / false
 * Notes:			Class external implementation of member functions
 */
template<typename T, typename E>
bool Graphlnk<T, E>::insertVertex(T vertex) {
	Vertex<T, E>* newVertex = new(std::nothrow)Vertex<T, E>;
	if (newVertex == NULL) {
		std::cerr << "Memory allocation failed in insertVertex." << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	nodeTable[numVertices] = newVertex;
	newVertex->data = vertex;
	newVertex->firstEdge = NULL;
	numVertices++;
	return true;
}

/*
 * Function Name:	insertEdge
 * Function:		insert a new edge into the graph
 * Input Parameters:int v1
 *					int v2
 *					E weight
 * Return Value:	true / false
 * Notes:			Class external implementation of member functions
 */
template<typename T, typename E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight) {
	if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices)
		return false;
	Edge<T, E>* current = nodeTable[v1].firstEdge;
	Edge<T, E>* newEdge1 = new(std::nothrow)Edge<T, E>;
	if (newEdge1 == NULL) {
		std::cerr << "Memory allocation failed in insertEdge." << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	newEdge1->otherVertex = v2;
	newEdge1->cost = weight;
	if (current != NULL) {
		while (current->link != NULL && current->otherVertex != v2) {
			current = current->link;
		}
		if (current->link != NULL || current->otherVertex == v2) {
			delete newEdge1;
			return false;
		}
		newEdge1->link = current->link;
		current->link = newEdge1;
	}
	else {
		newEdge1->link = NULL;
		nodeTable[v1].firstEdge = newEdge1;
	}
	numEdges++;
	return true;
}


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

/*define the struct of KeyActivity*/
struct ActivityNode {
	int vertex1;
	int vertex2;
	int day;
	friend std::istream& operator >>(std::istream& in, ActivityNode&k);
	friend std::ostream& operator <<(std::ostream& out, ActivityNode k);
};

/*
 * Function Name:	operator >>
 * Function:		the input operator of KeyActivity
 * Input Parameters:std::istream& in
 *					KeyActivity &k
 * Return Value:	in
 */
std::istream& operator >>(std::istream& in, ActivityNode&k) {	
	while (true) {
		in >> k.vertex1 >> k.vertex2 >> k.day;
		if (in.fail() ||
			static_cast<int>(k.vertex1) != k.vertex1 ||
			static_cast<int>(k.vertex2) != k.vertex2 ||
			static_cast<int>(k.day) != k.day) {
			std::cerr << "输入不是整数,请重新输入!" << std::endl;
			in.clear();
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
			break;
	}
	return in;
}

/*
 * Function Name:	operator <<
 * Function:		the output operator of KeyActivity
 * Input Parameters:std::ostream& out
 *					KeyActivity k
 * Return Value:	out
 */
std::ostream& operator <<(std::ostream& out, ActivityNode k) {
	out << k.vertex1 + 1 << "->" << k.vertex2+1;
	return out;
}


/*define the class of KeyActivites*/
template<typename T, typename E>
class KeyActivites :public Graphlnk<T,E> {
private:
	ActivityNode *activity;
	ActivityNode* keyActivity;
	int* topologicalVertex;
	int keyActivityCount = 0;
	int totalTime = 0;
public:
	KeyActivites() : Graphlnk<T, E>(0), activity(NULL),keyActivity(NULL), topologicalVertex(NULL) {};
	KeyActivites(int N, int M);
	~KeyActivites() { delete[] keyActivity; delete[] activity; delete[] topologicalVertex; }
	bool topologicalSort();
	void criticalActivity();
	void outputCriticalActivity();
};

/*
 * Function Name:	KeyActivites
 * Function:		the constructor of KeyActivites
 * Input Parameters:int N
 *					int M
 * Return Value:	void
 * Notes:			Class external implementation of member functions
 */
template<typename T, typename E>
KeyActivites<T,E>::KeyActivites(int N,int M) :Graphlnk<T, E>(N), activity(NULL), keyActivity(NULL), topologicalVertex(NULL) {
	this->numVertices = N;
	activity = new(std::nothrow) ActivityNode[M];
	if (activity == NULL) {
		std::cerr << "Memory allocation failed in insertEdge." << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	/*read the input data*/
	std::cout << std::endl << ">>> 请依次输入任务开始和完成的交接点编号[整数范围1-" << this->numVertices <<
		"]\n    以及完成该任务所需的时间[整数范围1 - " << MAX_TIME << "]\n    整数间用空格分隔:" << std::endl;
	for (int i = 0; i < M; i++) {
		while (true) {
			std::cout << "请输入第" << i + 1 << "个任务的相关信息:";
			std::cin >> activity[i];
			if ((activity[i].vertex1 <= 0 || activity[i].vertex1 > this->numVertices) ||
				(activity[i].vertex2 <= 0 || activity[i].vertex2 > this->numVertices) ||
				activity[i].vertex1 == activity[i].vertex2) {
				std::cerr << "任务交接点编号输入有误,请重新输入!" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else if (activity[i].day <= 0 || activity[i].day > MAX_TIME) {
				std::cerr << "任务完成时间超出范围[1-" << MAX_TIME << "],请重新输入!" << std::endl;
			}
			else {
				this->insertEdge(activity[i].vertex1 - 1, activity[i].vertex2 - 1, activity[i].day);
				break;
			}		
		}
	}
}

/*
 * Function Name:	topologicalSort
 * Function:		the topological sort algorithm
 * Input Parameters:void
 * Return Value:	true / false
 * Notes:			Class external implementation of member functions
 */
template<typename T, typename E>
bool KeyActivites<T, E>::topologicalSort() {
	int top = -1;
	int n = this->numVertices;
	int* count = new(std::nothrow) int[n];
	topologicalVertex = new(std::nothrow) int[n];
	if (count == NULL || topologicalVertex == NULL) {
		std::cerr << "Memory allocation failed in insertEdge." << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	/*statistics the in-degree of each vertex*/
	for (int i = 0; i < n; i++)
		count[i] = 0;
	for (int i = 0; i < n; i++) {
		int j = this->getFirstNeighbor(i);
		while (j != -1) {
			count[j]++;
			j = this->getNextNeighbor(i, j);
		}
	}
	/*push the vertex with in-degree 0 into the stack*/
	for (int i = 0; i < n; i++) {
		if (count[i] == 0) {
			count[i] = top;
			top = i;
		}
	}
	/*sort the vertices by the topological order*/
	for (int i = 0; i < n; i++) {
		if (top == -1) {
			return false;
		}
		else {
			int v = top;
			top = count[top];
			topologicalVertex[i] = v;
			int w = this->getFirstNeighbor(v);
			while (w != -1) {
				if (--count[w] == 0) {
					count[w] = top;
					top = w;
				}
				w = this->getNextNeighbor(v, w);
			}
		}
	}
	std::cout << std::endl;
	delete[] count;
	return true;
}

/*
 * Function Name:   criticalActivity
 * Function:		statistics the critical activites in all activites
 * Input Parameters:void 
 * Return Value:    void
 */
template<typename T, typename E>
void KeyActivites<T, E>::criticalActivity() {
	/*initailize*/
	int n = this->numVertices, m = this->numEdges;
	int top = -1;
	keyActivity = new(std::nothrow) ActivityNode[m];
	if (keyActivity == NULL) {
		std::cerr << "Memory allocation failed in criticalActivity." << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	int* eventEarlyTime = new(std::nothrow) int[n], * eventLateTime = new(std::nothrow) int[n];
	int* activityEarlyTime = new(std::nothrow) int[m], * activityLateTime = new(std::nothrow) int[m];
	if (eventEarlyTime == NULL || eventLateTime == NULL || activityEarlyTime == NULL || activityLateTime == NULL) {
		std::cerr << "Memory allocation failed in criticalActivity." << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	/*calculate the early time of each event*/
	for (int i = 0; i < n; i++)
		eventEarlyTime[i] = 0;
	for (int i = 0; i < n; i++) {
		int currentEvent = topologicalVertex[i];//u
		int nextEvent = this->getFirstNeighbor(currentEvent);//v
		while (nextEvent != -1) {
			int day = this->getWeight(currentEvent, nextEvent);//w
			if (eventEarlyTime[currentEvent] + day > eventEarlyTime[nextEvent])
				eventEarlyTime[nextEvent] = eventEarlyTime[currentEvent] + day;
			nextEvent = this->getNextNeighbor(currentEvent, nextEvent);
		}
	}
	/*calculate the late time of each event*/
	for (int i = 0; i < n; i++)
		eventLateTime[i] = eventEarlyTime[topologicalVertex[n - 1]];
	for (int i = n - 1; i >= 0; i--) {
		int currentEvent = topologicalVertex[i];//v
		int nextEvent = this->getFirstNeighbor(currentEvent);//k
		while (nextEvent != -1) {
			int day = this->getWeight(currentEvent, nextEvent);//w
			if (eventLateTime[nextEvent] - day < eventLateTime[currentEvent])
				eventLateTime[currentEvent] = eventLateTime[nextEvent] - day;
			nextEvent = this->getNextNeighbor(currentEvent, nextEvent);
		}
	}
	/*calculate the early and late time of activity*/
	int activityIndex = 0;
	for (int i = 0; i < n; i++) {
		int currentEvent = this->getFirstNeighbor(i);//u
		while (currentEvent != -1) {
			int day = this->getWeight(i, currentEvent);//w
			activityEarlyTime[activityIndex] = eventEarlyTime[i];
			activityLateTime[activityIndex] = eventLateTime[currentEvent] - day;
			if (activityEarlyTime[activityIndex] == activityLateTime[activityIndex]) 
				keyActivity[keyActivityCount++] = { i,currentEvent,day };
			if (activityIndex + 1 != m)
				activityIndex++;
			currentEvent = this->getNextNeighbor(i, currentEvent);
		}
	}
	totalTime = eventLateTime[n - 1];
	delete []eventEarlyTime;
	delete []eventLateTime;
	delete []activityEarlyTime;
	delete []activityLateTime;
}


/*
 * Function Name:   outputCriticalActivity
 * Function:		output the critical activities in all activites
 * Input Parameters:void
 * Return Value:    void
 */
template<typename T, typename E>
void KeyActivites<T, E>::outputCriticalActivity() {
	/*create a stack for critical activity*/
	ActivityNode* activityStack = new(std::nothrow) ActivityNode[keyActivityCount];
	if (activityStack == NULL) {
		std::cerr << "Memory allocation failed in outputCriticalPath!" << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	int top = -1;
	/*output the critical activities*/
	std::cout << ">>> 整个项目需要的最短时间为" << totalTime << "天" << std::endl << std::endl;
	std::cout << ">>> 项目中的关键活动为:" << std::endl;
	for (int i = 0; i < keyActivityCount; i++) {
		if (((i != keyActivityCount - 1) && (keyActivity[i].vertex1 < keyActivity[i + 1].vertex1)) || i == keyActivityCount - 1) {
			std::cout << keyActivity[i] << std::endl;
			while (top != -1) {
				std::cout << activityStack[top] << std::endl;
				top--;
			}
		}
		else 
			activityStack[++top] = keyActivity[i];
	}
	delete[]activityStack;
}

/*
 * Function Name:	main
 * Function:		main function
 * Return Value:	0
 */
int main() {
	std::cout << "+----------------------+" << std::endl;
	std::cout << "|       关键活动       |" << std::endl;
	std::cout << "|    Key Activities    |" << std::endl;
	std::cout << "+----------------------+" << std::endl;

	int N = inputInteger(1, MAX_NUM_OF_ACTIVITY_NODE, "任务交接点的数目");
	int maxM = (N * (N - 1) / 2) > MAX_NUM_OF_ACTIVITY ? MAX_NUM_OF_ACTIVITY : (N * (N - 1) / 2);
	int M = inputInteger(N - 1, maxM, "任务的数量");
	
	KeyActivites<int, int> KeyActivity(N, M);
	if (KeyActivity.topologicalSort()) {
		KeyActivity.criticalActivity();
		KeyActivity.outputCriticalActivity();
	}
	else {
		std::cout << 0 << std::endl;
		std::cout << "不可行的方案测试!" << std::endl;
	}
	return 0;
}