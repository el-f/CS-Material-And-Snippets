#include <stdio.h>
#include "Address.h"

void printAddress(const Address *address) {
    printf("Address: %s %d\n", address->street_name, address->house_number);
}

void initAddress(Address *address) {
    printf("Please enter the street name:");
    scanf("%s", address->street_name);

    printf("Please enter the house number:");
    scanf("%d", &address->house_number);

}

// Unused functions

//void initAddresses(Address *address, int size) {
//    for (int i = 0; i < size; i++) {
//        initAddress(&address[i]);
//    }
//}
//
//void printAddresses(const Address *addresses, int size) {
//    for (int i = 0; i < size; i++) {
//        printAddress(&addresses[i]);
//    }
//}