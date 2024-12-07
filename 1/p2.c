/*
    --- Day 1 (Part 2): Historian Hysteria ---

    Your analysis only confirmed what everyone feared: the two lists of location IDs are indeed very different.

    Or are they?

    The Historians can't agree on which group made the mistakes or how to read most of the Chief's handwriting, but in the commotion you notice an interesting detail: a lot of location IDs appear in both lists! Maybe the other numbers aren't location IDs at all but rather misinterpreted handwriting.

    This time, you'll need to figure out exactly how often each number from the left list appears in the right list. Calculate a total similarity score by adding up each number in the left list after multiplying it by the number of times that number appears in the right list.

    Here are the same example lists again:

    3   4
    4   3
    2   5
    1   3
    3   9
    3   3

    For these example lists, here is the process of finding the similarity score:

        The first number in the left list is 3. It appears in the right list three times, so the similarity score increases by 3 * 3 = 9.
        The second number in the left list is 4. It appears in the right list once, so the similarity score increases by 4 * 1 = 4.
        The third number in the left list is 2. It does not appear in the right list, so the similarity score does not increase (2 * 0 = 0).
        The fourth number, 1, also does not appear in the right list.
        The fifth number, 3, appears in the right list three times; the similarity score increases by 9.
        The last number, 3, appears in the right list three times; the similarity score again increases by 9.

    So, for these example lists, the similarity score at the end of this process is 31 (9 + 4 + 0 + 0 + 9 + 9).

    Once again consider your left and right lists. What is their similarity score?
*/
#include<stdio.h>

int main() {
    // Get the puzzle input from the file.
    FILE *input = fopen("inp.txt", "r");
    if (input == NULL) {
        printf("File does not exist.");
        return 0;
    }

    // Assumes each list containes 1000 elements and is of the same length.
    int list1[1000];
    int list2[1000];

    char curStr[15]; // Assumes each line is of lenth 15 (ignores \n and EOF).
    int count = 0;
    while (fgets(curStr, 15, input)) {
        if (count == 1000)
            break;

        int int1;
        int int2;
        sscanf(curStr, "%d   %d", &int1, &int2);

        list1[count] = int1;
        list2[count] = int2;

        count++;
    }
    fclose(input);

    // Calculate the similarity score.
    int score = 0;
    int i;
    for (i = 0; i < 1000; i++) {
        int matches = 0;

        int j;
        for (j = 0; j < 1000; j++) {
            if (list1[i] == list2[j]) {
                matches++;
            }
        }

        score += list1[i] * matches;
    }

    printf("%d\n", score);
    return 0;
}