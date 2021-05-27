#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FILE_SIMPLE_IN "mem simple in.txt"
#define FILE_SIMPLE_OUT "mem simple out.txt"
#define FILE_SPECIALS_IN "mem specials in.txt"
#define FILE_SPECIALS_OUT "mem specials out.txt"
#define SPECIALS_A_MEM_SIZE 8
#define SPECIAL_B_MEM_SIZE 16
#define SPECIALS_LIMIT 3
#define MEMORY_MAX_SIZE 128
#define ALPHABET_SIZE 26
#define ADD_SYMBOL '+'

typedef struct {
    char W[ALPHABET_SIZE];
    int X[ALPHABET_SIZE];
    int vector[MEMORY_MAX_SIZE];
    int FREELIST;
} MemoryManager;

typedef struct {
    int size;
    int limit;
    int N;
    int *pointers;
} SpecialsManager;

void initMemoryManager(MemoryManager *mm) {
    for (size_t i = 0; i < ALPHABET_SIZE; i++) {
        mm->W[i] = (char) (i + 'A');
    }

    mm->vector[0] = MEMORY_MAX_SIZE;
    mm->vector[1] = -1;
    mm->FREELIST = (MEMORY_MAX_SIZE - mm->vector[0]);
}

void initSpecialsManager(SpecialsManager *sm, int size) {
    sm->limit = SPECIALS_LIMIT;
    sm->pointers = malloc(sizeof(int) * sm->limit);
    if (!sm->pointers) {
        printf("SpecialsManager MALLOC FAILED!");
        exit(EXIT_FAILURE);
    }
    sm->size = size;
    sm->N = -1;
}

int removeFromSpecials(SpecialsManager *sm) {
    return sm->pointers[sm->N--];
}

int findObject(MemoryManager *memManager, int size, char letter) {
    int pointer = 0;
    while (pointer != MEMORY_MAX_SIZE) {
        if (memManager->vector[pointer] == letter
            && size == memManager->X[letter - 'A']) {
            memManager->vector[pointer] = size;
            return pointer;
        }
        if (memManager->vector[pointer] >= 'A') {
            pointer += memManager->X[memManager->vector[pointer] - 'A'];
        } else {
            pointer += memManager->vector[pointer];
        }
    }
    return -1;
}

void removeFromMemory(MemoryManager *memManager, FILE *writing, char letter) {
    int objSize = memManager->X[letter - 'A'];
    int nextFreeIndex;
    int lastFreeIndex = memManager->FREELIST;
    bool rightBeforeNextFree, rightAfterLastFree;

    int j = 0, success = 0;
    while (j != MEMORY_MAX_SIZE && !success) {
        if (memManager->vector[j] == memManager->vector[memManager->vector[lastFreeIndex + 1]] &&
            j != memManager->FREELIST
                ) {
            lastFreeIndex = memManager->vector[lastFreeIndex + 1];
        }
        if (memManager->vector[j] == letter) {
            int i;
            for (i = j; i < objSize + j; i++) {
                memManager->vector[i] = 0;
            }
            if (j < memManager->FREELIST) {
                if ((memManager->FREELIST - objSize) == j) {
                    memManager->vector[j] = objSize + memManager->vector[memManager->FREELIST];
                    memManager->vector[j + 1] = memManager->vector[memManager->FREELIST + 1];
                    for (int k = memManager->FREELIST; k < memManager->FREELIST + 2; k++) {
                        memManager->vector[k] = 0;
                    }
                    memManager->FREELIST = j;
                } else {
                    memManager->vector[j] = objSize;
                    memManager->vector[j + 1] = memManager->FREELIST;
                    memManager->FREELIST = j;
                }
            } else {
                rightAfterLastFree = (memManager->vector[lastFreeIndex] + lastFreeIndex) == j;
                nextFreeIndex = memManager->vector[lastFreeIndex + 1];
                rightBeforeNextFree = (j + objSize) == nextFreeIndex;

                if (rightAfterLastFree && rightBeforeNextFree) {
                    memManager->vector[lastFreeIndex] += (objSize + memManager->vector[nextFreeIndex]);
                    memManager->vector[lastFreeIndex + 1] = memManager->vector[nextFreeIndex + 1];
                    memManager->vector[nextFreeIndex] = 0;
                    memManager->vector[nextFreeIndex + 1] = 0;
                } else if (rightAfterLastFree) {
                    memManager->vector[lastFreeIndex] += objSize;
                } else if (rightBeforeNextFree) {
                    memManager->vector[j] = objSize + memManager->vector[nextFreeIndex];
                    memManager->vector[j + 1] = memManager->vector[nextFreeIndex + 1];
                    memManager->vector[lastFreeIndex + 1] = j;
                    memManager->vector[nextFreeIndex] = 0;
                    memManager->vector[nextFreeIndex + 1] = 0;
                } else {
                    memManager->vector[j] = objSize;
                    memManager->vector[j + 1] = nextFreeIndex;
                    memManager->vector[lastFreeIndex + 1] = j;
                }
            }
            fprintf(writing, "%c-  0\n", letter);
            success = true;
        }
        if (memManager->vector[j] >= 'A') {
            j += memManager->X[memManager->vector[j] - 'A'];
        } else {
            j += memManager->vector[j];
        }
    }
}

void writeLetterToMemory(MemoryManager *mm, FILE *writing, int start, int size, char letter) {
    for (int i = start; i < start + size; i++) {
        mm->vector[i] = (unsigned char) letter;
    }
    fprintf(writing, "%c+  %d\n", letter, start);
}

int assignToMemory(MemoryManager *mm, FILE *writing, char letter) {
    int objectSize = mm->X[letter - 'A'];
    int currentFreeCellIndex = mm->FREELIST;
    if (mm->vector[mm->FREELIST] >= objectSize) {
        if (mm->vector[mm->FREELIST] == objectSize) {
            mm->FREELIST = mm->vector[mm->FREELIST + 1];
        } else {
            mm->vector[mm->FREELIST + objectSize] = mm->vector[mm->FREELIST] - objectSize;
            mm->vector[mm->FREELIST + objectSize + 1] = mm->vector[mm->FREELIST + 1];
            mm->FREELIST = mm->FREELIST + objectSize;
        }
        writeLetterToMemory(mm, writing, currentFreeCellIndex, objectSize, letter);
        return 1;
    }

    int prevFreeIndex = mm->FREELIST;
    while (mm->vector[prevFreeIndex + 1] != -1) {
        currentFreeCellIndex = mm->vector[prevFreeIndex + 1];
        if (mm->vector[currentFreeCellIndex] < objectSize) {
            prevFreeIndex = currentFreeCellIndex;
        } else {
            if (mm->vector[currentFreeCellIndex] == objectSize) {
                mm->vector[prevFreeIndex + 1] = mm->vector[currentFreeCellIndex + 1];
            } else {
                mm->vector[prevFreeIndex + 1] = currentFreeCellIndex + objectSize;
                mm->vector[currentFreeCellIndex + objectSize] = mm->vector[currentFreeCellIndex] - objectSize;
                mm->vector[currentFreeCellIndex + objectSize + 1] = mm->vector[currentFreeCellIndex + 1];
            }
            writeLetterToMemory(mm, writing, currentFreeCellIndex, objectSize, letter);
            return 1;
        }
    }

    printf("Error! Can't assign to memory vector\n");
    fprintf(writing, "%c+  -1\n", letter);
    return 0;
}

int readLine(char *letter, char *symbol, FILE *reading) {
    if ((*letter = (signed char) fgetc(reading)) == EOF || (*symbol = (signed char) fgetc(reading)) == EOF)
        return 0;
    fscanf(reading, " "); // read whitespace
    return 1;
}

int matchLetterToSpecial_OnAdd(MemoryManager *memManager, char letter, SpecialsManager *sm, FILE *writing) {
    if (memManager->X[letter - 'A'] == sm->size && sm->N != -1) {
        writeLetterToMemory(memManager, writing, removeFromSpecials(sm), sm->size, letter);
        return 1;
    } else return 0;
}

int matchLetterToSpecial_OnRemove(MemoryManager *memManager, char letter, SpecialsManager *sm, FILE *writing) {
    if (memManager->X[letter - 'A'] == sm->size && sm->N != (sm->limit - 1)) {
        sm->pointers[++sm->N] = findObject(memManager, sm->size, letter); // add to specials
        fprintf(writing, "%c-  0\n", letter);
        return 1;
    } else return 0;
}

int main() {
    MemoryManager memManager = {
            .W = {},
            .X = {
                    8, 16, 16, 32, 8, 16, 8, 16, 8, 16, 16, 8, 48,
                    8, 8, 16, 8, 16, 72, 24, 32, 8, 16, 32, 8, 20
            }
    };
    initMemoryManager(&memManager);

    SpecialsManager specials_A, specials_B;
    initSpecialsManager(&specials_A, SPECIALS_A_MEM_SIZE);
    initSpecialsManager(&specials_B, SPECIAL_B_MEM_SIZE);

    FILE *reading = fopen(FILE_SPECIALS_IN, "r");
    FILE *writing = fopen(FILE_SPECIALS_OUT, "w");

    if (!reading) {
        printf("Error opening input file");
        exit(EXIT_FAILURE);
    }

    if (!writing) {
        printf("Error opening output file");
        exit(EXIT_FAILURE);
    }

    int special = fgetc(reading) - '0';
    fscanf(reading, " ");    // read whitespace

    fprintf(writing, "%d\n", special);
    char letter, symbol;
    while (readLine(&letter, &symbol, reading)) {
        if (symbol == ADD_SYMBOL) {
            if (!special ||
                (!matchLetterToSpecial_OnAdd(&memManager, letter, &specials_A, writing) &&
                 !matchLetterToSpecial_OnAdd(&memManager, letter, &specials_B, writing))
                    ) {
                assignToMemory(&memManager, writing, letter);
            }
        } else if (!special ||
                   (!matchLetterToSpecial_OnRemove(&memManager, letter, &specials_A, writing) &&
                    !matchLetterToSpecial_OnRemove(&memManager, letter, &specials_B, writing))
                ) {
            removeFromMemory(&memManager, writing, letter);
        }
        fflush(writing);
    }
    fclose(reading);
    fclose(writing);

    free(specials_A.pointers);
    free(specials_B.pointers);

    puts("Program finished, check output file.");
}
