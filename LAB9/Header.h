#pragma once

int levelTen(int degree);

int reverseNum(int num1, int num_size);

int numOfShoes();

struct Shoes* memoryForCatalog(int size);

int chekerForClass(const char* str, FILE* site);

int findPrice(FILE* site);

void getPrices(struct Shoes* mas, FILE* site);

enum firm findFirm(FILE* site);

void getFirms(FILE* site, struct Shoes* mas);

void getName(FILE* site, struct Shoes* mas);

char* findName(FILE* site);

char* memoryForNames(int size);

void getInfo(struct Shoes* mas);

void menuCorrect(int* task);

void chekerForContinue(int* num);



void showCatalog(struct Shoes* mas, int *size);


void deleteElement(struct Shoes** mas, int number, int *size);

void deleteElementMenu(struct Shoes* mas, int* size);



void sortPrice(struct Shoes* mas, int size);

void sortName(struct Shoes* mas, int size);

void sortBrend(struct Shoes* mas, int size);



void sortPriceAfterSort(struct Shoes* mas, int size, int sortBefore);

void changePriceAfterBrend(struct Shoes* mas, int counter);

void changePriceAfterName(struct Shoes* mas, int counter);

void sortBrendAfterSort(struct Shoes* mas, int size, int sortBefore);

void changeBrendAfterName(struct Shoes* mas, int counter);

void changeBrendAfterPrice(struct Shoes* mas, int counter);

void sortNameAfterSort(struct Shoes* mas, int size, int sortBefore);

void changeNameAfterBrend(struct Shoes* mas, int counter);

void changeNameAfterPrice(struct Shoes* mas, int counter);


void sortOneField(struct Shoes* mas, int* size);

void sortTwoField(struct Shoes* mas, int* size);

void addPair(struct Shoes* mas, int* size);

void memoryNew(struct Shoes** mas, int* size);