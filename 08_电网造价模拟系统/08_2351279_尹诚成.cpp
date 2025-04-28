#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <limits>
#include <conio.h>

#define MAX_VERTEX_NUM 26
#define MAX_COST INT_MAX
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
            std::cout << "请输入" << prompt << "[整数范围" << minNum << "-" << maxNum << "]:";
        std::cin >> num;
        if (std::cin.fail()||static_cast<int>(num)!=num) {
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

/*define the struct of ClosestEdge and MinTreeNode*/
struct ClosestEdge {
    int lowestVertex;
    int lowestCost;
};

struct MinTreeNode {
    char vertex1, vertex2;
    int cost;
};

/*define the class of PowerGrid*/
class PowerGrid {
private:
    int** costMatrix;
    int vertexNum;
    int edgeNum;
    int maxEdgeNum;
    MinTreeNode* minSpanningTree;
    ClosestEdge* closestEdges;
public:
    PowerGrid(int V);
    ~PowerGrid();
    bool insertEdge(int v1, int v2, int cost);
    void createMinimalSpanningTree(int startNode);
    void printMinimalSpanningTree();
};

/*
 * Function Name:   PowerGrid
 * Function:        the constructor of the PowerGrid class
 * Input Parameters:int V
 * Return Value:    void
 * Notes:           Class external implementation of member functions
 */
PowerGrid::PowerGrid(int V) {
    /*cost matrix initialization*/
    vertexNum = V;
    maxEdgeNum = V * (V - 1) / 2;

    costMatrix = new(std::nothrow) int* [vertexNum];
    if (costMatrix == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;   
        exit(MEMORY_ALLOCATION_ERROR);
    }

    for (int i = 0; i < vertexNum; i++) {
        costMatrix[i] = new(std::nothrow) int[vertexNum];
        if (costMatrix[i] == NULL) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
        for (int j = 0; j < vertexNum; j++) {
            costMatrix[i][j] = 0;
        }
    }
    std::cout << std::endl;
    std::cout << ">>> 电网节点";
    for (int i = 0; i < vertexNum; i++) {
        std::cout << static_cast<char>(i + 'A') << " ";
    }
    std::cout << "创建成功!" << std::endl << std::endl;

    /*input edge distance*/
    std::cout << ">>> 请输入电网各节点之间的距离" << std::endl;
    int index1 = 0,index2 = 1;
    while (edgeNum < maxEdgeNum) {
        for (index2; index2 < vertexNum; index2++) {
            char temp[64];
            sprintf(temp, "请输入电网节点%c到%c的边的距离", static_cast<char>(index1 + 'A'), static_cast<char>(index2 + 'A'));
            //std::cout << "请输入电网节点" << static_cast<char>(index1 + 'A') << "到" << static_cast<char>(index2 + 'A') << "的边的距离[整数范围1-" << MAX_COST << "]:";
            int distance = inputInteger(1, MAX_COST,temp);
            insertEdge(index1, index2, distance);
        }
        index1++;
        index2 = index1+1;
    }
}

PowerGrid::~PowerGrid() {
    for (int i = 0; i < vertexNum; i++) {
        delete[]costMatrix[i];
    }
    delete[]costMatrix;
    delete[]minSpanningTree;
    delete[]closestEdges;
}

/*
 * Function Name:   insertEdge
 * Function:        insert an edge into the cost matrix
 * Input Parameters:int v1
 *                  int v2
 *                  int cost
 * Return Value:    true / false
 * Notes:           Class external implementation of member functions
 */
bool PowerGrid::insertEdge(int v1, int v2, int cost) {
    if (v1 < 0 || v1 >= vertexNum || v2 < 0 || v2 >= vertexNum || cost < 0 || cost > MAX_COST) 
        return false;
    if (costMatrix[v1][v2] == 0 || costMatrix[v1][v2] == MAX_COST)
        edgeNum++;
    costMatrix[v1][v2] = costMatrix[v2][v1] = cost;
    return true;
}

/*
 * Function Name:   createMinimalSpanningTree
 * Function:        create a minimal spanning tree using Prim algorithm
 * Input Parameters:int startNode
 * Return Value:    void
 * Notes:           Class external implementation of member functions
 */
void PowerGrid::createMinimalSpanningTree(int startNode) {
    closestEdges = new(std::nothrow) ClosestEdge[vertexNum];
    minSpanningTree = new(std::nothrow) MinTreeNode[edgeNum];
    if (closestEdges == NULL||minSpanningTree == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    /*initialize closestEdges*/
    std::cout << ">>> 生成 Prim 最小生成树..." << std::endl << std::endl;
    startNode -= 'A';i
    for (int i = 0; i < vertexNum; i++) {
        closestEdges[i].lowestVertex = startNode;
        closestEdges[i].lowestCost = costMatrix[startNode][i];
    }
    /*create minimal spanning tree*/
    for (int count = 0; count < vertexNum - 1; count++) {
        int index=-1, min = MAX_COST;
        /*find the closest edge*/
        for (int i = 0; i < vertexNum; i++) {
            if (closestEdges[i].lowestCost != 0 && closestEdges[i].lowestCost < min) {
                min = closestEdges[i].lowestCost;
                index = i;
            }
        }
        minSpanningTree[count].vertex1 = static_cast<char>(index+'A');
        minSpanningTree[count].vertex2 = static_cast<char>(closestEdges[index].lowestVertex + 'A');
        minSpanningTree[count].cost = closestEdges[index].lowestCost;
        /*update closestEdges*/
        for (int i = 0; i < vertexNum; i++) {
            if (closestEdges[i].lowestCost != 0 && costMatrix[i][index] < closestEdges[i].lowestCost) {
                closestEdges[i].lowestVertex = index;
                closestEdges[i].lowestCost = costMatrix[i][index];
            }
        }
    }
}

/*
 * Function Name:   printMinimalSpanningTree
 * Function:        print the minimal spanning tree
 * Input Parameters:void
 * Return Value:    void
 * Notes:           Class external implementation of member functions
 */
void PowerGrid::printMinimalSpanningTree() {
    std::cout << ">>> 最小生成树的顶点及边为:" << std::endl;
    for (int count = 0; count < vertexNum - 1; count++) {
        std::cout << minSpanningTree[count].vertex1 << "-<" << minSpanningTree[count].cost << ">-" << minSpanningTree[count].vertex2 << std::endl;
    }
    std::cout << std::endl;
}

/*
 * Function Name:   makeChoice
 * Function:        choose the start node
 * Input Parameters:const char* prompt
 *                  int vertexNum
 * Return Value:    int
 */
int makeChoice(const char* prompt,int vertexNum)
{
    std::cout << prompt;
    while (true) {
        char choice = _getch();;
        if (choice == 0 || choice == 32)
            choice = _getch();
        if ('A' <= choice && choice <= static_cast<char>(vertexNum + 'A'-1)) {
            std::cout << " [" << choice << "]" << std::endl << std::endl;
            return choice ;
        }
    }
}

/*
 * Function Name:   main
 * Function:        Main function
 * Return Value:    0
 */
int main() {
    /*output the title*/
    std::cout << "+--------------------------------------------------+" << std::endl;
    std::cout << "|               电网建设造价模拟系统               |" << std::endl;
    std::cout << "|  Power Grid Construction Cost Simulation System  |" << std::endl;
    std::cout << "+--------------------------------------------------+" << std::endl<<std::endl;

    /*input the number of vertices*/
    int vertexNum = inputInteger(2, MAX_VERTEX_NUM, "电网节点数");
    PowerGrid powerGrid(vertexNum);
    /*choose the start node*/
    std::cout << std::endl;
    std::cout << ">>> 请输入起始节点[A-" << static_cast<char>('A' + vertexNum - 1) << "]:";
    int startNode = makeChoice("", vertexNum);
    /*create and print the minimal spanning tree*/
    powerGrid.createMinimalSpanningTree(startNode);
    powerGrid.printMinimalSpanningTree();
    /*wait for user input to quit*/
    std::cout << "Press Enter to Quit" << std::endl;
    while (_getch() != '\r')
        continue;
    return 0;
}
