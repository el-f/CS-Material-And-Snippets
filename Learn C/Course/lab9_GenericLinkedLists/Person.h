#ifndef PERSON_H_
#define PERSON_H_

#define MAX_LEN 20
typedef struct
{
	int 	id;
	char	name[20];
}Person;

void 	initPerson(Person* pPer);


#endif /* PERSON_H_ */
