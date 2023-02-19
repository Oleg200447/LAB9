#include < stdio.h >
#include"Header.h"
#include <locale.h>
#include<stdlib.h>

#define NUM_TASKS_MENU 4
#define EXIT 5

int main()
{   
    setlocale(LC_ALL, "Rus");

    void (**menu)(struct Shoes* mas, int *size) =(void(**)(struct Shoes* mas, int *size))calloc(NUM_TASKS_MENU, sizeof(void(*)(struct Shoes* mas, int* size)));
    if (menu != NULL)
    {
        int num_shoes = numOfShoes();
        struct Shoes* mas = memoryForCatalog(num_shoes);
        getInfo(mas);
            
        menu[0] =showCatalog;
        menu[1] = deleteElementMenu;
        menu[2] = sortOneField;
        menu[3] = sortTwoField;
        int choise = 0, task_choise = 0;

        do {             
            printf("  Menu:\n1.Show catalog.\n2.Delete 1 pair.\n3.Sort one field.\n4.Sort two fields.\n5.Exit.\nYour choise:");
            menuCorrect(&task_choise);
            system("cls");

            if (task_choise == EXIT)
            {
                free(menu);
                return 0;
            }
            menu[(task_choise - 1)](mas, &num_shoes);

            printf("\nDo you want to continue?(Yes-1/No-0):");
            chekerForContinue(&choise);
            system("cls");
        } while (choise == 1);                 
    }

    free(menu);

    return 0;
}
