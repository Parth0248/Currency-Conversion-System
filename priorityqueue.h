//headerfile to store data structure for priority queue stuff(which we will use in the dijkstra algorithm later)
#ifndef QUEUE__H
#define QUEUE__H

typedef struct HeapNode HeapNode;
struct HeapNode
{
    int key;   //contains node index as key
    int value; //contains dv(shortest distance as value )

}; //This is the Node for the Minheap, and will consist of a key-value pair
//In our case the key is the Node index, and the value is Dv(i.e shortest distance yet to the key node)

typedef struct MinHeap MinHeap;
typedef MinHeap *PtrToMinHeap;
struct MinHeap
{
    HeapNode *Harr; //heap array
    int capacity;   //maximum number of elements possible in the heap(will be 1e5 in our case for safe measure)
    int heap_size;  //current number of elements in the heap
};                  //structure which has minheap

//function declarations
PtrToMinHeap CreateHeap(int InputCapacity);                       //Creates a minheap of given capacity
void InsertMinHeapKeyValue(PtrToMinHeap H, int iKey, int iValue); //inserts min heap with given key and value pair, note that minheap will be made on basis of value not key
void Heapify(PtrToMinHeap H, int index);                          //heapifies the given MinHeap at the given index
void DeleteKeyHeap(PtrToMinHeap H, int index);                    //deletes the given index from the minheap
void swap(HeapNode *x, HeapNode *y);                              //call by reference function to swap values of the two parameters
HeapNode ExtractMin(PtrToMinHeap H);                              //extracts Minimum value from a given heap
void DecreaseKey(PtrToMinHeap H, int index, int newvalue);        //changes the value of given index in minheap to a smaller value(given that H[i].value>newvalue)
int left(int index);                                              //returns index of left child of index i
int right(int index);                                             //returns index of right child of index i
int parent(int index);                                            //returns index of parent of index i
HeapNode GetMin(PtrToMinHeap H);                                  //returns Minimum value of MinHeap, different from ExtractMin which also removes the minimum value as well
void PrintHeap(PtrToMinHeap H);                                   //Prints the Heap array

#endif // !QUEUE__H