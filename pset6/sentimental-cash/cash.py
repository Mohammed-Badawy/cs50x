def main():
    # Prompt user for float
    owed = 0.0

    while True:
        try:
            owed = float(input("Change: "))
        except ValueError:
            owed = 0.0
            pass

        if owed > 0:
            break
    
    # Convert to cents
    cents = owed * 100

    print(get_coins(cents))


def get_coins(cents):
    quarters = dimes = nickles = pennies = 0

    # Count quarters
    quarters = cents // 25
    cents %= 25

    # Count dimes
    dimes = cents // 10
    cents %= 10

    # Count nickles
    nickles = cents // 5
    cents %= 5

    # Count pennies
    pennies = cents // 1

    return (quarters + dimes + nickles + pennies)


if __name__ == "__main__":
    main()