def main():
    b = bytes([0x41, 0x42, 0x43, 0x44])
    print(b)

    s = "this is a string!"
    print(s)

    s2 = b.decode('utf-8')
    print(s + " " + s2)

    b2 = s.encode('utf-8')
    print(b + b2)

    b3 = s.encode('utf-32')
    print(b3)


if __name__ == '__main__':
    main()
