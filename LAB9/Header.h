#pragma once

int levelTen(int degree);

int reverseNum(int num1, int num_size);

int numOfShoes(void);

struct Shoes* memoryForCatalog(int size);

int chekerForClass(const char* str, FILE* site);

int findPrice(FILE* site);

void getPrices(struct Shoes* mas, FILE* site);

enum firm findFirm(FILE* site);

void getFirms(FILE* site, struct Shoes* mas);

void getName(FILE* site, struct Shoes* mas);

char* findName(FILE* site, int counter, struct Shoes* mas);

char* memoryForNames(int size);

void getInfo(struct Shoes* mas);

void menuCorrect(int* task);

void chekerForContinue(int* num);

int chekerEndSite(FILE* site);

void showCatalog(const int *size, const struct Shoes* mas);


void deleteElement(struct Shoes* *mas, unsigned int number, int *size);

void deleteElementMenu( int* size, struct Shoes** mas);


void sortOneFieldMenu( const int* size, struct Shoes* mas);
void sortOneField(struct Shoes* mas, int size, int choise1);


void sortTwoFieldMenu(const int* size, struct Shoes* mas);

void sortTwoField(struct Shoes* mas, int size, int choise1, int choise2);

void addElementMenu(int* size, struct Shoes** mas);

int variantToSort(int field, int counter, const struct Shoes* mas);

enum firm inputBrend();

enum firm ChekerBrend(const char* str);

void chekerBadCod(char** str, int* size);

void showName(const struct Shoes* mas, int counter);