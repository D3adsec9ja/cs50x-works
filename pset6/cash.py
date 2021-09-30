from cs50 import get_float


owed = -1
quarter = dime = nickle = penny = 0

while owed < 0:
    owed = get_float("Change owed: ") * 100

quarter = int(owed / 25) if owed // 25 >= 1 else 0
owed -= quarter * 25

dime = int(owed/10) if owed // 10 >= 1 else 0
owed -= dime * 10

nickle= int(owed / 5) if owed // 5 >= 1 else 0
owed -= nickle * 5

penny = owed if owed // 1 >= 1 else 0
owed -= penny * 1

print(int(quarter + dime + nickle + penny))