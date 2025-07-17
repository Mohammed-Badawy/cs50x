from csv import DictReader
from sys import argv, exit


def main():

    # Check for command-line usage
    if len(argv) != 3:
        print("Usage: python dna.py DATABASE SEQUENCE")
        exit(1)

    # Read database file into a variable
    try:
        database_file = open(argv[1], "r")
    except FileNotFoundError:
        print(f"Couldn't open file {argv[1]}")
        exit(1)
    
    # Read data from database file
    reader = DictReader(database_file)
    
    # List of dictionaries for persons' dna info
    database = []

    for p in reader:
        database.append(p)

    # Close database file
    database_file.close()

    # Read DNA sequence file into a variable
    try:
        sequence_file = open(argv[2], "r")
    except FileNotFoundError:
        print(f"Couldn't open file {argv[2]}")
        exit(1)
    
    # Read sequence sample
    sequence = sequence_file.read()

    # Close sequence file
    sequence_file.close()

    # Find longest match of each STR in DNA sequence
    str_counts = {}

    # Iterate through fieldnames except "name" 
    for k in reader.fieldnames[1:]:
        str_counts[k] = longest_match(sequence, k)

    # Check database for matching profiles
    for p in database:
        
        found = True

        for k in str_counts.keys():
            if int(p[k]) != str_counts[k]:
                found = False
                break
        # Found match
        if found:
            print(p["name"])
            return
    else:
        print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
