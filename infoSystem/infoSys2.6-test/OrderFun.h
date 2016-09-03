#ifndef OrderFun_H
#define OrderFun_H
#define __saveExternal__//this determine whether the class can be saved in external file.

#include "CDataBaseView.h"
#include "CDataBase.h"
#include "share.h"
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<iomanip>
using namespace std;
typedef bool (*POrderFun)();

//assistant function declare:
bool askIfSave();bool showMenu();bool saveDataBase();bool readDataBase();bool initDB();bool initAll();

//order function declare:
bool menu();bool resetAll();bool showAll();bool showGivenPerson();bool showGivenType();bool showGiveTypePerson();bool addPerson();bool addType();bool delPerson();bool delType();bool setPeron();bool renameType();bool save();bool quit();bool help();bool clear();bool changePrintAfter();

//constant:
#define MAX_INPUT_BUFFER 100
#define DEFFAULT_FILE_NAME "infoSystem.dat"
#define MAX_LEN_ORDER 20
#define MAX_LEN_DESCRIPT 100
#define MAX_SIZE_TYPE MAX_INPUT_BUFFER
const int numOrders=17;
const char tag[]="Eric's infosystem";


//global variables:
extern char *key;
extern bool isQuit;
extern char filePath[100];
extern CDataBase *db;
extern CDataBaseView dataBase;;
extern bool printAfter;
extern char descriptOrders[][MAX_LEN_DESCRIPT+1];
extern POrderFun orderFuns[];
extern char accessOrders[][MAX_LEN_ORDER+1];

#endif