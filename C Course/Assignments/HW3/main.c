#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "Company.h"

typedef enum {
    eAddFlight,
    eAddAirport,
    ePrintCompany,
    ePrintAirports,
    ePrintFlightOrigDest,
    eSortFlights,
    eSearchFlight,
    eNofOptions
} eMenuOptions;

const char *str[eNofOptions] = {
        "Add Flight",
        "Add Airport",
        "Print Company",
        "Print all Airports",
        "Print flights between origin-destination",
        "Sort Flights",
        "Search Flight"
};

#define EXIT            (-1)

#define AP_MANAGER_TEXT_FILE "airport_authority.txt"
#define COMPANY_BIN_FILE "company.bin"

void writeAirportManager(const char *filename, AirportManager *pManager);
int readAirportManager(const char *filename, AirportManager *pManager);
int writeCompany(const char *filename, Company *company);
int readCompany(const char *filename, Company *company);

int menu();

int main() {
    AirportManager manager;
    Company company;

    if (!readAirportManager(AP_MANAGER_TEXT_FILE, &manager)) return -1;
    if (!readCompany(COMPANY_BIN_FILE, &company)) return -2;

    int option;
    int stop = 0;

    do {
        option = menu();
        switch (option) {
            case eAddFlight:
                if (!addFlight(&company, &manager))
                    printf("Error adding flight\n");
                break;

            case eAddAirport:
                if (!addAirport(&manager))
                    printf("Error adding airport\n");
                break;

            case ePrintCompany:
                printCompany(&company);
                break;

            case ePrintAirports:
                printAirports(&manager);
                break;

            case ePrintFlightOrigDest:
                printFlightsCount(&company);
                break;

            case eSortFlights:
                sortFlights(&company);
                break;

            case eSearchFlight:
                searchFlight(&company);
                break;

            case EXIT:
                printf("Bye bye\n");
                stop = 1;
                break;

            default:
                printf("Wrong option\n");
                break;
        }
    } while (!stop);

    writeAirportManager(AP_MANAGER_TEXT_FILE, &manager);
    writeCompany(COMPANY_BIN_FILE, &company);

    freeManager(&manager);
    freeCompany(&company);
}

int menu() {
    int option;
    printf("\n\n");
    printf("Please choose one of the following options\n");
    for (int i = 0; i < eNofOptions; i++)
        printf("%d - %s\n", i, str[i]);
    printf("%d - Quit\n", EXIT);
    scanf("%d", &option);

    //clean buffer
    char tav;
    scanf("%c", &tav);

    return option;
}

void writeAirportManager(const char *filename, AirportManager *pManager) {
    FILE *fp = fopen(filename, "w");
    if (!fp) printf("Error Opening Airport Manager File!\n");
    writeAirportManagerToTextFile(fp, pManager);
    fclose(fp);
}

int readAirportManager(const char *filename, AirportManager *pManager) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error Opening Airport Manager File!\n");
        return 0;
    }
    return readAirportManagerFromTextFile(fp, pManager) && !fclose(fp);
}

int writeCompany(const char *filename, Company *company) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("Error Opening Company File!\n");
        return 0;
    }
    return writeCompanyToBinFile(fp, company) && !fclose(fp);
}

int readCompany(const char *filename, Company *company) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("Error Opening Company File!\n");
        return 0;
    }
    return readCompanyFromBinFile(fp, company) && !fclose(fp);
}