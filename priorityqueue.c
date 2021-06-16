#include "priorityqueue.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
int parent(int index)
{
    return (index - 1) / 2; //parent is index-1/2
}

int left(int index)
{
    return (2 * index + 1);
}

int right(int index)
{
    return (2 * index + 2);
}

void swap(HeapNode *x, HeapNode *y)
{
    HeapNode temp = *x;
    *x = *y;
    *y = temp;
}
PtrToMinHeap CreateHeap(int InputCapacity)
{
    PtrToMinHeap temp;                            // creating a temporary MinHeap pointer which will be finally returned
    temp = (PtrToMinHeap)malloc(sizeof(MinHeap)); //mallocing memory to min heap
    temp->capacity = InputCapacity;               //setting capacity size and mallocing memory for the array
    temp->heap_size = 0;
    temp->Harr = (HeapNode *)malloc(sizeof(HeapNode) * InputCapacity);
    return temp;
}
void InsertMinHeapKeyValue(PtrToMinHeap H, int iKey, int iValue)
{

    if (H->heap_size == H->capacity)
    {
        printf("cannot insert any more elements into the heap");
        return;
    }
    H->heap_size++; //first increase heap size of H

    //insert the element at the very end of the heap array
    int i = H->heap_size - 1;
    H->Harr[i].key = iKey;
    H->Harr[i].value = iValue;

    //Fixing the minheap if it violated(recursive fashion)
    while (i != 0 && H->Harr[parent(i)].value > H->Harr[i].value)
    {
        swap(&H->Harr[i], &H->Harr[parent(i)]);
        i = parent(i);
    }
}

void Heapify(PtrToMinHeap H, int index) //simple recursive function to Heapify a Heap at a violated index
{
    int leftchild = left(index);
    int rightchild = right(index);
    int smallest = index;
    if (leftchild < H->heap_size && H->Harr[leftchild].value < H->Harr[index].value)
        smallest = leftchild;
    if (rightchild < H->heap_size && H->Harr[rightchild].value < H->Harr[smallest].value)
        smallest = rightchild;
    //the 4 lines above are just to figure out the smallest value containing index amongst the index, left(index) and right(index)
    if (smallest != index)
    {
        swap(&H->Harr[index], &H->Harr[smallest]);
        Heapify(H, smallest);
    }
    return;
}

void DecreaseKey(PtrToMinHeap H, int index, int newvalue) //will decrease the value at a certain index
{
    H->Harr[index].value = newvalue; //set the value at index to newvalue
    while (index != 0 && H->Harr[parent(index)].value > H->Harr[index].value)
    {
        swap(&H->Harr[index], &H->Harr[parent(index)]);
        index = parent(index);
    } //perform sift up operation on the index
    return;
}

HeapNode ExtractMin(PtrToMinHeap H) //extract min value from heap(zeroth-index)
{
    HeapNode temp;
    temp.value = INT_MAX;
    temp.key = INT_MAX; //setting this in case heap size is null, we can print an error message instead as well
    if (H->heap_size <= 0)
        return temp;
    if (H->heap_size == 1)
    {
        H->heap_size--;
        return H->Harr[0];
    } //incase the heap size is 1, that is it has only 1 element, just print the element
    temp = H->Harr[0];
    H->Harr[0] = H->Harr[H->heap_size - 1];
    H->heap_size--;
    Heapify(H, 0); //if it has more than one element, store zeroeth index in some temp node and then replace zeroeth index with last index and sift down (Heapify)

    return temp;
}

void DeleteKeyHeap(PtrToMinHeap H, int index)
{
    DecreaseKey(H, index, INT_MIN); //simple trick to Delete a particular index of the heap, just decrease value at the index to INT_MIN
    ExtractMin(H);                  //extract the min value, that is the index which we want to delete
}

HeapNode GetMin(PtrToMinHeap H)
{
    return H->Harr[0]; //this returns the Minimum value of the heap, without removing it from the heap
}

void PrintHeap(PtrToMinHeap H) //Prints the Heap array
{
    for (int i = 0; i < H->heap_size; i++)
    {
        printf("%d   %d\n", H->Harr[i].key, H->Harr[i].value);
    }
    printf("\n\n\n\n\n");
    return;
}