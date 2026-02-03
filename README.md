# Simple farm game in C

<img width="426" height="594" alt="image" src="https://github.com/user-attachments/assets/e51154ab-9a6e-4694-b696-9e2a42cb4106" />

### gcc compile:
```bash
gcc main.c -Wall -Wextra -Wpedantic -std=c11 -o farm-game.out
```

<br>

## TODO LIST
### Improve the game
- [ ] add pseudo-random daily events (like storms or good weather)
- [ ] make variables and the algorithm use less memory

### Improve the code
- [ ] add comments to the code
- [ ] make the code easier to read
- [ ] make the user experience better

<br>

## Sanitized string input

```c
    void clearBuffer(void) 
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF){}
    }
```
## Created my isSame function for strings

```c

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

```
## Using my my_lower function

```c

    void my_lower(char *s)
    {
        while (*s != '\0') {
            *s += (*s >= 'A' && *s <= 'Z') ? ('a' - 'A'): 0;
            s++;
        }
    }

```
## Using enums to label choice variable, for using it in different times 

```c

    enum status {
        WAIT_COMMAND, WAIT_CROP, END
    };

    enum action {
        PLANT, HARVEST, NONE
    };

    enum status status = WAIT_COMMAND;
    enum action action = NONE;

```
In do-while loop
```c
    scanf("%19s", choice);
    my_lower(choice);
    clearBuffer();

    switch (status) {
        case WAIT_COMMAND:

            if (isSame(choice, menu[0])) {
                    action = PLANT;
                    status = WAIT_CROP;
                    ...
            }

            break;
        case WAIT_CROP:
            ...
            break;
    }

```

