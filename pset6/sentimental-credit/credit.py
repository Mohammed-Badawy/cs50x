# Global
AMEX = 15
MASTERCARD = 16
VISA = [13, 16]


def main():
    # Prompt user for credit card number
    card = input("Number: ")

    # Not digits
    if not card.isdigit():
        print("INVALID")
        return

    # Card length
    ln = len(card)

    # First two digits
    first_digits = int(card[0:2])

    # Calculate checksum
    card = int(card)
    checksum = calculate_checksum(card)

    # Check card type and print it
    if is_AMEX(checksum, first_digits, ln):
        print("AMEX")
    elif is_mastercard(checksum, first_digits, ln):
        print("MASTERCARD")
    elif is_visa(checksum, first_digits, ln):
        print("VISA")
    else:
        print("INVALID")


def calculate_checksum(card):
    last2second = 0
    last = 0
    is_second_to_last = False

    while card > 0:
        # Get last recent digit
        last_digit = card % 10

        # Get second to last digit
        if is_second_to_last:
            last_digit *= 2
            # Calculate the product of 2tolast
            if last_digit > 9:
                last2second += (last_digit % 10)
                last2second += (last_digit // 10)
            else:
                last2second += last_digit
        # Get last digits total
        else:
            last += last_digit
        
        is_second_to_last = not is_second_to_last
        card //= 10
    
    return (last2second + last) % 10


# Check AMEX
def is_AMEX(checksum, first_digits, ln):
    return (checksum == 0) and (first_digits in [34, 37]) and (ln == AMEX)


# Check MASTERCARD
def is_mastercard(checksum, first_digits, ln):
    return (checksum == 0) and (first_digits >= 51 and first_digits <= 55) and (ln == MASTERCARD)


# Check VISA
def is_visa(checksum, first_digits, ln):
    return (checksum == 0) and (first_digits // 10 == 4) and (ln in VISA)


if __name__ == "__main__":
    main()