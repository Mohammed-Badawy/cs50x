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
    
    # Draw pyramids
    draw_pyramids(height)


def draw_pyramids(h):
    for i in range(h):
        # Draw right-aligned pyramid
        print(" " * (h - i - 1), end="")  # Draw spaces
        print("#" * (i + 1), end="")     # Draw bricks

        # Two spaces between pyramids
        print("  ", end="")

        # Draw left-aligned pyramid with new row
        print("#" * (i + 1))


if __name__ == "__main__":
    main()