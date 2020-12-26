#ifndef ADDRESS_H_
#define ADDRESS_H_

#define MAX_LEN 20

typedef struct {
    char street_name[MAX_LEN];
    int house_number;
} Address;

void initAddress(Address *address);

void printAddress(const Address *address);

//void initAddresses(Address *address, int size);
//
//void printAddresses(const Address *addresses, int size);

#endif /* ADDRESS_H_ */
