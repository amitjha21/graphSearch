#include <iostream>
using namespace std;

/************ Decleration ***********/
	char const c_bfs[] = "BFS";
	char const c_dfs[] = "DFS";
	char const c_ucs[] = "UCS";
	char const c_ast[] = "A*";
	char const space[] = " ";

	typedef struct node
	{
		string name;
		double pathCost;
		node* parent;
		node* firstChild;
		node* nextSibling;
	} node;

   typedef struct allNodeList
    {
        char* nodeNM;
        node* nodeAddr;
        allNodeList* next;
    } allNodeList;

	 struct liveTraffic
	{
		string srcLoc;
		string desLoc;
		double ttTravel;
	} ;

	 struct sunTraffic
	{
		string srcLoc;
		string desLoc;
		double ttTravel;
	} ;

	string ALGO="",
		  START_STATE="",
		  GOAL_STATE="";
	int NO_LIVETRAFFIC = 0,
		NO_SUNTRAFFIC = 0;
		int fileLineCount = 0,
		 totalTreeNodes = 0;

		node* treeRoot;
liveTraffic* liveT;
sunTraffic* sunT;
allNodeList* nodeListStart, *nodeListEnd ;

deque<node*> dfsQueue;
deque<node*> dfsQueueOutput;
deque<node*> dfsQueuePathSequence;
