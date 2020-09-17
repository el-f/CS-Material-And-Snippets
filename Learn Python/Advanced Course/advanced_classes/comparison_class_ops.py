class Employee:
    def __init__(self, fname, lname, level, years):
        self.fname = fname
        self.lname = lname
        self.level = level
        self.seniority = years

    def __ge__(self, other):
        if self.level == other.level:
            return self.seniority >= other.seniority
        return self.level >= other.level

    def __gt__(self, other):
        if self.level == other.level:
            return self.seniority > other.seniority
        return self.level > other.level

    def __lt__(self, other):
        if self.level == other.level:
            return self.seniority < other.seniority
        return self.level < other.level

    def __le__(self, other):
        if self.level == other.level:
            return self.seniority <= other.seniority
        return self.level <= other.level

    def __eq__(self, other):
        return self.level == other.level and self.seniority == other.seniority


def main():
    dept = [Employee("Tim", "Sims", 5, 9),
            Employee("John", "Doe", 4, 12),
            Employee("Jane", "Smith", 6, 6),
            Employee("Becca", "Robin", 5, 13),
            Employee("Tyler", "Durden", 5, 12)]

    print(dept[0] > dept[2])
    print(dept[4] < dept[3])
    print(dept[3] == dept[4])
    print("\n")
    
    emps = sorted(dept)

    for emp in emps:
        print(emp.lname)


if __name__ == '__main__':
    main()
