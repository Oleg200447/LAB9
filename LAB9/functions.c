#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Header.h"
#include <locale.h>

#define KB 1024
#define NUM_BRENDS 4

#define EQUAL 2
#define NEED_CHANGE 1
#define NO_CHANGE 0 

#define FIRST_FIELD 0
#define SECOND_FIELD 1
#define THIRD_FIELD 2

void chekerPrice(int* num)
{
    while ((scanf_s("%d", num)) != 1 || getchar() != '\n' || *num < 0)
    {
        printf("Intput correct price:");
        rewind(stdin);
    }
}

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
    while ((scanf_s("%d", task)) != 1 || *task < 1 || *task>6 || getchar() != '\n')
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

void correctChoiseBrend(int* num, int num_brends)
{
    while ((scanf_s("%d", num)) != 1 || *num < 1 || *num>(num_brends -1) || getchar() != '\n')
    {
        printf("Make right choise(0-%d):", num_brends-1);
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
    int storer1 = 0;

    for (int i = 0, j = num_size - 1; i <= num_size; j--, i++)
    {
        storer1 = num1 / levelTen(j);
        num2 += storer1 * levelTen(i);
        num1 -= storer1 * levelTen(j);
    }

    return num2;
}

int chekerEndSite(FILE* site)
{
    fgetc(site);

    if (feof(site))
    {
        return 1;
    }
    else
    {
        fseek(site, -1, SEEK_CUR);
        return 0;
    }
}

int numOfShoes(void)
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

            if (storer == *class_site && chekerForClass(class_site, site) == strlen(class_site))
            {              
                    size++;               
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
    NO_BREND
};



int findPrice(FILE* site)
{
    char storer = fgetc(site);

    while (storer != '>')
        storer = fgetc(site);
    storer = fgetc(site);

    int price_rev = 0;
    int size_price = 0;
    int price = 0;

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

        if (storer == *class_sale && chekerForClass(class_sale, site) == strlen(class_sale))
        {           
            mas[num_shoes_counter].price = findPrice(site);
            num_shoes_counter++;              
                   
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
    return NO_BREND;
}

void getFirms(FILE* site, struct Shoes* mas)
{

    const char* brand_name_class = "x-product-card-description__brand-name";

    rewind(site);

    int num_shoes_counter = 0;

    while (!feof(site))
    {
        char storer = fgetc(site);

        if (storer == *brand_name_class) 
        {
            if (chekerForClass(brand_name_class, site) == strlen(brand_name_class))
            {
                mas[num_shoes_counter].brend = findFirm(site);
                num_shoes_counter++;               
            }
        }
    }
}

void chekerBadCod(char** str,int *size)
{  
       for (int i = 0; i < *size+1; i++)
       {
            if (*(*str + i) == '&')
            {
                int cheker = 1;
                int counter = i;
                while (*(*str + counter) != ';' && counter < *size+1)
                {
                    counter++;
                    cheker++;
                }
                if (*(*str + counter) != ';')
                    break;
                for (int j = i; j < *size+1; j++)
                {
                    *(*str + j) = *(*str + j + cheker);
                }
                *size -= cheker;
            }
       }
       char* storer = (char*)realloc(*str, (*size+1) * sizeof(char));
       if (storer != NULL)
       {
           *str = storer;
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
    fsetpos(site, &pos);

    storer = fgetc(site);
    for(int i=0;i<size-1;i++)
    {
        *(str + i) = storer;

        storer = fgetc(site);
    }
    chekerBadCod(&str, & size);
    mas[counter].model = memoryForNames(size);
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

        if (storer == *type_name_class && chekerForClass(type_name_class, site) == strlen(type_name_class))
        {         
            mas[num_shoes_counter].model = findName(site, num_shoes_counter,mas);
            num_shoes_counter++;             
        }
    }
    
}

void showCatalog(const int* size, const struct Shoes* mas)
{
    printf("\tName:\t\t\t\t\t\tBrend:\t\t\tPrice:\n\n");
    for (int i = 0; i < *size; i++)
    {
        printf("%d.\t", i+1);
        if (mas != NULL)
        {
            fputs(mas[i].model, stdout);
            int len = strlen(mas[i].model);
            if (len <= 7)
                printf("\t\t\t\t\t\t");
            if (len >= 16 && len < 24)
                printf("\t\t\t\t");
            if (len < 16 && len > 7)
                printf("\t\t\t\t\t");
            if (len >= 24 && len < 27)
                printf("\t\t\t");
            if (len >= 27 && len < 30)
                printf("\t\t\t");
            if (len >= 30 && len < 40)
                printf("\t\t");
            if (len >= 40)
                printf("\t");

            const static char* BrendForPrint[NUM_BRENDS] = { "Adidas","Nike","Puma","Nobrend" };
            if (mas[i].brend >= 0 && mas[i].brend < NUM_BRENDS)
            {
                printf("%s\t\t\t", BrendForPrint[mas[i].brend]);
            }
            printf("%dð.\n\n", mas[i].price);
        }
    }
}

void deleteElement(struct Shoes**mas, int number,int *size)
{
    if (mas != NULL)
    {
        
        
        for (int i = number; i < *size; i++)
        {
            mas[0][i - 1] = mas[0][i];
        }
        
        (*size)--;


        struct Shoes* storer = (struct Shoes*)realloc(*mas, (*size) * sizeof(struct Shoes));       
        if (storer != NULL)
        {
            *mas = storer;
        }
    }
}

int changeNeed(const char* str1, const char* str2)
{
    size_t size;
    if (strlen(str1) > strlen(str2))
        size = strlen(str2);
    else
        size = strlen(str1);
    for (int i = 0; i < size+1; i++)
    {
        if (*(str1 + i) > *(str2 + i))
            return NEED_CHANGE;
        if (*(str1 + i) < *(str2 + i))
            return NO_CHANGE;
    }
    return EQUAL;
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

void sortOneField(struct Shoes* mas,int size,int choise1)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size - 1; j++)
            if (variantToSort(choise1, j, mas) == 1 )
            {
                struct Shoes storer = mas[j];
                mas[j] = mas[j + 1];
                mas[j + 1] = storer;
            }
}

void sortOneFieldMenu( int* size, struct Shoes* mas)
{
    int choise = 0;
    printf("By what field do you want to sort?(Brend(0)/Name(1)/Price(2)).\nYour choise:");
    correctChoiseForSort(&choise);

    sortOneField(mas, *size, choise);

    showCatalog(size,mas);
}


void deleteElementMenu( int* size, struct Shoes**mas)
{
    int num = 0;
    printf("What pair you want delete?\nYour choise(1-%d):",*size);
    correctChoiseDelete(&num, *size);

    if (*mas != NULL)
    {
        deleteElement(mas, num, size);
    }

    system("cls");
    showCatalog(size,*mas);
}

char* inputStr()
{
   char *str= (char*)calloc(KB, sizeof(char));
   if (str != NULL)
   {
       do {
           printf("Input name: ");
           rewind(stdin);

           gets_s(str, KB - 1);
           rewind(stdin);
       } while (strlen(str) < 1);
  
       
       if (str[0] <= 'z' && str[0] >= 'a')
       {
           str[0] = str[0] - ('a' - 'A');
       }

       char*storer= (char*)realloc(str, (strlen(str) + 1) * sizeof(char));
       if (storer != NULL)
       {
           str = storer;
       }
   }
   return str;
}

void addElementMenu( int* size, struct Shoes** mas)
{  
    (*size)++;
    struct Shoes* storer= (struct Shoes*)realloc(*mas, (*size) * sizeof(struct Shoes));
    if (storer != NULL)
    {
        *mas = storer;
    }

    if (mas[0] != NULL)
    {
        mas[0][*size - 1].model = inputStr();

        printf("Input price: ");
        chekerPrice(&mas[0][*size - 1].price);


        printf("Input brend: ");
        mas[0][*size - 1].brend = inputBrend();

    }
}

enum firm inputBrend()
{
    char* str = (char*)calloc(KB, sizeof(char));
    if (str != NULL)
    {
        do {
            rewind(stdin);
            gets_s(str, KB - 1);
            rewind(stdin);
        } while (strlen(str) < 1);

        char* storer = (char*)realloc(str, (strlen(str) + 1) * sizeof(char));
        if (storer != NULL)
        {
            str = storer;
        }
    }

    return ChekerBrend(str);
}

enum firm ChekerBrend(const char* str)
{
    const static char* BrendForInput[NUM_BRENDS - 1] = { "adidas","nike","puma" };

    for (int i = 0; i <NUM_BRENDS-1; i++)
    {
        int cheker = 0;
        for (int j = 0; j < strlen(BrendForInput[i]); j++)
        {
            char storer = BrendForInput[i][j] - ('a' - 'A');
            if (str!=NULL && (BrendForInput[i][j] == str[j] || (str[j] == storer)))
            {
                cheker++;
            }
            if (cheker == strlen(BrendForInput[i]))
                return i;
        }
        
    }

    return NO_BREND;
}

int variantToSort(int field, int counter, struct Shoes* mas)
{
    if (field == FIRST_FIELD)
    {
        if (mas[counter].brend > mas[counter + 1].brend)
        {
            return NEED_CHANGE;
        }
        if (mas[counter].brend == mas[counter + 1].brend)
        {
            return EQUAL;
        }
    }

    if (field == SECOND_FIELD)
    {
        return changeNeed(mas[counter].model, mas[counter+1].model);

    }

    if (field == THIRD_FIELD)
    {
        if (mas[counter].price > mas[counter + 1].price)
        {
            return NEED_CHANGE;
        }
        if (mas[counter].price == mas[counter + 1].price)
        {
            return EQUAL;
        }

    }

    return NO_CHANGE;
}

void sortTwoField(struct Shoes* mas, int size, int choise1, int choise2)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size - 1; j++)
            if (variantToSort(choise1, j, mas) == 1 || (variantToSort(choise1, j, mas) == 2 && variantToSort(choise2, j, mas) == 1))
            {
                struct Shoes storer = mas[j];
                mas[j] = mas[j + 1];
                mas[j + 1] = storer;
            }
}

void sortTwoFieldMenu(int* size, struct Shoes* mas)
{
    int choise1 = 0;
    int choise2 = 0;
    printf("Choose first and second fields:(Brend(0)/Name(1)/Price(2)).\n");
    printf("First choise:");
    correctChoiseForSort(&choise1);
    printf("Second choise:");
    correctChoiseForSortTwoFields(choise1, &choise2);

    sortTwoField(mas, *size, choise1, choise2);

    system("cls");
    showCatalog(size,mas);
}

