#include "graph.h"
#include "priorityqueue.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

PtrToGraphList CreateGraph(int NumberOfVertices)
{
    PtrToGraphList G; //making temporary Graphlist which we will return in the end
    //Allocating memory to the List
    G = (PtrToGraphList)malloc(sizeof(GraphList)); //malloc'ed memory here
    //asserting whether memory has been allocated or not
    if (G == NULL) //memory could not be allocated.
    {
        printf("Malloc failed!\n");
        exit(0);
    }
    G->NumberOfVertices = NumberOfVertices;
    G->GraphVertexArray = (PtrToGraphNode *)malloc(NumberOfVertices * sizeof(PtrToGraphNode)); //This makes an array of pointers to nodes.
    //asserting for memory allocation
    if (G->GraphVertexArray == NULL)
    {
        printf("Malloc failed");
        exit(0);
    }
    //Now we create an empty Graph
    for (int i = 0; i < NumberOfVertices; i++)
    {
        G->GraphVertexArray[i] = NULL; //Initialize all of the graph node pointers to NULL since an empty graph does not have neighbours for any vertex
    }
    return G;
}
void InsertEdge(PtrToGraphList G, int source, int destination, int inputweight) //this function will add an edge to the graphlist from the source vertex to the destination
{
    int found = 0;                      //In case there already exists an edge between source to destination this flag will change to 1
    PtrToGraphNode temp;                //making a temporary NodePtr which will be inserted later
    temp = G->GraphVertexArray[source]; //go to the source vertex of the array
    if (temp == NULL)
    {
        temp = (PtrToGraphNode)malloc(sizeof(GraphNode));
        temp->VertexID = destination;
        temp->weight = inputweight; //these three lines create the temp node and then set its ID and weight
        temp->next = G->GraphVertexArray[source];
        G->GraphVertexArray[source] = temp; //standard code for inserting a node to the front of the linked list
        return;
    }
    for (; temp; temp = temp->next) //traversing through the list of the source vertex to check whether the edge already exists
    {
        int checker = temp->VertexID; //stores the vertex ID of the node being traversed right now
        if (checker == destination)
        {
            found = 1;
        }
    }
    if (!found)
    {
        temp = (PtrToGraphNode)malloc(sizeof(GraphNode));
        temp->VertexID = destination;
        temp->weight = inputweight; //these three lines create the temp node and then set its ID and weight
        temp->next = G->GraphVertexArray[source];
        G->GraphVertexArray[source] = temp; //standard code for inserting a node to the front of the linked list
    }
    else
    {
        printf("Edge already exists\n"); //incase the edge already exists then print this statement
    }
    return;
}
void PrintGraph(PtrToGraphList G)
{
    PtrToGraphNode temp; //temporary node structure which we will use to traverse the entire graph structure
    for (int i = 0; i < G->NumberOfVertices; i++)
    {
        if (G->GraphVertexArray[i] == NULL) //in case the i-th vertex has no neighbours then no need to traverse through the entire array
        {
            printf("%d node has no neighbours\n", i);
            continue;
        }
        printf("%d---->", i); //in case the i-th vertex has neighbours then print all the neighbours
        for (temp = G->GraphVertexArray[i]; temp->next; temp = temp->next)
        {
            printf("%d(w=%d)---->", temp->VertexID, temp->weight);
        }
        printf("%d(w=%d)\n", temp->VertexID, temp->weight); //to make sure that the last neighbour doesn't get printed with an arrow we print it separately
    }
    return;
}

dijkstra dijkstraalgo(PtrToGraphList G, int NumberOfVertices, int startindex)
{
    int vis[NumberOfVertices]; //Creates a array which will store the visited nodes
    dijkstra answer;
    answer.dist = (int *)malloc(sizeof(int) * NumberOfVertices);
    answer.prev = (int *)malloc(sizeof(int) * NumberOfVertices);
    for (int i = 0; i < NumberOfVertices; i++)
    {
        answer.dist[i] = INT_MAX; //setting all dist values to inf(INT_MAX)
        answer.prev[i] = -1;      //setting all prev values to NULL(here -1)
        vis[i] = 0;               //setting visited array to 0 for all elements in the array
    }
    answer.dist[startindex] = 0; //set startindex dist to zero to kickstart algo
    PtrToMinHeap PQ = NULL;      //create empty priority queue
    PQ = CreateHeap(100000);
    InsertMinHeapKeyValue(PQ, startindex, 0); //This will ensure that algo is kickstarted properly
    while (PQ->heap_size != 0)
    {
        HeapNode tempheapnode;
        tempheapnode = ExtractMin(PQ); //Extract the most promising key-value pair
        vis[tempheapnode.key] = 1;     //set vis of index in tempnode to true meaning that node has been visited
        if (answer.dist[tempheapnode.key] < tempheapnode.value)
            continue; //Stale Node optimization to ensure that nodes aren't visited multiple times
        PtrToGraphNode tempgraphnode;
        tempgraphnode = G->GraphVertexArray[tempheapnode.key];
        if (tempgraphnode == NULL) //if the vertex has no neighbours then skip(control flow will definitely not reach here but still)
            continue;
        for (; tempgraphnode; tempgraphnode = tempgraphnode->next) // traversing through the adjacency list of a particular index
        {
            if (vis[tempgraphnode->VertexID]) //if the node has already been visited(i.e smallest distance has been found) then skip
                continue;
            int newDist = 0;
            newDist = answer.dist[tempheapnode.key] + tempgraphnode->weight;
            if (newDist < answer.dist[tempgraphnode->VertexID]) //This is the relaxation part of dijkstra algo
            {
                //if we have found a better distance then update the prev dist array as well as the heap
                answer.prev[tempgraphnode->VertexID] = tempheapnode.key;
                answer.dist[tempgraphnode->VertexID] = newDist;
                InsertMinHeapKeyValue(PQ, tempgraphnode->VertexID, newDist);
            }
        }
    }
    free(PQ->Harr);
    free(PQ);

    return answer;
}
void DeleteGraph(PtrToGraphList G)
{
    for (int i = 0; i < G->NumberOfVertices; i++)
    {
        PtrToGraphNode temp;
        if (G->GraphVertexArray[i] == NULL) //checks if there is any data in the particular vertex to remove and if there is not it will continue
            continue;
        while (G->GraphVertexArray[i]->next != NULL)
        {
            temp = G->GraphVertexArray[i];                         //equating the temporary node to that particular vertex and
            G->GraphVertexArray[i] = G->GraphVertexArray[i]->next; //then accessing the next element and freeing the temp node until it points to NULL
            free(temp);                                            //indicating the last element had been deleted
        }
        free(G->GraphVertexArray[i]); //freeing the memory allocated to the particular vertex and equating it to NULL
        G->GraphVertexArray[i] = NULL;
    }
    free(G->GraphVertexArray); //freeing the memory allocated to the array of pointer to Graphnodes
    free(G);                   //freeing the memory allocated to the Pointer to the particular struct GraphList
}
void DeleteVertex(PtrToGraphList G, int vertex)
{
    PtrToGraphNode tempgraphnode;                 //temporary node
    PtrToGraphNode prevgraphnode;                 //pointer to previous node
    for (int i = 0; i < G->NumberOfVertices; i++) //for loop to traverse all the vertices of the graph
    {
        if (i == vertex) //we shall deal with the adjacency list of the vertex itself separately
            continue;
        else
        {
            tempgraphnode = G->GraphVertexArray[i];
            if (tempgraphnode == NULL) //if the ith vertex has no neighbour, skip
                continue;
            if (tempgraphnode->VertexID == vertex) //if the first neighbour is the input vertex then just remove it
            {
                G->GraphVertexArray[i] = tempgraphnode->next;
                free(tempgraphnode);
                continue;
            }
            else //else go through the adjacency list and then remove
            {
                tempgraphnode = G->GraphVertexArray[i]->next;
                prevgraphnode = G->GraphVertexArray[i];
                for (; tempgraphnode; tempgraphnode = tempgraphnode->next, prevgraphnode = prevgraphnode->next)
                {
                    if (tempgraphnode->VertexID == vertex)
                    {
                        prevgraphnode->next = tempgraphnode->next;
                        free(tempgraphnode);
                        break;
                    }
                }
            }
        }
    }
    PtrToGraphNode temp;
    if (G->GraphVertexArray[vertex] == NULL)
        return;
    while (G->GraphVertexArray[vertex]->next != NULL)
    {
        temp = G->GraphVertexArray[vertex];
        G->GraphVertexArray[vertex] = G->GraphVertexArray[vertex]->next;
        free(temp);
    }
    free(G->GraphVertexArray[vertex]);
    G->GraphVertexArray[vertex] = NULL;
}

int EdgeExists(PtrToGraphList G, int source, int dest)
{
    int found = 0;                      //In case there already exists an edge between source to destination this flag will change to 1
    PtrToGraphNode temp;                //making a temporary NodePtr which will be inserted later
    temp = G->GraphVertexArray[source]; //go to the source vertex of the array
    if (temp == NULL)
    {
        return 0;
    }
    for (; temp; temp = temp->next) //traversing through the list of the source vertex to check whether the edge already exists
    {
        int checker = temp->VertexID; //stores the vertex ID of the node being traversed right now
        if (checker == dest)
        {
            found = 1;
        }
    }
    return found;
}

void RemoveEdge(PtrToGraphList G, int source, int dest)
{
    PtrToGraphNode tempgraphnode;                //declaring a temporary pointer to struct GraphNode
    tempgraphnode = G->GraphVertexArray[source]; //equating the temp pointer to the source of the edge to be removed
    if (tempgraphnode == NULL)                   //indicating the edge does not exist
        return;
    else
    {
        if (tempgraphnode->VertexID == dest) //if the first edge of the source is the edge to be removed we free the memory allocated to it
        {
            G->GraphVertexArray[source] = tempgraphnode->next;
            free(tempgraphnode);
            return;
        }
        else //we will traverse all edges until we find the edge with destination as 'dest'
        {
            tempgraphnode = G->GraphVertexArray[source]->next;
            PtrToGraphNode prevgraphnode = G->GraphVertexArray[source];
            for (; tempgraphnode; tempgraphnode = tempgraphnode->next, prevgraphnode = prevgraphnode->next)
            {
                if (tempgraphnode->VertexID == dest)
                {
                    prevgraphnode->next = tempgraphnode->next;
                    free(tempgraphnode); //freeing the memory allocated to the temporary pointer to GraphNode
                    break;
                }
            }
        }
    }
}
stackhead initstack() //initializes the stack
{
    stackhead S;
    S = (ptrtostack)malloc(sizeof(stack));
    S->value = -1;
    S->next = NULL;
    return S;
}
void push(ptrtostack S, int value) //pushes elements onto the stack
{
    ptrtostack x;
    x = initstack();
    x->value = value;
    x->next = S->next;
    S->next = x;
}
ptrtostack pop(ptrtostack S) //pops elements fromt the stack
{
    ptrtostack temp1 = NULL;
    if (S->next == NULL)
    {
        printf("Stack is empty");
        return temp1;
    }
    //since i only have to remove from the top
    ptrtostack temp = S->next;
    S->next = S->next->next;
    return temp;
    //displaystack(S);
}
void displaystack(stackhead S) //displays the stack
{
    if (S == NULL)
    {
        printf("Stack does not exist!!!");
        return;
    }
    else if (S->next == NULL)
    {
        printf("Stack is empty");
        return;
    }
    else
    {
        ptrtostack t = S->next;
        for (; t; t = t->next)
        {
            printf("%d", t->value);
        }
        printf("\n\n");
    }
}

int min(int a, int b) //returns minimum of two numbers
{
    if (a < b)
        return a;
    else
        return b;
}

void depthfirst(PtrToGraphList G, stackhead S, int *id, int source, int ids[], int onstack[], int low[], int *scccount)
{
    push(S, source);                    //push the vertex into the stack
    onstack[source] = 1;                //set the onstack of vertex id to 1(meaning it is in the stack)
    ids[source] = low[source] = source; //set the low link and id value to vertexid
    PtrToGraphNode tempgraphnode;
    tempgraphnode = G->GraphVertexArray[source];
    if (tempgraphnode != NULL) //traverse through the adjacency list
    {
        for (; tempgraphnode; tempgraphnode = tempgraphnode->next)
        {
            if (ids[tempgraphnode->VertexID] == -1) //if node is unvisited then to dfs there
                depthfirst(G, S, id, tempgraphnode->VertexID, ids, onstack, low, scccount);
            if (onstack[tempgraphnode->VertexID] == 1) //if the neighbour is visited then change low link value to min of source and neighbour
                low[source] = min(low[source], low[tempgraphnode->VertexID]);
        }
    }
    if (ids[source] == low[source]) //if we reach the beggining of scc
    {
        for (ptrtostack node = pop(S);; node = pop(S)) //pop all elements from the stack, mark onstack as 0
        {
            onstack[node->value] = 0;
            low[node->value] = ids[source];
            if (node->value == source)
                break;
        }
        (*scccount)++; //increase the scccount
    }
}

int Tarjan(PtrToGraphList G, int low[], int NumberofVertices)
{
    // we will returning the low array, which will calculate the low link values of the vertices
    //vertices with the same low link value are in the same component
    int id = 0;
    int scccount = 0;
    int ids[NumberofVertices];
    //int low[NumberofVertices];
    int onstack[NumberofVertices];
    stackhead S;
    S = initstack(); //making an empty stack, supports push and pop operations
    for (int i = 0; i < NumberofVertices; i++)
    {
        ids[i] = -1;
        low[i] = 0;
        onstack[i] = 0;
    } //initialize the stack array, the lowlink value array, and the id array to UNVISITED
    for (int i = 0; i < NumberofVertices; i++)
    {
        if (ids[i] == -1)
            depthfirst(G, S, &id, i, ids, onstack, low, &scccount); //perform a specialized depth first search
    }
    return scccount;
}