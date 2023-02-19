#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Header.h"

#define KB 1024
#define NUM_BRENDS 4

void chekerForContinue(int* num)
{
    while ((scanf_s("%d", num)) != 1 || getchar() != '\n' || *num < 0 || *num > 1)
    {
        printf("Intput correct number:");
        rewind(stdin);
    }
}

void correctChoiseForSort(int* num)
{
    while ((scanf_s("%d", num)) != 1 || getchar() != '\n' || *num<0 || *num > 2)
    {
        printf("Intput correct number:");
        rewind(stdin);
    }
}

void menuCorrect(int* task)
{
    while ((scanf_s("%d", task)) != 1 || *task < 1 || *task>5 || getchar() != '\n')
    {
        printf("Make right choise(1-5):");
        rewind(stdin);
    }
}

void correctChoiseForSortTwoFields(int num1,int *num2)
{
    while ((scanf_s("%d", num2)) != 1 || getchar() != '\n' || *num2 < 0 || *num2 > 2|| num1==*num2)
    {
        if (num1 == *num2)
            printf("They can not be identical,choose another one.\n");
       
        printf("Intput correct number:");
        rewind(stdin);
    }
}

void correctChoiseDelete(int *num,int size)
{
    while ((scanf_s("%d", num)) != 1 || *num < 1 || *num>size || getchar() != '\n')
    {
        printf("Make right choise(1-%d):",size);
        rewind(stdin);
    }
}

int levelTen(int degree)
{
    int num = 1;
    for (int i = 1; i <= degree; i++)
    {
        num *= 10;
    }
    return num;
}

char* memoryForNames(int size)
{
    char* mas;

    mas = (char*)calloc(size + 1, sizeof(char));

    return mas;
}

int reverseNum(int num1, int num_size)
{
    int num2 = 0;
    int storer1 = 0, storer2 = 0;

    for (int i = 0, j = num_size - 1; i <= num_size; j--, i++)
    {
        storer1 = num1 / levelTen(j);
        num2 += storer1 * levelTen(i);
        num1 -= storer1 * levelTen(j);
    }

    return num2;
}



int numOfShoes( )
{
    FILE* site;
    errno_t err = fopen_s(&site, "C:\\Users\\Oleg\\Desktop\\Project\\site2.html", "r+");
    
    if (err != 0)
    {
        printf("Cant open file");
        return -1;
    }
    else
    {
        const char* class_site = "class=\"x-product-card-description\"";
        int size = 0;

        rewind(site);

        while (!feof(site))
        {
            int cheker = 0;
            char storer = fgetc(site);

            if (storer == *class_site)
            {
                if (chekerForClass(class_site, site) == strlen(class_site))
                {
                    size++;
                }
            }
        }
        fclose(site);
        return size;
    }
}



struct Shoes {

    enum firm brend;
    char* model;
    int price;

};



struct Shoes* memoryForCatalog(int size)
{
    struct Shoes* mas = (struct Shoes*)calloc(size, sizeof(struct Shoes));

    return mas;
}

int chekerForClass( const char* str, FILE* site)
{
    int cheker = 1;
    char storer = fgetc(site);

    while (storer == *(str + cheker) || storer == ' ' || storer == '\0' || storer == '\n')
    {
        if (storer == ' ' || storer == '\0' || storer == '\n')
        {
            cheker--;
        }

        cheker++;
        storer = fgetc(site);
    }

    return cheker;
}


enum firm {
    ADIDAS,
    NIKE,
    PUMA,
    NOFIRM
};



int findPrice(FILE* site)
{
    char storer = fgetc(site);

    while (storer != '>')
        storer = fgetc(site);
    storer = fgetc(site);

    int price_rev = 0, size_price = 0, price = 0;

    while (storer != '.')
    {
        price_rev += (storer - '0') * levelTen(size_price);

        size_price++;

        storer = fgetc(site);
    }

    price = reverseNum(price_rev, size_price);

    return price;

}



void getPrices(struct Shoes* mas, FILE* site)
{
    const char* class_sale = "x-product-card-description__price-WEB8507_price_no_bold";

    rewind(site);

    int num_shoes_counter = 0;

    while (!feof(site))
    {
        char storer = fgetc(site);

        if (storer == *class_sale) // x
        {           
            if (chekerForClass(class_sale, site) == strlen(class_sale))
            {
                mas[num_shoes_counter].price = findPrice(site);
                num_shoes_counter++;              
            }          
        }
    }
}

char* findStr(FILE* site)
{
    char* str = (char*)calloc(KB, sizeof(char));
    
    char  storer = fgetc(site);


    int counter = 0;
    while (storer != '<')
    {
        if (str != NULL)
        {
            *(str + counter) = storer;
        }
        counter++;
        storer = fgetc(site);

    }

    char* str_storer= (char*)realloc(str, (counter + 1) * sizeof(char));
    if (str_storer != NULL)
    {
        str = str_storer;
    }

    return str;
}

enum firm findFirm(FILE *site)
{
    char storer = fgetc(site);
    while (storer != '>')
        storer = fgetc(site);
  
    const static char* Brends[] = { "adidas","Nike","PUMA"};
    char* str = findStr(site);

    for (int i = 0; i < 3; i++)
    {      
         if (strcmp(str, *(Brends + i)) == 0)
         {
             free(str);
            return i;
         }   
    }
    free(str);
    return NOFIRM;
}

void getFirms(FILE* site, struct Shoes* mas)
{

    const char* brand_name_class = "x-product-card-description__brand-name";

    rewind(site);

    int num_shoes_counter = 0;

    while (!feof(site))
    {
        char storer = fgetc(site);

        if (storer == *brand_name_class) // <
        {
            if (chekerForClass(brand_name_class, site) == strlen(brand_name_class))
            {
                mas[num_shoes_counter].brend = findFirm(site);
                num_shoes_counter++;               
            }
        }
    }
}

char* findName(FILE* site,int counter, struct Shoes* mas)
{
    char storer = fgetc(site);
    while (!((storer >= 'a' && storer <= 'z') || (storer >= 'A' && storer <= 'Z')||(storer>='0'&&storer<='9')))
        storer = fgetc(site);
   
    fseek(site, -1, SEEK_CUR);
    char* str;
    fpos_t pos;
    fgetpos(site, &pos);
    int size = 0;

    while (storer != '<')
    {
        size++;  
        storer = fgetc(site);
    }

    str = memoryForNames(size);
    mas[counter].model= memoryForNames(size);
    fsetpos(site, &pos);

    storer = fgetc(site);
    for(int i=0;i<size-1;i++)
    {
        *(str + i) = storer;

        storer = fgetc(site);
    }
    
    return str;
}

void getName(FILE* site, struct Shoes* mas)
{

    const char* type_name_class = "x-product-card-description__product-name";

    rewind(site);

    int num_shoes_counter = 0;

    while (!feof(site))
    {
        char storer = fgetc(site);

        if (storer == *type_name_class) // <
        {
            if (chekerForClass(type_name_class, site) == strlen(type_name_class))
            {
                mas[num_shoes_counter].model = findName(site, num_shoes_counter,mas);
                num_shoes_counter++;             
            }
        }
    }
}

void showCatalog(struct Shoes* mas,int* size)
{
    printf("\tName:\t\t\t\t\t\tBrend:\t\t\tPrice:\n\n");
    for (int i = 0; i < *size; i++)
    {
        printf("%d.\t", i+1);
        if (mas != NULL)
        {
            fputs(mas[i].model, stdout);
            if (strlen(mas[i].model) <= 7)
                printf("\t\t\t\t\t\t");
            if (strlen(mas[i].model) >= 16 && strlen(mas[i].model) < 24)
                printf("\t\t\t\t");
            if (strlen(mas[i].model) < 16 && strlen(mas[i].model) > 7)
                printf("\t\t\t\t\t");
            if (strlen(mas[i].model) >= 24 && strlen(mas[i].model) < 27)
                printf("\t\t\t");
            if (strlen(mas[i].model) >= 27 && strlen(mas[i].model) < 30)
                printf("\t\t\t");
            if (strlen(mas[i].model) >= 30 && strlen(mas[i].model) < 40)
                printf("\t\t");
            if (strlen(mas[i].model) >= 40)
                printf("\t");


            const static char* BrendForPrint[NUM_BRENDS] = { "Adidas","Nike","Puma","No brend(pal)" };
            if(mas[i].brend>=0 && mas[i].brend< NUM_BRENDS)
            printf("%s\t\t\t", BrendForPrint[mas[i].brend]);


            printf("%dð.\n\n", mas[i].price);
        }
    }
}

void deleteElement(struct Shoes* mas, int number,int *size)
{

    for (int i = number; i < *size; i++)
    {
        if (mas != NULL && (mas+i)!=NULL && i>1&&i<60)
            *(mas+(i-1)) = *(mas+i);
    }

    (*size)--;

    if (mas != NULL)
    {
        struct Shoes* storer = (struct Shoes*)realloc(mas, (*size) * sizeof(struct Shoes));
        if (storer != NULL)
        {
            mas = storer;
        }
    }

    
}

void sortPrice(struct Shoes* mas, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size-1; j++)
        {
            if (mas[j].price > mas[j + 1].price)
            {
                struct Shoes storer = mas[j];
                mas[j] = mas[j + 1];
                mas[j + 1] = storer;
            }

        }
    }
}

int changeNeed(char* str1, char* str2)
{
    size_t size;
    if (strlen(str1) > strlen(str2))
        size = strlen(str2);
    else
        size = strlen(str1);
    for (int i = 0; i < size+1; i++)
    {
        if (*(str1 + i) > *(str2 + i))
            return 1;
        if (*(str1 + i) < *(str2 + i))
            return 0;
    }
    return 0;
}

void sortName(struct Shoes* mas, int size)
{

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (changeNeed(mas[j].model, mas[j + 1].model) == 1)
            {
                struct Shoes storer = mas[j];
                mas[j] = mas[j + 1];
                mas[j + 1] = storer;
            }
        }
    }
}

void sortBrend(struct Shoes* mas, int size)
{

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (mas[j].brend> mas[j+1].brend)
            {
                struct Shoes storer = mas[j];
                mas[j] = mas[j + 1];
                mas[j + 1] = storer;
            }
        }
    }
}

void changePriceAfterBrend(struct Shoes* mas,int counter)
{
    if (mas[counter].brend == mas[counter + 1].brend)
    {
        if (mas[counter].price > mas[counter+ 1].price)
        {
            struct Shoes storer = mas[counter];
            mas[counter] = mas[counter + 1];
            mas[counter + 1] = storer;
        }
    }

}

void changePriceAfterName(struct Shoes* mas, int counter)
{
    if (strcmp(mas[counter].model, mas[counter + 1].model)==0)
    {
        if (mas[counter].price > mas[counter + 1].price)
        {
            struct Shoes storer = mas[counter];
            mas[counter] = mas[counter + 1];
            mas[counter + 1] = storer;
        }
    }

}


void sortPriceAfterSort(struct Shoes* mas, int size, int sortBefore)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (sortBefore == 0)
            {
                changePriceAfterBrend(mas, j);               
            }
            if (sortBefore == 1)
            {
                changePriceAfterName(mas, j);
            }
        }
    }
}


void changeBrendAfterPrice(struct Shoes* mas, int counter)
{
    if (mas[counter].price == mas[counter + 1].price)
    {
        if (mas[counter].brend > mas[counter + 1].brend)
        {
            struct Shoes storer = mas[counter];
            mas[counter] = mas[counter + 1];
            mas[counter + 1] = storer;
        }
    }

}

void changeBrendAfterName(struct Shoes* mas, int counter)
{
    if (strcmp(mas[counter].model, mas[counter + 1].model) == 0)
    {
        if (mas[counter].brend > mas[counter+ 1].brend)
        {
            struct Shoes storer = mas[counter];
            mas[counter] = mas[counter + 1];
            mas[counter + 1] = storer;
        }
    }
}


void sortBrendAfterSort(struct Shoes* mas, int size, int sortBefore)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (sortBefore == 1)
            {
                changeBrendAfterName(mas, j);
            }
            if (sortBefore == 2)
            {
                changeBrendAfterPrice(mas, j);
            }
        }
    }
}





void changeNameAfterPrice(struct Shoes* mas, int counter)
{
    if (mas[counter].price == mas[counter + 1].price)
    {
        if (changeNeed(mas[counter].model, mas[counter + 1].model) == 1)
        {
            struct Shoes storer = mas[counter];
            mas[counter] = mas[counter + 1];
            mas[counter + 1] = storer;
        }
    }
}

void changeNameAfterBrend(struct Shoes* mas, int counter)
{
    if (mas[counter].brend == mas[counter + 1].brend)
    {
        if (changeNeed(mas[counter].model, mas[counter + 1].model) == 1)
        {
            struct Shoes storer = mas[counter];
            mas[counter] = mas[counter + 1];
            mas[counter + 1] = storer;
        }
    }
}

void sortNameAfterSort(struct Shoes* mas, int size, int sortBefore)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (sortBefore == 0)
            {
                changeNameAfterBrend(mas, j);
            }
            if (sortBefore == 2)
            {
                changeNameAfterPrice(mas, j);
            }
        }
    }
}


void getInfo(struct Shoes* mas)
{
    FILE* site;
    errno_t err = fopen_s(&site, "C:\\Users\\Oleg\\Desktop\\Project\\site2.html", "r+");
    if (err != 0)
    {
        printf("Cant open file");
    }
    else
    {
        getName(site, mas);
        getFirms(site, mas);
        getPrices(mas, site);

        fclose(site);
    }
}



void sortOneField(struct Shoes* mas, int* size)
{
    int choise1 = 0;
    printf("By what field do you want to sort?(Brend(0)/Name(1)/Price(2)).\nYour choise:");
    correctChoiseForSort(&choise1);
    if (choise1 == 0)
        sortBrend(mas, *size);
    if (choise1 == 1)
        sortName(mas, *size);
    if (choise1 == 2)
        sortPrice(mas, *size);
    showCatalog(mas, size);
}

void sortTwoField(struct Shoes* mas, int* size)
{
    int choise1 = 0, choise2 = 0;
    printf("Choose first and second fields:(Brend(0)/Name(1)/Price(2)).\n");
    printf("First choise:");
    correctChoiseForSort(&choise1);
    printf("Second choise:");
    correctChoiseForSortTwoFields(choise1, &choise2);

    switch (choise1)
    {
    case 0:
        sortBrend(mas, *size);
        break;
    case 1:
        sortName(mas, *size);
        break;
    case 2:
        sortPrice(mas, *size);
        break;
    }

    switch (choise2)
    {
    case 0:
        sortBrendAfterSort(mas, *size, choise1);
        break;
    case 1:
        sortNameAfterSort(mas, *size, choise1);
        break;
    case 2:
        sortPriceAfterSort(mas, *size, choise1);
        break;
    }
    
    system("cls");
    showCatalog(mas, size);
}


void deleteElementMenu(struct Shoes* mas, int* size)
{
    int num = 0;
    printf("What pair you want delete?\nYour choise(1-%d):",*size);
    correctChoiseDelete(&num, *size);

    if (mas != NULL)
    {
        deleteElement(mas, num, size);
    }

    system("cls");
    showCatalog(mas, size);
}

