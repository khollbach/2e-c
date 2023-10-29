#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <limits.h>

bool is_yes(char *s);
bool is_no(char *s);
void play();
char *trim_whitespace(char *s);
bool my_strtoimax(char *s, int *guess);

char buf[256];

// NOTE: back arrow doesn't work correctly with scanf for re-editing the line.
// Maybe there's a more appropriate //e routine for getting user input? (todo)

// NOTE: when the program terminates, we can't re-launch it from the sysmon after.
// What's up with that?

int main() {
    int ret;

    clrscr();

    while (1) {
        play();

        printf("\n");
        while (1) {
            printf("Play again? (y/n) ");
            ret = scanf("%255s", buf);
            if (ret == EOF) {
                break;
            } else if (ret == 0) {
                perror("scanf");
                return 1;
            }

            if (is_yes(buf)) {
                break;
            } else if (is_no(buf)) {
                return 0;
            }
        }
    }
}

void play() {
    int ret, secret_number, guess;
    unsigned wait_time;

    // todo: if there's already keyboard input waiting in the buffer,
    // will the secret number always be 1?
    // UPDATE: yep, that's exactly what happens... todo: fix it

    // Gather "randomness".
    printf("\n");
    printf("Guess the number! Press any key to begin\n"); // exactly 40 chars
    wait_time = 0;
    while (1) {
        if (kbhit()) break;
        wait_time += 1;
    }
    cgetc(); // consume the pending keypress

    secret_number = wait_time % 100 + 1;

    printf("\n");
    printf("I'm thinking of a number\nbetween 1 and 100...\n");

    while (1) {
        // todo: get guesses by *line*.
        // currently this treats any whitespace as a word separator, which
        // doesn't feel quite "right"
        // (update: getline is POSIX but not ISO C, so we don't have it...)

        printf("\n");
        printf("What is your guess? ");
        ret = scanf("%255s", buf);
        if (ret == EOF) {
            break;
        } else if (ret == 0) {
            perror("scanf");
            exit(EXIT_FAILURE);
        }

        if (!my_strtoimax(buf, &guess)) {
            printf("That's not a number.\n");
        } else if (!(1 <= guess && guess <= 100)) {
            printf("Try guessing a number between 1 and 100.\n");
        } else if (guess == secret_number) {
            printf("Yes! The number was %d\n", secret_number);
            break;
        } else if (guess < secret_number) {
            printf("Nope. %d is too low.\n", guess);
        } else if (guess > secret_number) {
            printf("Nope. %d is too high.\n", guess);
        }
    }
}

// There seems to be a bug in their (todo: who?) strtoimax implementation.
//
// On success, they return a pointer *to* the last char in the number, instead
// of *past* it. So there's no way to distiguish these two cases:
// 1. success on a string of length 1
// 2. failure
//
// Hopefully this work-around fixes the issue.
bool my_strtoimax(char *s, int *guess) {
    char *end;
    s = trim_whitespace(s);
    *guess = strtoimax(s, &end, 10);

    // Happy path.
    if (*guess != 0) {
        return true;
    }

    // Definitely failed.
    if (end + 1 - s != strlen(s)) {
        return false;
    }

    // I *think* the remaining cases consist of:
    // 1. a string that correctly parsed as the value `0`
    // 2. a string of length 1 that failed to parse

    // So we determine success as follows:
    return *s == '0';
}

char *trim_leading_ws(char *s) {
    char *c;
    for (c = s; *c; c++) {
        if (!isspace(*c)) {
            return c;
        }
    }
    return c;
}

void trim_trailing_ws(char *s) {
    char *c;
    for (c = s + strlen(s) - 1; c >= s; c--) {
        if (!isspace(*c)) {
            *(c + 1) = '\0';
            return;
        }
    }

    // s was all whitespace.
    *s = '\0';
}

// Insert a null byte after the last non-whitespace character.
//
// Return a pointer to the first non-whitespace character.
//
// Be careful to free s and not the returned pointer.
char *trim_whitespace(char *s) {
    trim_trailing_ws(s);
    return trim_leading_ws(s);
}

// Ignore leading whitespace.
bool is_yes(char *s) {
    char *c;
    for (c = s; *c; c++) {
        if (*c == 'y' || *c == 'Y') {
            return true;
        } else if (!isspace(*c)) {
            return false;
        }
    }
    return false;
}

// Ignore leading whitespace.
bool is_no(char *s) {
    char *c;
    for (c = s; *c; c++) {
        if (*c == 'n' || *c == 'N') {
            return true;
        } else if (!isspace(*c)) {
            return false;
        }
    }
    return false;
}
