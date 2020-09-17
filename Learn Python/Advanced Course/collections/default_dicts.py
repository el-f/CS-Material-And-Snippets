from collections import defaultdict


def main():
    fruits = ['apple', 'pear', 'orange' 'grape', 'banana',
              'apple', 'pear', 'orange' 'grape', 'banana']

    fruit_counter = defaultdict(int)
    fruit_counter2 = defaultdict(lambda: 100)

    for fruit in fruits:
        fruit_counter[fruit] += 1
        fruit_counter2[fruit] += 1

    for (k, v) in fruit_counter.items():
        print(k + ": " + str(v))

    print("\n")
    
    for (k, v) in fruit_counter2.items():
        print(k + ": " + str(v))


if __name__ == '__main__':
    main()
