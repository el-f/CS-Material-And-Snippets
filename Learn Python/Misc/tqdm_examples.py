from tqdm import tqdm, trange
import random
import time


# an easy progress bar generator

def tqdm_example_1():
    for _ in tqdm(range(10)):
        time.sleep(0.2)


def tqdm_example_2():
    for i in trange(3, desc="outer_loop"):
        for j in trange(10, desc="inner_loop"):
            time.sleep(0.01)


def tqdm_example_3(add_tot=False):
    max_iter = 100
    tot = 0

    if add_tot:
        bar = tqdm(desc="update example", total=max_iter)
    else:
        bar = tqdm()

    while tot < max_iter:
        update_iter = random.randint(1, 5)
        bar.update(update_iter)
        tot += update_iter
        time.sleep(0.03)


def tqdm_example_4():
    t = trange(100)
    for i in t:
        t.set_description(f"on iter {i}")
        time.sleep(0.02)


if __name__ == "__main__":
    # tqdm_example_1()
    # tqdm_example_2()
    # tqdm_example_3()
    # tqdm_example_3(True)
    tqdm_example_4()
