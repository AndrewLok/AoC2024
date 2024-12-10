/*
    --- Day 2 (Part 1): Red-Nosed Reports ---

    Fortunately, the first location The Historians want to search isn't a long walk from the Chief Historian's office.

    While the Red-Nosed Reindeer nuclear fusion/fission plant appears to contain no sign of the Chief Historian, the engineers there run up to you as soon as they see you. Apparently, they still talk about the time Rudolph was saved through molecular synthesis from a single electron.

    They're quick to add that - since you're already here - they'd really appreciate your help analyzing some unusual data from the Red-Nosed reactor. You turn to check if The Historians are waiting for you, but they seem to have already divided into groups that are currently searching every corner of the facility. You offer to help with the unusual data.

    The unusual data (your puzzle input) consists of many reports, one report per line. Each report is a list of numbers called levels that are separated by spaces. For example:

    7 6 4 2 1
    1 2 7 8 9
    9 7 6 2 1
    1 3 2 4 5
    8 6 4 4 1
    1 3 6 7 9

    This example data contains six reports each containing five levels.

    The engineers are trying to figure out which reports are safe. The Red-Nosed reactor safety systems can only tolerate levels that are either gradually increasing or gradually decreasing. So, a report only counts as safe if both of the following are true:

        The levels are either all increasing or all decreasing.
        Any two adjacent levels differ by at least one and at most three.

    In the example above, the reports can be found safe or unsafe by checking those rules:

        7 6 4 2 1: Safe because the levels are all decreasing by 1 or 2.
        1 2 7 8 9: Unsafe because 2 7 is an increase of 5.
        9 7 6 2 1: Unsafe because 6 2 is a decrease of 4.
        1 3 2 4 5: Unsafe because 1 3 is increasing but 3 2 is decreasing.
        8 6 4 4 1: Unsafe because 4 4 is neither an increase or a decrease.
        1 3 6 7 9: Safe because the levels are all increasing by 1, 2, or 3.

    So, in this example, 2 reports are safe.

    Analyze the unusual data from the engineers. How many reports are safe?
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    FILE *input = fopen("inp.txt", "r");
    if (input == NULL) {
        printf("File does not exist.");
        return 0;
    }

    int safeCount = 0;
    char curStr[25];
    while (fgets(curStr, 25, input)) {
        // Convert the input into an array.
        int *report = malloc(0);

        char *strPos = curStr;
        int curInt;
        int count = 0;
        while (sscanf(strPos, "%d", &curInt)) {

            int size = (count + 1) * sizeof(int);
            //printf("Allocating %d.\n", size);

            void *p = realloc(report, size);
            if (!p) {
                printf("Reallocation failed");
            }
            else {
                report = p;
            }

            report[count] = curInt;
            count++;
            
            strPos = strchr(strPos, ' '); // Find the next whitespace;
            if (!strPos) // If there are no more whitespaces we can assume that there are no more integers and end the loop.
                break;
            strPos++; // Advance by one to move from the whitespace to the next integer.
        }

        /*for (int i = 0; i < count; i++) {
            printf("%d ", report[i]);
        }*/
        //printf("\nSize %d\n", count);

        int prevInt = report[0];
        int increasing = 0;
        int decreasing = 0;
        int safe = 1;
        for (int i = 1; i < count; i++) {
            if (report[i] > prevInt) { // Increasing.
                if (decreasing == 1) { // Unsafe.
                    safe = 0;
                    break;
                }
                increasing = 1;
            }
            else if (report[i] < prevInt) { // Decreasing.
                if (increasing == 1) { // Unsafe.
                    safe = 0;
                    break;
                }
                decreasing = 1;
            }
            else if (report[i] == prevInt) { // Unsafe.
                safe = 0;
                break;
            }

            int difference = 0;
            if (increasing == 1) {
                difference = report[i] - prevInt;
            }
            else if (decreasing == 1) {
                difference = prevInt - report[i];
            }

            if (difference < 1 || difference > 3) { // Unsafe.
                safe = 0;
                break;
            }

            prevInt = report[i];
        }

        if (safe == 1)
            safeCount++;

        free(report);
    }

    printf("%d\n", safeCount);

    fclose(input);

    return 0;
}