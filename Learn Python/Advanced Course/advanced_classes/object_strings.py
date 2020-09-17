class Person:
    def __init__(self):
        self.fname = "Joe"
        self.lname = "Shmoe"
        self.age = 25

    def __repr__(self):
        return "<Person Class - fname:{0}, lname:{1}, age:{2}>".format(
            self.fname, self.lname, self.age
        )

    def __str__(self):
        return "Person {0} {1} is {2}".format(
            self.fname, self.lname, self.age
        )

    def __bytes__(self):
        val = "Person:{0}:{1}:{2}".format(
            self.fname, self.lname, self.age
        )
        return bytes(val.encode('utf-8'))


def main():
    cls1 = Person()

    print(repr(cls1))
    print(str(cls1))
    print("Formatted: {0}".format(cls1))
    print(bytes(cls1))


if __name__ == '__main__':
    main()
