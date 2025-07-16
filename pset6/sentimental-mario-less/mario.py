def main():
    # Prompt user for a positive integer between 1 & 8
    height = 0

    while True:
        try:
            height = int(input("Height: "))
        except ValueError:
            height = 0
            pass

        if (height > 0) and (height <= 8):
            break
    
    # Draw right-aligned pyramid
    draw_pyramid(height)


def draw_pyramid(h):
    for i in range(h):
        # Draw spaces
        print(" " * (h - i - 1), end="")

        # Draw bricks
        print("#" * (i + 1), end="")

        # New row
        print()


if __name__ == "__main__":
    main()