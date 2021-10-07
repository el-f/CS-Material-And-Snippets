import heapq
import random


def sorted_generator(iterable):
    heap = list(iterable)
    heapq.heapify(heap)
    return (heapq.heappop(heap) for _ in range(len(heap)))


if __name__ == '__main__':
    arr = list(range(30))
    random.shuffle(arr)
    print(arr)
    sg = sorted_generator(arr)
    for x in sg:
        print(x, end=" ")
