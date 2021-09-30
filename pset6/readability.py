from cs50 import get_string


def get_text():
    # Prompt for text. If user enters an empty string, prompt again.
    while True:
        word = get_string("Text: ")
        if word != "":
            return word


def text_parser(text):
    # Helper function for parse input text.
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    return letters, words, sentences


def count_letters(text):
    # Count the number of letters
    return len([c for c in text if c.isalnum()])


def count_words(text):
    # Count the number of words
    return len([w for w in text.split(' ') if w != ""])


def count_sentences(text):
    # Count the number of sentences
    return len([w for w in text.replace('? ', '. ').split('.') if w != ""])


def formula(letters, words, sentences):
    # according to Coleman-Liau index formula.
    # L is the average number of letters per 100 words
    L = float(letters) / words * 100.0

    # S is the average number of sentences per 100 words
    S = float(sentences) / words * 100.0

    return round(0.0588 * L - 0.296 * S - 15.8)


def the_grade(grade):
    if grade >= 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {grade}")


def main():
    text = get_text()
    letters, words, sentences = text_parser(text)
    grade = formula(letters, words, sentences)
    the_grade(grade)


if __name__ == "__main__":
    main()