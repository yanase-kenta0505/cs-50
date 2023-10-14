from cs50 import get_string


def count_char(text):
    char_count = 0
    for char in text:
        if char.isalpha():
            char_count += 1
    
    return char_count


def count_word(text):
    return len(text.split())


def count_sentence(text):
    sentence_count = 0
    for char in text:
        if char == "." or char == "!" or char == "?":
            sentence_count += 1

    return sentence_count


def evaluation_input_grade_level(char_count, word_count, sentence_count):
    L = (char_count / word_count) * 100
    S = (sentence_count / word_count) * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    return index


text = get_string("Text: ")

char_count = count_char(text)
word_count = count_word(text)
sentence_count = count_sentence(text)

readability_index = evaluation_input_grade_level(char_count, word_count, sentence_count)

if readability_index < 1:
    print("Before Grade 1")
elif readability_index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {round(readability_index)}")
