def main():
    # Prompt user for text
    text = input("Text: ")

    # Count sentences, words, letters
    counts = get_counts(text)

    sentences = counts["sentences"]
    words = counts["words"]
    letters = counts["letters"]

    # Calculate Coleman-Liau index formula
    # index = 0.0588 * L - 0.296 * S - 15.8

    l_avg = (letters / words) * 100
    s_avg = (sentences / words) * 100

    index = int(round((0.0588 * l_avg) - (0.296 * s_avg) - 15.8))

    print_grade(index)


# Get text counts
def get_counts(text):
    counts = {
        "sentences": 0,
        "words": 0,
        "letters": 0
    }

    for c in text:  # sentences
        if c in ["!", "?", "."]:
            counts["sentences"] += 1
        elif c == " ":  # words
            counts["words"] += 1
        elif c.isalpha():  # letters
            counts["letters"] += 1
    
    # Last word in a text
    counts["words"] += 1

    return counts


# Print reading grade according to index
def print_grade(index):
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()