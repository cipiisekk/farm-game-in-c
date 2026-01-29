/*
 * TODO:
 * stav, choice misto dvou promennych choice_menu a choice_crops - ENUM pouzit
 *
 */
#include <stdio.h>
#include <stdbool.h>

void lower(char *s);
bool isSame(char *s1, char *s2);

struct crop {
    char name[20];
    int price;
    int sell;
    int warehouse;
};

int main()
{

    char *menu[3] = {
        "plant",
        "havrest",
        "end"
    };

    int money = 100;
    int day = 0;

    char choice_menu[20] = {0};
    char choice_crops[20] = {0};

    struct crop wheat = {"wheat", 5, 15, 0};
    struct crop corn = {"corn",8, 24, 0};
    struct crop potatoes = {"potatoes",10, 30, 0};

    struct crop *crops[0];

    do {
        scanf("%19s", choice_menu);
        lower(choice_menu);
        if ((isSame(choice_menu, menu[0]) == true){


        }

    } while (isSame(choice_menu, menu[2]) == false);

    return 0;
}

bool isSame(char *s1, char *s2) {
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
