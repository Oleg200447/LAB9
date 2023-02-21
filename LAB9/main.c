#include < stdio.h >
#include"Header.h"
#include <locale.h>
#include<stdlib.h>

#define NUM_TASKS_MENU 5
#define EXIT 6

int main()
{   
    setlocale(LC_ALL, "Rus");

    void (**menu)(int *size,...) =(void(**)(int *size,...))calloc(NUM_TASKS_MENU, sizeof(void(*)(int* size,...)));
    if (menu != NULL)
    {
        int num_shoes = numOfShoes();
        struct Shoes* mas = memoryForCatalog(num_shoes);
        getInfo(mas);
        menu[0] =&showCatalog;
        menu[1] =&addElementMenu;
        menu[2] =&deleteElementMenu;
        menu[3] =&sortOneFieldMenu;
        menu[4] =&sortTwoFieldMenu;

        int choise = 0;
        int task_choise = 0;

        do {             
            printf("  Menu:\n1.Show catalog.\n2.Add 1 pair.\n3.Delete 1 pair.\n4.Sort one field.\n5.Sort two fields.\n6.Exit.\nYour choise:");
            menuCorrect(&task_choise);
            system("cls");

            if (task_choise == EXIT)
            {
                free(menu);
                return 0;
            }
            if (task_choise == 2 || task_choise == 3)
            {
                menu[task_choise - 1](&num_shoes, &mas);
            }
            else
            {
                menu[task_choise - 1](&num_shoes, mas);
            }
            printf("\nDo you want to continue?(Yes-1/No-0):");
            chekerForContinue(&choise);
            system("cls");
        } while (choise == 1);                 
    }

    free(menu);

    return 0;
}
