#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <limits>
#include <memory>
#include <deque>
#include <malloc.h>

#include "homework.h"
#define INF numeric_limits<double>::infinity()

using namespace std;

/************ Implementation ***********/
node* createNode(string nodeName)
{

    node* temp,*temp2;// = NULL;
    temp = new node; //(node*)malloc(sizeof(node));
    //cout<<endl<<temp;
    //cout<<"\nNode to be created:-"<<nodeName<<endl;
    temp->name = nodeName;

    temp->pathCost = INF;
    temp->parent = NULL;
    temp->firstChild = NULL;
    temp->nextSibling = NULL;
    temp2 = temp;
    //free(temp);
   // cout<<"\nNode "<<nodeName<<" created\n";
    return temp2;
}

int outputFile()
{
int ret=0,j=0,outputQueueSize=0;
        ofstream outfile;
     outputQueueSize = dfsQueuePathSequence.size();
   outfile.open("output.txt");

    if(outfile.is_open())
    {
         for(j=0;j<outputQueueSize;++j)
        {
        outfile <<dfsQueuePathSequence[j]->name<<space<<dfsQueuePathSequence[j]->pathCost;
        outfile << endl;
        }
        outfile.close();
        ret = 1;
    }

    else
    {
    ret = 0;
    cout << "Unable to open file";
    }
    return ret;
}

int readFile()
{
    int ret=0,lt=-1,trafficCount=0,suntrafficCount=0,stCount=-1;
    string data = "",inputArr;
   // char noLiveTraffic[255];
    char *station,*datat;
    //char *const sp = ' ';
    ifstream infile;
    infile.open("input.txt");
    if(infile.is_open())
    {
        cout << "Reading from the file" << endl;
        while(getline(infile, data))
        {
            //cout << data << endl;

            ++fileLineCount;

            if(fileLineCount == 1)
                ALGO = data;
            else if(fileLineCount == 2)
                START_STATE = data;
            else if(fileLineCount == 3)
                GOAL_STATE = data;
            else if(fileLineCount == 4)
            {
                //noLiveTraffic = (char)data;

                NO_LIVETRAFFIC = atoi (data.c_str());
                //liveTraffic *liveT = (liveTraffic*)malloc(NO_LIVETRAFFIC*sizeof(liveTraffic));
    liveT = new liveTraffic[NO_LIVETRAFFIC];
            }

            else if(fileLineCount <= 4+NO_LIVETRAFFIC)
            {
                //cout << "\nLine59\n";
                //liveTraffic* liveT = new liveTraffic[NO_LIVETRAFFIC];
                datat = (char*)data.c_str();
                //cout << datat <<endl;
                station = strtok (datat," ");
                trafficCount = 0;
                ++lt;
                while (station != NULL)
                {
                    ++trafficCount;
                    switch(trafficCount)
                    {
                    case 1:
                        liveT[lt].srcLoc = station;
                       // strcpy("111",liveT[0].srcLoc);
                        break;
                   case 2:
                        liveT[lt].desLoc = station;
                        break;
                    case 3:
                        liveT[lt].ttTravel = atoi(station);
                        break;
                    default:
                        break;

                    }
                    station = strtok (NULL," ");
                }
                //cout << endl;

            }

            else if(fileLineCount == 5+NO_LIVETRAFFIC)
            {
             NO_SUNTRAFFIC = atoi (data.c_str());
             sunT = new sunTraffic[NO_SUNTRAFFIC];
            }
            else
            {
            datat = (char*)data.c_str();
                //cout << datat <<endl;
                station = strtok (datat," ");
                suntrafficCount = 0;
                ++stCount;
                while (station != NULL)
                {
                    ++suntrafficCount;
                    switch(suntrafficCount)
                    {
                    case 1:
                        sunT[stCount].srcLoc = station;
                        sunT[stCount].desLoc = GOAL_STATE;
                        break;
                    case 2:
                        sunT[stCount].ttTravel = atoi(station);
                        break;
                    default:
                        break;

                    }
                    station = strtok (NULL," ");
                }
            }

            data = "";
        }
        // close the opened file
        infile.close();
        ret = 1;
    }
    return ret;
}

void addNodeToList(node* nodeToBeAdded)
{
    char* nodeName;
    allNodeList* tempList = NULL;

    tempList = new allNodeList;//(allNodeList*)malloc(sizeof(allNodeList));
    nodeName = (char*)nodeToBeAdded->name.c_str();
    //cout << "Mera:"<<nodeName<<endl;

    tempList->nodeAddr = nodeToBeAdded;
     tempList->nodeNM = nodeName;
    tempList->next = NULL;
    if(!nodeListStart) // first node
    {
        nodeListStart = tempList;
        nodeListEnd = tempList;
    }
    else
    {
        nodeListEnd->next = tempList;
        nodeListEnd = nodeListEnd->next;
    }

    tempList = NULL;
}

node* doesNodeExist(string nodeName)
{
  allNodeList*  t1 = nodeListStart;

        while(t1){
        if(t1->nodeNM == nodeName)
        return t1->nodeAddr;
        t1 = t1->next;
        }
       return NULL;
}

void attachNodeToTree(node* src, node* dest)
{
    node* nodeTemp;
    //cout << "\n Src:" << src<<" , dest:"<<dest <<endl;
                if(!src->firstChild)
                    src->firstChild = dest;
                else
                {
                    nodeTemp = src->firstChild;
                    while(nodeTemp->nextSibling)
                    {
                        nodeTemp = nodeTemp->nextSibling;
                    }
                    nodeTemp->nextSibling = dest;
                    //cout << "nextSIb:" <<nodeTemp->nextSibling;
                }
}
void createTree()
{
int i;
node* srcAdd=NULL,*desAdd=NULL;
node* t = NULL,*t2=NULL,*t3=NULL;//*nodeTemp;
    for(i=0;i<NO_LIVETRAFFIC;++i)
    {
        if(i==0 && liveT[i].srcLoc == START_STATE)  // root intersection
        {
            t = createNode(liveT[i].srcLoc);
            treeRoot = t;
            addNodeToList(t);

           t2 = createNode(liveT[i].desLoc);
            addNodeToList(t2);
            attachNodeToTree(t,t2);
        }
        else
        {
            srcAdd = doesNodeExist(liveT[i].srcLoc);    //Address of source node in traffic
            desAdd = doesNodeExist(liveT[i].desLoc);    //Address of destination node in traffic
           if(srcAdd)
           {
             if(desAdd)                       // src and dest both exist
             {
             attachNodeToTree(srcAdd,desAdd);
                /*if(!srcAdd->firstChild)
                    srcAdd->firstChild = desAdd;
                else
                {
                    nodeTemp = srcAdd;
                    while(nodeTemp->nextSibling)
                    {
                        nodeTemp = nodeTemp->nextSibling;
                    }
                    nodeTemp->nextSibling = desAdd;
                }*/
             }
             else{            //dest does not exist
                t3 = createNode(liveT[i].desLoc);
                addNodeToList(t3);
                attachNodeToTree(srcAdd,t3);
             }
           }
           else  //src does not exist
           {
               node*  t4 = createNode(liveT[i].srcLoc);   // create src
                addNodeToList(t4);
                if(desAdd)            // src not but dest does exist
                {
                    attachNodeToTree(t4,desAdd);
                }
                else                   // neither src nor dest node in traffic exist
                {
                    node*  t5 = createNode(liveT[i].desLoc);   //create dest node
                    addNodeToList(t5);
                    attachNodeToTree(t4,t5);
                }


           }


        }
       // t = NULL;

    }
}

int findNoOfTreeNodes()
{
    allNodeList *countNode;
    double count =0 ;
    countNode = nodeListStart;
    while(countNode)
    {
        ++count;
       countNode = countNode->next;
    }
    return count;
}

void enqueue( node* p)
{
    /*
    int i =0;
    while(dfsQueue[i]!="")
    {
        ++i;
    }
    dfsQueue[i] = p;
    */
    dfsQueue.push_back(p);
}
/*
char* dqueue()
{

}
*/
void findSortestPath()
{

node* nodeTraversal = dfsQueueOutput.back();   // Lats node i.e. GOAL_STATE node
while(nodeTraversal->parent)
{
    dfsQueuePathSequence.push_front(nodeTraversal);
    nodeTraversal = nodeTraversal->parent;
}
    dfsQueuePathSequence.push_front(nodeTraversal);
}

void init_bfs()           //BFS Implementation
{
    int j = 0,outputQueueSize=0,goalStFound = 0;
    node *currentNode = NULL, *childNode = NULL;
    totalTreeNodes = findNoOfTreeNodes();

    //Initialize start_node with 0 path cost
    treeRoot->pathCost = 0;
    dfsQueue.push_back(treeRoot);
//enqueue("AMIT");
    while(!dfsQueue.empty() && goalStFound==0){

    currentNode = dfsQueue.front();
    childNode = currentNode->firstChild;
    dfsQueue.pop_front();
    dfsQueueOutput.push_back(currentNode);
    if(currentNode->name != GOAL_STATE)
      {
        while(childNode)
        {
            if((currentNode->pathCost + 1) < childNode->pathCost)
            {
                childNode->pathCost = currentNode->pathCost + 1;
                childNode->parent =  currentNode;
                dfsQueue.push_back(childNode);
            }
            childNode = childNode->nextSibling;
        }
        }
        else
        goalStFound = 1;
    }
    findSortestPath();
    //<-----------------display DFS---------------->
    outputQueueSize = dfsQueuePathSequence.size();
    cout<<"\n<----------DFS----------------->\n\nLength of Path:"<<outputQueueSize<<endl<<endl;
    for(j=0;j<outputQueueSize;++j)
    {
        cout<<"   "<<dfsQueuePathSequence[j]->name<<" "<<dfsQueuePathSequence[j]->pathCost;
        j==outputQueueSize-1? :cout<<"   ====>";
    }

}
int main ()
{
    //int nodeCount = 0;
    if(readFile())
    {
        cout<< "FIle was read successfully!\n";
        allNodeList* t1;
        createTree();
        //cout << t->name << endl << t->pathCost << endl << c_bfs <<endl<<c_dfs<<endl<<c_ucs<<endl<<c_ast<<endl;
        cout << endl<<ALGO <<START_STATE<<GOAL_STATE<<NO_LIVETRAFFIC<<NO_SUNTRAFFIC<<endl;

        t1 = nodeListStart;
         cout<<"\n<------- N-Array Tree ----------->\n";
        cout<<"\n Node in List: ";
        while(t1){
        cout<<endl<<t1->nodeNM <<" "<<t1->nodeAddr <<" "<<t1->nodeAddr->firstChild<<space<<t1->nodeAddr->nextSibling;
        t1 = t1->next;
        }
        //print N-Array tree
        //node* treeTravTemp = treeRoot;


//  <<<<<<<<<<<<<<<_____________ALGO_______________>>>>>>>>>>>>>>>>
if(ALGO == c_bfs)
{
     init_bfs();
     if(outputFile()==1)
        cout <<"\nFile Generayed Succefully.\n";
    else
        cout<< "\nError in file generation!\n";
}

    }

    return 0;
}

