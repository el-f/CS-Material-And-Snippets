class Employee:

    def __init__(self, first, last):
        self.first = first
        self.last = last

    @property
    def email(self):
        return '{}.{}@email.com'.format(self.first, self.last)

    @property
    def fullname(self):
        return '{} {}'.format(self.first, self.last)

    @fullname.setter
    def fullname(self, name):
        first, last = name.split(' ')
        self.first = first
        self.last = last

    @fullname.deleter
    def fullname(self):
        print('Name deleted!')
        # del self.first; del self.last
        self.first = None
        self.last = None


def print_emp(emp: Employee):
    print(emp.first)
    print(emp.email)
    print(emp.fullname)


e1 = Employee('John', 'Smith')
e1.first = 'Elazar'
print_emp(e1)

e1.fullname = 'Joe Mama'
print_emp(e1)

del e1.fullname
print_emp(e1)
