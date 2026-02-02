/*
 *
 * Created by cipiisekk
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define COLOR_BOLD "\033[1m"
#define ERROR_COLOR "\033[1;31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_CYAN "\033[36m"
#define COLOR_OFF  "\033[m"

struct crop {
    char name[20];
    int price;
    int sell;
    int stock;
    int is_planted;
};

void my_lower(char *s);
bool isSame(char *s1, char *s2);
bool plant(struct crop *actual_crop, int *money);
bool harvest(struct crop *actual_crop, int *money);
void printMenu(char *menu[]);
void nextDay(int *day, struct crop crops[], int size);
void error(char error[]);
void clearBuffer();
void printHarvest(struct crop crops[], int sizeOfCrops);
void printPlant(struct crop crops[], int sizeOfCrops);
bool back(char *choice);
void plantChoice(char *choice,struct crop crops[], int sizeOfCrops, bool *found);
void harvestChoice(char *choice,struct crop crops[], int sizeOfCrops, bool *found);

enum status {
    WAIT_COMMAND, WAIT_CROP, END
};

enum action {
    PLANT, HARVEST, NONE
};

// GLOBAL VARS
enum status status = WAIT_COMMAND;
enum action action = NONE;
int money = 100;
int day = 0;


int main(void)
{
    srand(time(NULL));

    bool found = false;
    char choice[20] = {0};

    char *menu[3] = {
        "plant",
        "harvest",
        "end"
    };

    struct crop crops[3] = {
        {"wheat", 5, 15, 0, 0},
        {"corn",8, 24, 0, 0},
        {"potatoes",10, 30, 0, 0}
    };
    int sizeOfCrops = sizeof(crops) / sizeof(crops[0]);

    nextDay(&day, crops, sizeOfCrops);
    printMenu(menu);

    do {
        scanf("%19s", choice);
        my_lower(choice);
        clearBuffer();

        switch (status) {
            case WAIT_COMMAND:
                if (isSame(choice, menu[0])) { // if choice is same as "plant"
                    printPlant(crops, sizeOfCrops);

                } else if (isSame(choice, menu[1])) { // if choice is same as "harvest"
                    printHarvest(crops, sizeOfCrops);

                } else if (isSame(choice, menu[2])) { // if choice is same as "END" 
                    status = END;
                    printf(ERROR_COLOR"OK! Ending the program...\n"COLOR_OFF);

                } else {
                    error("Unknown command!\n");
                    printMenu(menu);
                }

                break;

            case WAIT_CROP:
                switch (action) {
                case PLANT:
                        if (back(choice) == true) {
                            printMenu(menu);
                            break;
                        }
                        plantChoice(choice, crops, sizeOfCrops, &found);
                        if (found == false) {
                            error("Unknown crop!\n");
                            printMenu(menu);
                            break;
                        }
                        printMenu(menu);
                        break;
                case HARVEST:
                        if (back(choice) == true) {
                            printMenu(menu);
                            break;
                        }
                        harvestChoice(choice, crops, sizeOfCrops, &found);
                        if (found == false) {
                            error("Unknown crop!\n");
                            printMenu(menu);
                        }
                        printMenu(menu);
                        break;
                case NONE:
                        error("NONE as action!");
                        return 1;
                }
                break;

            case END:
                break;
        }

    } while (status != END);

    return 0;
}

    bool back (char *choice)
    {
        if (isSame(choice,"back")) {
            printf("going back..\n");

            status = WAIT_COMMAND;
            action = NONE;

            return true;
        }
        return false;
    }

    void harvestChoice(char *choice,struct crop crops[], int sizeOfCrops, bool *found){
        *found = false;
        for (int i = 0; i < sizeOfCrops; i++) {
            if (isSame(choice,crops[i].name)) {

                if(harvest(&crops[i], &money))
                    nextDay(&day, crops, sizeOfCrops);

                status = WAIT_COMMAND;
                action = NONE;
                *found = true;
                break;
            }
        }
    }

    void plantChoice(char *choice,struct crop crops[], int sizeOfCrops, bool *found)
    {
        *found = false;
        for (int i = 0; i < sizeOfCrops; i++) {
            if (isSame(choice ,crops[i].name)) {

                if(plant(&crops[i], &money))
                    nextDay(&day, crops, sizeOfCrops);

                status = WAIT_COMMAND;
                action = NONE;
                *found = true;
            }
        }
    }


    void printPlant(struct crop crops[], int sizeOfCrops)
    {
        action = PLANT;
        status = WAIT_CROP;

        printf(COLOR_GREEN"Menu of crops & their prices:\n"COLOR_OFF);
        for (int i = 0; i < sizeOfCrops;i++) {
            printf("- %s cost: %d money\n", crops[i].name, crops[i].price);
        }
        printf(COLOR_GREEN"Type "COLOR_OFF COLOR_BOLD"back"COLOR_OFF COLOR_GREEN" OR what crop u want to plant: "COLOR_OFF);
    }

    void printHarvest (struct crop crops[], int sizeOfCrops)
    {
        action = HARVEST;
        status = WAIT_CROP;

        printf(COLOR_YELLOW"Menu of crops & their sell prices: \n"COLOR_OFF);
            for (int i = 0; i < sizeOfCrops;i++) {
                printf("- %s sell price: %d money, in stock %dx\n"
                       , crops[i].name, crops[i].sell, crops[i].stock);
            }

            printf(COLOR_YELLOW"Type "COLOR_OFF COLOR_BOLD"back"COLOR_OFF COLOR_YELLOW" OR what crop u want to harvest: "COLOR_OFF);
    }

    void clearBuffer(void) 
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF){}
    }

    void error(char error[]) 
    {
        printf(ERROR_COLOR"ERROR"COLOR_OFF);
        printf(": %s\n", error);
    }


    void nextDay(int *day, struct crop crops[], int sizeOfCrops)
    {
        *day += 1; // zvysi se den
        for (int i = 0; i < sizeOfCrops; i++) { // presune se vsechno planted do stock
            crops[i].stock += crops[i].is_planted;
            crops[i].is_planted = 0;
        }
    
    }

    void printMenu(char *menu[]) 
    {
        printf(COLOR_BOLD"Menu of commands:\n"COLOR_OFF);
                    printf(COLOR_GREEN"- %s\n"COLOR_OFF,menu[0]);
                    printf(COLOR_YELLOW"- %s\n"COLOR_OFF,menu[1]);
                    printf(COLOR_CYAN"- %s\n"COLOR_OFF,menu[2]);
        printf(COLOR_BOLD"Type what u want to do: "COLOR_OFF);
    }

    bool harvest(struct crop *actual_crop, int *money)
    {
        if (actual_crop->stock == 0) {
            printf(COLOR_BOLD"ERROR: "COLOR_OFF);
            printf("There is 0 %s in ur stock\n", actual_crop->name);
            return false;
        } else {
            *money+= (actual_crop->sell * actual_crop->stock);
            printf("OK! Harvested %d %s, money added: %d\n",actual_crop->stock, actual_crop->name, (actual_crop->sell * actual_crop->stock));
            actual_crop->stock = 0;
            return true;
        }
    }


    bool plant(struct crop *actual_crop, int *money)
    {
        int howMuch = 0;
        printf("How much %s u want to plant: ", actual_crop->name);
        scanf("%d", &howMuch);
        clearBuffer();
        if (howMuch <= 0) {
            printf(COLOR_BOLD"ERROR: "COLOR_OFF);
            printf("U can't plant %d of %s\n Now is set to: 1", howMuch, actual_crop->name);
            howMuch = 1;
        }
        if (*money >= (actual_crop->price * howMuch)) {
            *money-= (actual_crop->price * howMuch);
            actual_crop->is_planted+=howMuch;
            return true;
        } else {
            printf("U dont have enought money\nUr money: %d, Cost of %dx %s: %d\n", *money, howMuch, actual_crop->name, actual_crop->price * howMuch);
            return false;
        }
    }


    bool isSame(char *s1, char *s2)
    {
        while (*s2 != '\0' && *s1 != '\0') {
            if (*s1 != *s2)
                return false;

            s1++;
            s2++;
        }
        if (*s1 != *s2)
            return false;
        return true;
    }


    void my_lower(char *s)
    {
        while (*s != '\0') {
            *s += (*s >= 'A' && *s <= 'Z') ? ('a' - 'A'): 0;
            s++;
        }
    }
