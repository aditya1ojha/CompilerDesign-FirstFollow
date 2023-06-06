// Necessary header files
#include <ctype.h>
#include <stdio.h>
#include <string.h>


// Function to calculate First
void findFirst(char, int, int);

// Functions to calculate Follow
void followFirst(char, int, int);
void findFollow(char c);

int count, num = 0;

// To store the final result of the First Sets
char calcFirst[10][100];

// To store the final result of the Follow Sets
char calcFollow[10][100];
int m = 0;

// To store the production rules
char production[10][10];
char f[10], first[10];
int k;
char ck;
int e;


// Main function
int main(int argc, char** argv)
{
    int firstIndex = 0;
    int followIndex = 0;
    int i, choice;
    char c, ch;
    count = 0;

    // Taking input from user
    printf("Enter the number of production rules: ");
    scanf("%d", &count);

    printf("Enter the production rules (in the format X=Y): \n");
    for (i = 0; i < count; i++) {
        scanf("%s", production[i]);
    }

    int doneIndex;
    char done[count];
    int ptr = -1;

    // Initializing the calcFirst array
    for (k = 0; k < count; k++) {
        for (doneIndex = 0; doneIndex < 100; doneIndex++) {
            calcFirst[k][doneIndex] = '!';
        }
    }
    int firstSetsIndex = 0, firstSetsIndex2, xxx;

    printf("\n  FIRST SETS: \n");

    for (k = 0; k < count; k++) {
        c = production[k][0];
        firstSetsIndex2 = 0;
        xxx = 0;

        // Checking if First of c has already been calculated
        for (doneIndex = 0; doneIndex <= ptr; doneIndex++)
            if (c == done[doneIndex])
                xxx = 1;

        if (xxx == 1)
            continue;

        // Function call
        findFirst(c, 0, 0);
        ptr += 1;

        // Adding c to the calculated list
        done[ptr] = c;
        printf("\n First(%c) = { ", c);
        calcFirst[firstSetsIndex][firstSetsIndex2++] = c;

        // Printing the First Sets of the grammar
        for (i = 0 + firstIndex; i < num; i++) {
            int lark = 0, chk = 0;

            for (lark = 0; lark < firstSetsIndex2; lark++) {

                if (first[i] == calcFirst[firstSetsIndex][lark]) {
                    chk = 1;
                    break;
                }
            }
            if (chk == 0) {
                printf("%c, ", first[i]);
                calcFirst[firstSetsIndex][firstSetsIndex2++] = first[i];
            }
        }
        printf("}\n");
        firstIndex = num;
        firstSetsIndex++;
    }
    printf("\n");
    printf("-----------------------------------------------"
        "\n\n");
    char donee[count];
    ptr = -1;

    // Initializing the calcFollow array
    for (k = 0; k < count; k++) {
        for (doneIndex = 0; doneIndex < 100; doneIndex++) {
            calcFollow[k][doneIndex] = '!';
        }
    }

    firstSetsIndex = 0;
    int land = 0;

    printf("\n  FOLLOW SETS: \n");

    for (e = 0; e < count; e++) {
        ck = production[e][0];
        firstSetsIndex2 = 0;
        xxx = 0;

        // Checking if Follow of ck already been calculated
        for (doneIndex = 0; doneIndex <= ptr; doneIndex++)
            if (ck == donee[doneIndex])
                xxx = 1;

        if (xxx == 1)
            continue;
        land += 1;

        // Function call
        findFollow(ck);
        ptr += 1;

        // Adding ck to the calculated list
        donee[ptr] = ck;
        printf("\nFollow(%c) = { ", ck);
        calcFollow[firstSetsIndex][firstSetsIndex2++] = ck;

        // Printing the Follow Sets of the grammar
        for (i = 0 + followIndex; i < m; i++) {
            int lark = 0, chk = 0;
            for (lark = 0; lark < firstSetsIndex2; lark++) {
                if (f[i] == calcFollow[firstSetsIndex][lark]) {
                    chk = 1;
                    break;
                }
            }
            if (chk == 0) {
                printf("%c, ", f[i]);
                calcFollow[firstSetsIndex][firstSetsIndex2++] = f[i];
            }
        }
        printf(" }\n\n");
        followIndex = m;
        firstSetsIndex++;
    }
}


void findFollow(char c)
{
    int i, j;

    // Adding "$" to the findFollow set of the start symbol
    if (production[0][0] == c) {
        f[m++] = '$';
    }
    for (i = 0; i < 10; i++) {
        for (j = 2; j < 10; j++) {
            if (production[i][j] == c) {
                if (production[i][j + 1] != '\0') {

                    // Calculate the first of the next Non-Terminal in the production
                    followFirst(production[i][j + 1], i,
                                (j + 2));
                }

                if (production[i][j + 1] == '\0'
                    && c != production[i][0]) {
                    // Calculate the findFollow of the Non-Terminal in the L.H.S. of the production
                    findFollow(production[i][0]);
                }
            }
        }
    }
}

void findFirst(char c, int q1, int q2)
{
    int j;

    // The case where we encounter a Terminal
    if (!(isupper(c))) {
        first[num++] = c;
    }
    for (j = 0; j < count; j++) {
        if (production[j][0] == c) {
            if (production[j][2] == '#') {
                if (production[q1][q2] == '\0')
                    first[num++] = '#';
                else if (production[q1][q2] != '\0'
                        && (q1 != 0 || q2 != 0)) {

                    // Recursion to calculate First of new Non-Terminal we encounter after epsilon
                    findFirst(production[q1][q2], q1,
                            (q2 + 1));
                }
                else
                    first[num++] = '#';
            }
            else if (!isupper(production[j][2])) {
                first[num++] = production[j][2];
            }
            else {
                // Recursion to calculate First of new Non-Terminal we encounter at the beginning
                findFirst(production[j][2], j, 3);
            }
        }
    }
}

void followFirst(char c, int c1, int c2)
{
    int k;

    // The case where we encounter a Terminal
    if (!(isupper(c)))
        f[m++] = c;
    else {
        int i = 0, j = 1;
        for (i = 0; i < count; i++) {
            if (calcFirst[i][0] == c)
                break;
        }

        // Including the First set of the Non-Terminal in the Follow of the original query
        while (calcFirst[i][j] != '!') {
            if (calcFirst[i][j] != '#') {
                f[m++] = calcFirst[i][j];
            }
            else {
                if (production[c1][c2] == '\0') {

                    // Case where we reach the end of a production
                    findFollow(production[c1][0]);
                }
                else {

                    // Recursion to the next symbol in case we encounter a "ε"
                    followFirst(production[c1][c2], c1,
                                c2 + 1);
                }
            }
            j++;
        }
    }
}