#ifndef __CurrencyUI
#define __CurrencyUI

typedef struct DijkstraBankInfo DijkstraBankInfo;

struct DijkstraBankInfo // Structure for Dijkistra Algorithm
{
    int mincost;
    char TradeBankName[100];
};

PtrToCurrencyNode CreateEmptyCurrList();                                                         //creates a dummy node and returns it's value
int searchforcurrency(char *inputcurrency, PtrToCurrencyNode C);                                 //search for the input currency in the given currency linked list
void addcurrency(char *inputcurrency, int vertexid, PtrToCurrencyNode c);                        //add the input currency to the currency linked list
void deletecurrency(char *inputcurrency, PtrToCurrencyNode c);                                   //deletes the node from the given currency list
void printcurrencylist(PtrToCurrencyNode C);                                                     //prints currency list on the screen
void DeleteCurrList(PtrToCurrencyNode C);                                                        //frees pointers in the currency list
void AddTradeBank(char *BankName);                                                               //adds a new Tradebank to the linked list
void AddCurrencyExchange(char *BankName, char *Currency1, char *Currency2, int ConversionRate);  //adds an edge in the currency graph of a Tradebank
void RemoveCurrencyExchange(char *BankName, char *source, char *dest);                           //deletes an edge in the currency graph of a Tradebank
void RemoveTradeBank(char *BankName);                                                            //removes the Trade Bank selected and all the currencis and the graph that Trade Bank holds
void PrintTradeBankList();                                                                       //only prints name of Trade Banks
void PrintTradeBankList2();                                                                      //prints Trade Bank list with the currencies it holds
void AddCurrencyExchange1(char *BankName, char *Currency1, char *Currency2, int ConversionRate); //Updated Version of AddCurrenyExchange
void AddCurrencyToTradeBank(char *Bankname, char *inputcurrency);                                //checks if the input currency exists in the Trade Bank.If not then addes currency to it
void PrintTradeBankGraph(PtrToTradebank T);                                                      //this function prints the graph of a selected Trade Bank
void RemoveCurrencyFromTradeBank(char *BankName, char *inputcurrency);                           //this function removes the inputted currency from the inputted Trade Bank
void RemoveCurrencyExchange(char *BankName, char *Currency1, char *Currency2);                   //this function removes a currency exchange from the currency graph, if it exists
DijkstraBankInfo DijkstraOnBankList(char *sourcecurrency, char *destcurrency);                   //runs dijkistra on all the available Trade Banks and finds best conversion between the input currencies
void CycleCheckinTradeBank(char *BankName);                                                      // this function checks for cycle in the graph of a given trade bank by running Tarjan's Algorithm
                                                                                                 //and by comparing the number of Strongly Connected Components with number of Vertices.

#endif
