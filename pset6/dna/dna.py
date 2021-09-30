import sys
import csv


args = sys.argv

STRS_H = []


def load_database():
    data = []

    with open(args[1], "r") as f:
        read = csv.DictReader(f)

        global STRS_H
        STRS_H = read.fieldnames[1:]

        for dash in read:
            for a in STRS_H:
                dash[a] = int(dash[a])
            data.append(dash)

    return data


def load_sequence_data():
    with open(args[2], "r") as f:
        seq = f.readline()

    return seq


def str_sequence_counter(seq):
    counter = {a: 0 for a in STRS_H}

    for a in counter:
        n = find_maxnum_key(a, seq)
        counter[a] = n

    return counter


def find_maxnum_key(key, text):
    count = 0
    pattern = key
    while pattern in text:
        count += 1
        pattern += key

    return count


def search_database(target, database):
    for people in database:
        if all([people[a] == target[a] for a in STRS_H]):
            return people["name"]

    return "No match"


def main():
    # Check for correct number of args.
    if len(args) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    data = load_database()

    seq = load_sequence_data()

    target = str_sequence_counter(seq)

    result = search_database(target, data)

    print(result)


if __name__ == "__main__":
    main()