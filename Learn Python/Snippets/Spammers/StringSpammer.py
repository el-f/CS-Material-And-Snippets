import pyautogui
import time

from Snippets.Spammers.pastas.short_pastas import breastfeed, cd, supermarket, t3h, gaming_laptop, dt
from Snippets.Spammers.pastas.beeScript import b as bee
from Snippets.Spammers.pastas.shrekScript import ss as shrek
from Snippets.Spammers.pastas.NavySeal import navySeal

words = ""


def spam():
    global words
    choice = -1
    while choice < 0:
        choice = input("1) bee movie \n2) shrek \n3) navy seal \n4) catholic daughter \n5) penguin of doom \n6) "
                       "supermarket \n7) breastfeed \n8) gaming laptop \n9) dt 2+2")
        choice = int(choice)
        if choice == 1:
            words = bee().split()
        elif choice == 2:
            words = shrek().split()
        elif choice == 3:
            words = navySeal().split()
        elif choice == 4:
            words = cd().split()
        elif choice == 5:
            words = t3h().split()
        elif choice == 6:
            name = input("please enter name of the person you saw in the supermarket")
            city = input("please enter the city the supermarket is in")
            words = supermarket(name, city).split()
        elif choice == 7:
            name = input("please enter name")
            words = breastfeed(name).split()
        elif choice == 8:
            words = gaming_laptop().split()
        elif choice == 9:
            words = dt().split()
        else:
            choice = -1

    print("4 seconds until spam")
    time.sleep(4)
    for w in words:
        pyautogui.write(w)
        pyautogui.press('enter')


def main():
    spam()


if __name__ == '__main__':
    main()
