#include <stdio.h>

#include "Utils.h"
#include "AirportManager.h"
#include "Date.h"
#include "Airline.h"

#define ADD_FLIGHT 1
#define ADD_AIRPORT 2
#define PRINT_AIRLINE 3
#define PRINT_AIRPORT_MANAGER 4
#define PRINT_LINES 5
#define QUIT 6

int main() {
    bool init = false;
    AirportManager airportManager;
    while (!init) {
        init = initAirportManager(&airportManager);
        if (!init) printf("Error initializing airport manager! Try again\n");
    }
    printAirportManager(&airportManager);

    init = false;
    Airline airline;
    while (!init) {
        init = initAirline(&airline);
        if (!init) printf("Error initializing airline! Try again\n");
    }

    int choice;
    do {
        printf("\n>Menu:\n");
        printf("%d - Add Flight\n", ADD_FLIGHT);
        printf("%d - Add Airport\n", ADD_AIRPORT);
        printf("%d - Print Airline\n", PRINT_AIRLINE);
        printf("%d - Print Airport Manager\n", PRINT_AIRPORT_MANAGER);
        printf("%d - Print Lines\n", PRINT_LINES);
        printf("%d - Quit\n", QUIT);

        choice = scanInt();
        switch (choice) {
            case ADD_FLIGHT:
                if (!addFlight(&airline, &airportManager))
                    printf("Error Adding Flight!\n");
                break;

            case ADD_AIRPORT:
                if (!addAirport(&airportManager))
                    printf("Error Adding Flight!\n");
                break;

            case PRINT_AIRLINE:
                printAirline(&airline);
                break;

            case PRINT_AIRPORT_MANAGER:
                printAirportManager(&airportManager);
                break;

            case PRINT_LINES:
                printNumOfFlightsInLine(&airline, &airportManager);
                break;

            case QUIT:
                printf("Bye Bye!\n");
                freeAirline(&airline);
                freeAirportManager(&airportManager);
                break;

            default:
                printf("Invalid Input\n");
        }
    } while (choice != QUIT);
    return 0;
}
