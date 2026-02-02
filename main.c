/*
 * TODO:
 *
 * - Zlepseni algo apod.
 * Pridat pseudo-random eventy kazdy den
 * Vylepsit promene a algo, aby to bylo co nejmin zatezujici pro pamet:]
 *
 * - Zkrasleni kodu
 * Pridat commenty do kodu XD
 * Udelat kod vice citelny
 * Udelat prehlednejsi menu apod. pro bettr UX
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define COLOR_BOLD  "\033[1m"
#define ERROR_COLOR "\033[1;31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_CYAN "\033[36m"
#define COLOR_OFF   "\033[m"

struct crop {
    char name[20];
    int price;
    int sell;
    int warehouse;
    int is_planted;
};

void lower(char *s);
bool isSame(char *s1, char *s2);
bool plant(struct crop *actual_crop, int *money);
bool harvest(struct crop *actual_crop, int *money);
void printMenu(char *menu[], int size);
void nextDay(int *day, struct crop crops[], int size);
void printMoney(int money);
void error(char error[]);
void clearBuffer();


enum status {
    WAIT_COMMAND, WAIT_CROP, END
};

enum action {
    PLANT, HARVEST, NONE
};

enum status status = WAIT_COMMAND;
enum action action = NONE;


int main(void)
{
    bool found = false;
    int money = 100;
    int day = 0;

    char choice[20] = {0};

    char *menu[3] = {
        "plant",
        "harvest",
        "end"
    };
    int sizeOfMenu = (sizeof(menu) / sizeof(menu[0]));

    struct crop crops[4] = {
        {"wheat", 5, 15, 0, 0},
        {"corn",8, 24, 0, 0},
        {"potatoes",10, 30, 0, 0}
    };
    int sizeOfCrops = sizeof(crops) / sizeof(crops[0]);

    nextDay(&day, crops, sizeOfCrops);
    printMoney(money);
    printMenu(menu, sizeOfMenu);

    do {
        scanf("%19s", choice);
        lower(choice);
        clearBuffer();

        switch (status) {
            case WAIT_COMMAND:
                if (isSame(choice, menu[0])) {
                    action = PLANT;
                    status = WAIT_CROP;
                    printMoney(money);
                    printf(COLOR_GREEN"Menu of crops & their prices:\n"COLOR_OFF);
                    for (int j = 0; j < sizeOfCrops;j++) {
                        printf("- %s cost: %d money\n", crops[j].name, crops[j].price);
                    }
                    printf(COLOR_GREEN"Type "COLOR_OFF COLOR_BOLD"back"COLOR_OFF COLOR_GREEN" OR what crop u want to harvest: "COLOR_OFF);

                } else if (isSame(choice, menu[1])) {
                    action = HARVEST;
                    status = WAIT_CROP;
                    printMoney(money);
                    printf(COLOR_YELLOW"Menu of crops & their sell prices: \n"COLOR_OFF);
                    for (int k = 0; k < sizeOfCrops;k++) {
                        printf("- %s sell price: %d money, in stock %dx\n", crops[k].name, crops[k].sell, crops[k].warehouse);
                    }
                    printf(COLOR_YELLOW"Type "COLOR_OFF COLOR_BOLD"back"COLOR_OFF COLOR_YELLOW" OR what crop u want to harvest: "COLOR_OFF);

                } else if (isSame(choice, menu[2])) {
                    printf(ERROR_COLOR"OK! Ending the program...\n"COLOR_OFF);
                    status = END;
                } else {
                    error("Unknown command!\ntype command from menu: ");
                }

                break;

            case WAIT_CROP:
                switch (action) {
                case PLANT:
                        if (isSame(choice,"back")) {
                            printf("going back..\n");
                            status = WAIT_COMMAND;
                            action = NONE;
                            printMenu(menu, sizeOfMenu);
                            break;
                        }
                        found = false;
                        for (int i = 0; i < sizeOfCrops; i++) {
                            if (isSame(choice,crops[i].name)) {

                                if(plant(&crops[i], &money))
                                    nextDay(&day, crops, sizeOfCrops);

                                status = WAIT_COMMAND;
                                action = NONE;
                                printMenu(menu, sizeOfMenu);
                                found = true;
                                break;
                            }
                        }
                        if (found == false) {
                            error("Unknown crop!\n pls type it again: ");
                            break;
                        }

                        break;
                case HARVEST:
                        if (isSame(choice,"back")) {
                            printf("going back..\n");
                            status = WAIT_COMMAND;
                            action = NONE;
                            printMenu(menu, sizeOfMenu);
                            break;
                        }
                        found = false;
                        for (int i = 0; i < sizeOfCrops; i++) {
                            if (isSame(choice,crops[i].name)) {

                                if(harvest(&crops[i], &money))
                                    nextDay(&day, crops, sizeOfCrops);

                                status = WAIT_COMMAND;
                                action = NONE;
                                printMenu(menu, sizeOfMenu);
                                found = true;
                                break;
                            }
                        }
                        if (found == false) {
                            error("Unknown crop!\n pls type it again: ");
                        }

                        break;
                case NONE:
                        error("NONE as action!");
                        break;
                }

                break;

            case END:
                break;
        }

    } while (status != END);

    return 0;
}


    void clearBuffer() {
        int c;
        while ((c = getchar()) != '\n' && c != EOF){}
    }

    void error(char error[]) {
        printf(ERROR_COLOR"ERROR"COLOR_OFF);
        printf(": %s\n", error);
    }

    void printMoney(int money)
    {
        // printf("++++++++++++++\n");
        // printf("+ Money: %d +\n", money);
        // printf("++++++++++++++\n");
    }

    void nextDay(int *day, struct crop crops[], int sizeOfCrops)
    {

        *day += 1;
        for (int i = 0; i < sizeOfCrops; i++) {
            crops[i].warehouse += crops[i].is_planted;
            crops[i].is_planted = 0;
        }



        // printf("----------\n");
        // printf("- Day: %d -\n", *day);
        // printf("----------\n");
    }

    void printMenu(char *menu[], int size) {
        printf(COLOR_BOLD"Menu of commands:\n"COLOR_OFF);
        // printf(COLOR_BOLD"Menu"COLOR_OFF);
        // printf("of commands:\n");
        for (int i = 0; i < size;i++) {
            switch (i) {
                case 0:
                    printf(COLOR_GREEN"- %s\n"COLOR_OFF,menu[i]);
                break;
                case 1:
                    printf(COLOR_YELLOW"- %s\n"COLOR_OFF,menu[i]);
                break;
                case 2:
                    printf(COLOR_CYAN"- %s\n"COLOR_OFF,menu[i]);
                break;
                default:
                    printf(COLOR_CYAN"- %s\n"COLOR_OFF,menu[i]);
            }
        }
        printf(COLOR_BOLD"Type what u want to do: "COLOR_OFF);
    }

    bool harvest(struct crop *actual_crop, int *money)
    {
        if (actual_crop->warehouse == 0) {
            printf(COLOR_BOLD"ERROR: "COLOR_OFF);
            printf("There is 0 %s in ur warehouse\n", actual_crop->name);
            return false;
        } else {
            *money+= (actual_crop->sell * actual_crop->warehouse);
            printf("OK! Harvested %d %s, money added: %d\n",actual_crop->warehouse, actual_crop->name, (actual_crop->sell * actual_crop->warehouse));
            actual_crop->warehouse = 0;
            return true;
        }
    }


    bool plant(struct crop *actual_crop, int *money)
    {
        int howMuch = 0;
        printf("How much %s u want to plant: ", actual_crop->name);
        scanf("%d", &howMuch);
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


void lower(char *s)
{
    while (*s != '\0') {
        *s += (*s >= 'A' && *s <= 'Z') ? ('a' - 'A'): 0;
        *s++;
    }
}
