from cs50 import get_int


def print_pyramid(height):
    for i in range(1, height + 1):
        # スペースの数
        for _ in range(height - i):
            print(" ", end="")
        for _ in range(i):
            print("#", end="")

        print()


while True:
    try:
        height = get_int("Height: ")
        if 1 <= height <= 8:
            break

    except ValueError:
        pass

print_pyramid(height)
