#ifndef GRAPH__HH
#define GRAPH__HH

//now defining a linklist for Currencies in a particular Tradebank
//This will only be used when we want to check whether a particular currency exists for a node or not

//now we add info on graph nodes
typedef struct GraphNode GraphNode; //standard typedef
typedef GraphNode *PtrToGraphNode;  //standard typedef
struct GraphNode
{
    int VertexID;        //stores the VertexID of the Node
    int weight;          //will be useful for storing weights of edges
    PtrToGraphNode next; //stores the pointer to the next node
};
//now the actual adjacency list
typedef struct GraphList GraphList;
typedef GraphList *PtrToGraphList;
struct GraphList
{
    int NumberOfVertices;             //stores the number of vertices that are currently present in the graph
    PtrToGraphNode *GraphVertexArray; //essentially an array of ptrtonodes
                                      //which will essentially store pointers to the neighbouring vertices of a given vertex
};
typedef struct dijkstra dijkstra;
struct dijkstra
{
    int *dist; //contains the shortest cost

    int *prev; //contains the node previous to the end node for the shortest code, will be used to figure out the path
};             //this is what we will have to return from the dijkstra function at the end

typedef struct currencynode currencynode;
typedef struct currencynode *PtrToCurrencyNode;
typedef PtrToCurrencyNode CurrencyList;
struct currencynode
{
    char NameOfCurrency[100]; // stores the name of the currency
    int Vertexid;             //stores the VertexID of that currency
    PtrToCurrencyNode next;   //pointer to next node
};

typedef struct Tradebank Tradebank; //typdefing structures
typedef Tradebank *PtrToTradebank;  //typedefing pointers to tradebank
struct Tradebank
{
    char NameOfTradeBank[100]; //Stores the name of the trade bank
    PtrToTradebank next;
    PtrToGraphList G;
    int availablevertices[1000];
    PtrToCurrencyNode CurrencyHead; //Head of the linked list
};

typedef struct stack stack;
typedef stack *ptrtostack;
typedef stack *stackhead;
struct stack
{
    int value;
    stack *next;
};
stackhead initstack();
void push(ptrtostack S, int value);
ptrtostack pop(ptrtostack S);
void displaystack(stackhead S);

//functions for the tradebank
PtrToGraphList CreateGraph(int NumberOfVertices);                              //This function will create a graph with the given number of vertices, for our case it will be 1e3
void DeleteVertex(PtrToGraphList G, int vertex);                               //This function deletes all the incoming and outgoing edges from a vertex and deletes it.
void DeleteGraph(PtrToGraphList G);                                            //deletes the entire graph struct entered;
void InsertEdge(PtrToGraphList G, int source, int destination, int weight);    //this function will add an edge to the graphlist from the source vertex to the destination vertex with a given weight
void PrintGraph(PtrToGraphList G);                                             //function to print the graph and its vertices
dijkstra dijkstraalgo(PtrToGraphList G, int NumberOfVertices, int startindex); //This function is the dijkstra algo to calculate minimum cost path from a given vertex to all other vertices
int EdgeExists(PtrToGraphList G, int source, int dest);                        //this function checks if a particular edge exists in the graph
void RemoveEdge(PtrToGraphList G, int source, int dest);                       //this function removes an edge from the graph, if it exists
int min(int a, int b);
int Tarjan(PtrToGraphList G, int low[], int NumberofVertices);                                                           //performs Tarjan's SCC algorithm to find out the number of Singly connected componenents in the graph
void depthfirst(PtrToGraphList G, stackhead S, int *id, int source, int ids[], int onstack[], int low[], int *scccount); //modified depth first search which is used as a subroutine to the Tarjan algo

#endif
