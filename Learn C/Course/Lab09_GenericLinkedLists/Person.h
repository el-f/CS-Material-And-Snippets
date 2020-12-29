#ifndef PERSON_H_
#define PERSON_H_

#define MAX_LEN 20
typedef struct
{
	int 	id;
	char	name[MAX_LEN];
}Person;

void 	initPerson(Person* pPer);
void	showPerson(const void* pPer);
int		comparePersonById(const void* p1, const void* p2);
void	freePerson(void* p1);
#endif /* PERSON_H_ */
