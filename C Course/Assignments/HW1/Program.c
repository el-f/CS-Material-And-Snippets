#include <stdio.h>

#include "PictureManipulation.h"
#include "NumberGame.h"
#include "Utils.h"

#define PICTURE_MANIPULATION 'P'
#define NUMBER_GAME 'N'
#define EXIT 'E'

int main() {
    char choice;
    do {
        printf("Please choose one of the following options:\n");
        printf("%c - Picture Manipulation\n", PICTURE_MANIPULATION);
        printf("%c - Number Game\n", NUMBER_GAME);
        printf("%c - Quit\n", EXIT);

        choice = scanChar();
        switch (choice) {
            case PICTURE_MANIPULATION:
                pictureManipulation();
                break;

            case NUMBER_GAME:
                numberGame();
                break;

            case EXIT:
                printf("Bye Bye!\n");
                break;

            default:
                printf("Invalid Input\n");
        }
    } while (choice != EXIT);
    return 0;
}
