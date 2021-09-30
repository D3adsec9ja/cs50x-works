from cs50 import get_int


def get_height(min=1, max=8):
    #Prompt user height
    while True:
        h = get_int("Height: ")
        if h >= min and h <= max:
            return h


def print_pyramid(b):
    #Print n height of half-pyramid to console.
    for dash in range(1, b + def main():
    owed = get_owed()
    coins = calc_coins(owed)
    print(f"{coins}")


def get_owed():
    while True:
        try:
            owed = float(input("Cash owed: "))
            if owed > 0:
                break
        except ValueError:
            None

    return owed


def calc_coins(owed):
    cents = round(owed * 100)
    coins = 0

    while cents > 0:
        if cents >= 25:
            cents -= 25
        elif cents >= 10:
            cents -= 10
        elif cents >= 5:
            cents -= 5
        else:
            cents -= 1
        coins += 1
    return coins


main()1):
        print(" "*(b - dash) + "#" * dash)


def main():
    height = get_height()
    print_pyramid(height)


if __name__ == "__main__":
    main()