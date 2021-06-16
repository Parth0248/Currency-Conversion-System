#include "graph.h"
#include "UserInterface.h"
#include "priorityqueue.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

// char CurrencyList[1000][100];//Global Currency List
int CurrencyListCounter = 0;            //will keep track of the number of currencies inserted to the graph
PtrToTradebank ListofTradeBank;         // Linked List to store the TradeBanks
PtrToTradebank Tail;                    // To keep track of last added bank
PtrToTradebank Head;                    // To keep track of first added bank
int NoOfTradeBanks = 0;                 // To keep track of number of banks added
PtrToCurrencyNode CreateEmptyCurrList() //creates a dummy node and returns it's value
{
    PtrToCurrencyNode t;
    t = (PtrToCurrencyNode)(malloc)(sizeof(currencynode));
    strcpy(t->NameOfCurrency, "undefined");
    t->Vertexid = -1;
    t->next = NULL;
    return t;
}

int searchforcurrency(char *inputcurrency, PtrToCurrencyNode C) //search for the input currency in the given currency linked list
{
    if (C->next == NULL)
    {
        // printf("list is empty");
        return -1;
    }
    PtrToCurrencyNode tempnode; //temporary pointer used to traverse the entire linked list
    tempnode = C->next;         //set the tempnode to point to head of linked list
    for (; tempnode; tempnode = tempnode->next)
    {
        if (strcmp(inputcurrency, tempnode->NameOfCurrency) == 0)
        {
            return tempnode->Vertexid; //return the vertex id of the currency in the linked list
        }
    }
    return -1; //if the element is not found in the linked list then return zero
}

void addcurrency(char *inputcurrency, int vertexid, PtrToCurrencyNode c) //add the input currency to the currency linked list
{
    //if list is empty then do nothing
    if (c->next == NULL)
    {
        PtrToCurrencyNode temp;
        temp = (PtrToCurrencyNode)malloc(sizeof(currencynode));
        strcpy(temp->NameOfCurrency, inputcurrency);
        temp->Vertexid = vertexid;
        temp->next = c->next;
        c->next = temp;
        return;
    }
    //first search for the currency in the given linked list
    else
    {
        int search = searchforcurrency(inputcurrency, c); //searches for the currency in the linked list
        if (search != -1)
        {
            // printf("currency already exists"); //if the function returns -1 that means the currency wasn't there in the linked list
            return;
        }
        else
        {
            PtrToCurrencyNode temp;                                 //create a temporary currency node which will be inserted
            temp = (PtrToCurrencyNode)malloc(sizeof(currencynode)); //malloc a node and return it's pointer to temp
            strcpy(temp->NameOfCurrency, inputcurrency);
            temp->Vertexid = vertexid;
            temp->next = c->next;
            c->next = temp; //inserting the node to the front of the linked list
        }
    }
}

void deletecurrency(char *inputcurrency, PtrToCurrencyNode c) //deletes the node from the given currency list
{
    int search = searchforcurrency(inputcurrency, c); //searches for the currency in the linked list
    if (search == -1)
    {
        // printf("currency does not exist");
        return;
    }
    else
    {
        if (strcmp(c->next->NameOfCurrency, inputcurrency) == 0) //if the first node itself is the node to be deleted
        {
            PtrToCurrencyNode temp = c->next;
            c->next = c->next->next;
            free(temp);
        }
        else
        {
            PtrToCurrencyNode temp = c->next->next;
            PtrToCurrencyNode prev = c->next;
            for (; temp; temp = temp->next, prev = prev->next)
            {
                if (strcmp(temp->NameOfCurrency, inputcurrency) == 0)
                {
                    prev->next = temp->next;
                    free(temp);
                }
            }
        }
        return;
    }
}

void printcurrencylist(PtrToCurrencyNode C) //function to print the currency list of a bank and their respective vertices
{
    PtrToCurrencyNode temp; //declares a temporary pointer to struct CurrencyNode
    temp = C->next;
    for (; temp; temp = temp->next) //traverses the list and prints the name of the currency and the vertexID of the currency
    {
        printf("{%s,%d}", temp->NameOfCurrency, temp->Vertexid);
    }
    printf("\n");
    return;
}

void DeleteCurrList(PtrToCurrencyNode C) //function to delete currency List
{
    PtrToCurrencyNode temp;
    if (C->next == NULL) //the list is already empty
    {
        free(C); //frees memory allocated to pointer to struct CurrencyNode
        return;
    }
    while (C->next->next != NULL) //traversing the list and freeing memory allocated to the particular element of the currency list
    {
        temp = C->next;
        C->next = C->next->next;
        free(temp);
    }
    free(C->next);
    C->next = NULL;
    free(C);
    return;
}

void AddTradeBank(char *BankName)
{                            // we use this function to open a new bank in the sense to creat a head structure
    if (NoOfTradeBanks == 0) //this is the first TradeBank to be added
    {
        ListofTradeBank = (PtrToTradebank)malloc(sizeof(Tradebank));

        strcpy(ListofTradeBank->NameOfTradeBank, BankName);
        ListofTradeBank->G = CreateGraph(1000);
        ListofTradeBank->CurrencyHead = (PtrToCurrencyNode)malloc(sizeof(currencynode));
        strcpy(ListofTradeBank->CurrencyHead->NameOfCurrency, "undefined");
        ListofTradeBank->CurrencyHead->Vertexid = -1;
        ListofTradeBank->CurrencyHead->next = NULL;

        for (int i = 0; i < 1000; i++)
            ListofTradeBank->availablevertices[i] = 0; //initialises currency array to 0

        Tail = ListofTradeBank;
        Head = ListofTradeBank;

        Tail->next = NULL;
        NoOfTradeBanks++;
    }
    else
    {

        PtrToTradebank Traverse = Head; // We check if the bank exists or not
        bool BankExists = true;
        while (Traverse != NULL && BankExists) //traversing to check if the bank already exists
        {
            if (strcmp(Traverse->NameOfTradeBank, BankName) == 0)
            {
                BankExists = false;
                break;
            }
            Traverse = Traverse->next;
        }

        if (BankExists) //if the bank does not exist but other banks already exist in the list
        {
            Tradebank *NewBank = (Tradebank *)malloc(sizeof(Tradebank));

            strcpy(NewBank->NameOfTradeBank, BankName); //Storing bank name in the node created

            NewBank->G = CreateGraph(1000);
            NewBank->CurrencyHead = (PtrToCurrencyNode)malloc(sizeof(currencynode));
            strcpy(NewBank->CurrencyHead->NameOfCurrency, "undefined");
            NewBank->CurrencyHead->Vertexid = -1;
            NewBank->CurrencyHead->next = NULL;

            for (int i = 0; i < 1000; i++)
                NewBank->availablevertices[i] = 0; //initialises currency array to 0

            Tail->next = NewBank; // adding the node to end
            Tail = NewBank;       // updating the tail

            Tail->next = NULL;
            NoOfTradeBanks++; //incrementing the number of TradeBanks
        }
        else //if the bank already exists
        {
            printf("Bank Already exists");
            return;
        }
    }
}
void RemoveTradeBank(char *BankName)
{
    PtrToTradebank current, previous, position;       //creates 3 temporary Pointers to struct TradeBank for traversal
        previous = Head;                                  //Points to the 1st TradeBank
    if(previous==NULL)
    {
        printf("No bank exists in the list");
        return;
    }
    current = Head->next;                             //Points to the 2nd TradeBank
    if (strcmp(Head->NameOfTradeBank, BankName) == 0) //if the bank to be deleted is the first Trade bank in the list
    {
        position = Head;
        Head = Head->next; //the 1st bank shall then point to the second bank(which now becomes the first bank)
    }
    else
    {
        while (current != NULL) //traversing the list of trade banks to find the Trade bank to be deleted
        {
            if (strcmp(current->NameOfTradeBank, BankName) == 0)
            {
                break;
            }
            current = current->next;
            previous = previous->next;
        }
        if (current == NULL) //we have reached the end of the list but could not find the name of the bank indicating it does not exist
        {
            printf("The Trade bank does not exist.\n");
            return;
        }
        previous->next = current->next;
        position = current;
    }

    DeleteCurrList(position->CurrencyHead); //deletes currency list of the Position pointer
    DeleteGraph(position->G);               //deletes the graph
    position->next = NULL;
    free(position); //frees the memory allocated to the Pointer Position
}

void PrintTradeBankList()
{ //this function creates a temporary pointer for traversal and then prints each TradeBank as it traverses the list of trade banks
    PtrToTradebank temp;
    temp = Head;
    while (temp != NULL)
    {
        printf("%s\n", temp->NameOfTradeBank);
        temp = temp->next;
    }
}

void PrintTradeBankList2()
{
    printf("\n\n\n");
    PtrToTradebank temp;
    temp = Head;
    while (temp != NULL)
    {
        printf("Name of TradeBank->%s\n", temp->NameOfTradeBank); //prints name of the bank
        printf("Currencies supported by the Tradebank are \n");   // prints name of currencies in the bank
        PtrToCurrencyNode tc = temp->CurrencyHead->next;
        for (; tc; tc = tc->next)
        {
            printf("%s\n", tc->NameOfCurrency);
        }
        printf("\nCurrency conversion rates are\n");
        PrintTradeBankGraph(temp);
        temp = temp->next;
        printf("--------------------\n\n\n");
    }
}
void AddCurrencyExchange1(char *BankName, char *Currency1, char *Currency2, int ConversionRate)
{
    PtrToTradebank Traverse = Head; //declaring temporary pointer to struct TradeBank to traverse the List of Tradebanks
    bool BankExists = false;        //declaring bool variable to check if the bank exists or not

    while (Traverse != NULL && !BankExists) // We check if the bank exists or not by traversing the list
                                            // using the temporary Pointer to struct TradeBank 'Traverse'
    {                                       // finds the bank
        if (strcmp(Traverse->NameOfTradeBank, BankName) == 0)
        {
            BankExists = true; // if bank is found the bool variablee changes to TRUE
            break;
        }
        Traverse = Traverse->next;
    }

    if (BankExists)
    {
        PtrToCurrencyNode Checker = Traverse->CurrencyHead;    // Declaring temporary pointer to struct CurrencyNode for traversal of all currencies
        bool Currency1Exists = false, Currency2Exists = false; // declaring 2 bool variables to check if the currencies exist

        while (Checker != NULL)
        {
            if (strcmp(Checker->NameOfCurrency, Currency1) == 0)
                Currency1Exists = true;
            if (strcmp(Checker->NameOfCurrency, Currency2) == 0)
                Currency2Exists = true; //if the currencies are found their respective bool variable changes to TRUE
            Checker = Checker->next;
        }                                         //to check which of the two currency exists
        if (!Currency1Exists && !Currency2Exists) // both currency dont exists in the list
        {
            printf("neither currency exists\n");
            return;
        }

        else if (!Currency2Exists && Currency1Exists) // Currency 1 exists but currency 2 doesnt
        {
            printf("one of the two currencies does not exist\n");
            return;
        }
        else if (Currency2Exists && !Currency1Exists) // Currency 1 doesntexists but currency 2 exists
        {
            printf("one of the two currencies does not exist\n");
            return;
        }
        else
        {
            int sourceid = searchforcurrency(Currency1, Traverse->CurrencyHead); //finds the vertexID of currency1
            int destid = searchforcurrency(Currency2, Traverse->CurrencyHead);   //finds the vertexID of currency2
            if (EdgeExists(Traverse->G, sourceid, destid))
                printf("There already exists a conversion between the two given currencies\n");
            else
            {
                InsertEdge(Traverse->G, sourceid, destid, ConversionRate); //if edge deos not exist we create an edge between the two vertices(currencies)
            }
        }
    }

    else
    {
        printf("The Bank Does not Exist.\n"); //the bank does not exist
        return;
    }
}

void AddCurrencyToTradeBank(char *Bankname, char *inputcurrency)
{
    PtrToTradebank Traverse = Head; // We check if the bank exists or not
    bool BankExists = false;        // Declaring a bool variable to check if the bank exists

    while (Traverse != NULL && !BankExists)
    {                                                         // finds the bank
        if (strcmp(Traverse->NameOfTradeBank, Bankname) == 0) //if the bank is found changes the bool variable to TRUE
        {
            BankExists = true;
            break;
        }
        Traverse = Traverse->next;
    }

    if (BankExists)
    {
        int currencyid = searchforcurrency(inputcurrency, Traverse->CurrencyHead); //Searches for the currencyID
        if (currencyid == -1)                                                      //implies the currency does not exist
        {
            int insertid = 0;
            for (; insertid < 1000; insertid++) // traverses until finds free space for the currency
            {
                if (Traverse->availablevertices[insertid] == 0)
                    break;
            }
            if (insertid == 1000) // the maximum number of currencies that can be inserted has been reached
            {
                printf("Max Currency Limit Reached, Cannot Insert More Currencies\n");
            }
            else
            {
                Traverse->availablevertices[insertid] = 1;
                addcurrency(inputcurrency, insertid, Traverse->CurrencyHead);
            }
        }
        else
        {
            printf("Currency already exists\n");
            return;
        }
    }
    else
    {
        printf("Bank does not exist\n");
        return;
    }
}

void printcurrencyofvertexid(PtrToCurrencyNode C, int vertexid) //prints the currency id corresponding to a given vertex in a tradebank
{
    PtrToCurrencyNode t = C->next; // Starts from the node next to the dummy node
    for (; t; t = t->next)         //for loop to traverse the currencies until the vertexID matches
    {
        if (t->Vertexid == vertexid)
        {
            printf("%s", t->NameOfCurrency); // prints the name of the particular currency
            return;
        }
    }
    return;
}

void PrintTradeBankGraph(PtrToTradebank T) //prints the graph of the trade bank by going through it's adjacency list
{
    PtrToGraphList TradebankGraph = T->G; // Creates a temporary pointer to struct GraphList which is used for traversal
    for (int i = 0; i < TradebankGraph->NumberOfVertices; i++)
    {
        PtrToGraphNode tempgraphnode = TradebankGraph->GraphVertexArray[i]; // Creates a temporary pointer to struct GraphNode which accesses a particular vertex
        for (; tempgraphnode; tempgraphnode = tempgraphnode->next)
        {
            printcurrencyofvertexid(T->CurrencyHead, i);
            printf("----->");
            printcurrencyofvertexid(T->CurrencyHead, tempgraphnode->VertexID);
            printf("(conversion rate=%d)", tempgraphnode->weight); //
            printf("\n");
        }
    }
}

void RemoveCurrencyExchange(char *BankName, char *Currency1, char *Currency2)
{

    PtrToTradebank Traverse = Head; // We check if the bank exists or not
    bool BankExists = false;        // Declaring a bool variable which changes to true if the Bank exists
    while (Traverse != NULL && !BankExists)
    { // finds the bank
        if (strcmp(Traverse->NameOfTradeBank, BankName) == 0)
        {
            BankExists = true;
            break;
        }
        Traverse = Traverse->next;
    }
    if (BankExists) //if the bank exists then perform the below operations
    {
        PtrToCurrencyNode Checker = Traverse->CurrencyHead;    // Declaring a temporary pointer to struct CurrencyNode to use for traversal
        bool Currency1Exists = false, Currency2Exists = false; // Declaring 2 bool variables to check if the currencies exist

        while (Checker != NULL)
        {
            if (strcmp(Checker->NameOfCurrency, Currency1) == 0)
                Currency1Exists = true;
            if (strcmp(Checker->NameOfCurrency, Currency2) == 0)
                Currency2Exists = true;
            Checker = Checker->next;
        }
        if (!Currency1Exists && !Currency2Exists) // both currency dont exists in the list
        {
            printf("neither currency exists\n");
            return;
        }

        else if (!Currency2Exists && Currency1Exists) // Currency 1 exists but currency 2 doesnt
        {
            printf("one of the currencies does not exist\n");
            return;
        }
        else if (Currency2Exists && !Currency1Exists) // Currency 1 doesntexists but currency 2 exists
        {
            printf("one of the two currencies does not exist\n");
            return;
        }
        else //if both currencies exist
        {
            int sourceid = searchforcurrency(Currency1, Traverse->CurrencyHead); //find vertex id of source
            int destid = searchforcurrency(Currency2, Traverse->CurrencyHead);   //find vertex id of dest vertex
            if (EdgeExists(Traverse->G, sourceid, destid))                       //if edge exists between the two vertices
            {
                RemoveEdge(Traverse->G, sourceid, destid); //Remove the Edge between the two vertices
            }
            else
            {
                printf("no conversion rate exists between the two currencies\n"); //if no edge exists then print error message
            }
        }
    }

    else
    {
        printf("The Bank Does not Exist.\n");
        return;
    }
}

DijkstraBankInfo DijkstraOnBankList(char *sourcecurrency, char *destcurrency)
{
    DijkstraBankInfo solution;
    PtrToTradebank t = Head;
    solution.mincost = INT_MAX;
    for (; t; t = t->next)
    {
        int sourceid = searchforcurrency(sourcecurrency, t->CurrencyHead);
        int destid = searchforcurrency(destcurrency, t->CurrencyHead);
        if (sourceid != -1 && destid != -1)
        {
            dijkstra answer;
            answer = dijkstraalgo(t->G, 1000, sourceid);
            if (answer.dist[destid] < solution.mincost)
            {
                solution.mincost = answer.dist[destid];
                strcpy(solution.TradeBankName, t->NameOfTradeBank);
            }
        }
        else
        {
            continue;
        }
    }
    return solution;
}

void RemoveCurrencyFromTradeBank(char *BankName, char *inputcurrency)
{
    PtrToTradebank Traverse = Head; // We check if the bank exists or not
    bool BankExists = false;        // Declaring a bool variable which changes to true if bank is found
    while (Traverse != NULL && !BankExists)
    { // finds the bank
        if (strcmp(Traverse->NameOfTradeBank, BankName) == 0)
        {
            BankExists = true;
            break;
        }
        Traverse = Traverse->next;
    }
    if (BankExists) //if bank exists then search for the currency in Bank's currency list
    {
        int currencyid = searchforcurrency(inputcurrency, Traverse->CurrencyHead); //extract the vertex id of the currency
        if (currencyid == -1)
        {
            printf("currency does not exist\n"); //if the vertex id is -1 then the currency does not exist so print error message
            return;
        }
        else
        {
            DeleteVertex(Traverse->G, currencyid); //otherwise delete the vertex from the graph
            return;
        }
    }
    else //if BankExists is still false then the Bank does not exist
    {
        printf("Bank Does Not Exist\n");
        return;
    }
}

void CycleCheckinTradeBank(char *BankName)
{
    PtrToTradebank Traverse = Head; // We check if the bank exists or not
    bool BankExists = false;
    while (Traverse != NULL && !BankExists)
    { // finds the bank
        if (strcmp(Traverse->NameOfTradeBank, BankName) == 0)
        {
            BankExists = true;
            break;
        }
        Traverse = Traverse->next;
    }
    if (BankExists) //if the bank exists then perform Tarjan SCC on it
    {
        int currencycount = 0;
        PtrToCurrencyNode t = Traverse->CurrencyHead->next;
        for (; t; t = t->next)
        {
            currencycount++; //first calculate the number of currencies in the bank
        }
        int low[currencycount];
        int scccount = Tarjan(Traverse->G, low, currencycount); //then perform Tarjan using currencycount as input
        if (currencycount == scccount)                          //if number of SCCs is equal to number of currencies(vertices) then no cycle exists
        {

            printf("no cycle exists\n");
        }
        else //otherwise cycle exists
        {

            printf("cycle exists\n");
        }
        return;
    }
    else //if bank does not exist then print the error message
    {
        printf("Bank does not exist\n");
        return;
    }
}