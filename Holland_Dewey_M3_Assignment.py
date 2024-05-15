import random
# Taking Inputs for lower & upper bounds of the range and number of guesses
lower = int(input("Enter Lower Bound: "))
upper = int(input("Enter Upper Bound: "))
nGuesses = int(input("Enter Maximum Number of Guesses: "))

# Generating random number between the lower and upper
x = random.randint(lower, upper)

print("\n\tYou've only have ", nGuesses," chances to guess an integer between ", lower, " and ", upper, " !\n")

# count the number of guesses.
count = 0

while count < nGuesses:
    count += 1

    # taking guessing number as input
    guess = int(input("Guess a number: "))

    # Condition testing of the guess
    if guess < x:
        print("Try Again! You guessed too small.")
    elif guess > x:
        print("Try Again! You guessed too high.")
    else:
        print("Congratulations! You guessed the number in ", count, " tries!")
        break

# If Guessing is more than required number of guesses, shows this output.
if count >= nGuesses:
    print("\nThe number is %d" % x)
    print("\tBetter Luck Next time!")
