# Dewey Holland

# DESC the program is Longest common substring. The program consists of a method creation print_lcs which takes in the values c x y i and j it then contains a few conditional statements
# which go through the logic of the program to best find the matching values. comments are placed in approriate locations to besst explain what the prrogram is doing
# in this case python felt like the most straight forward language to use because of its data manipulation qualities that are used often in the field of data science 
# in my opinion LCS would follow under that category so i felt it would be apporiate to set it up as such. in the main section the variables are initalized and the c table is filled in with the corresponding values and a call to the function is made.

# method creation takes c x y i and j and matches
def print_lcs(c, X, Y, i, j, matches):
    print(f"Current matches: {matches}")
    # testing if base case return and do nothing or value at 0
    if i == 0 or j == 0:
        #matches get sliced and feel the pain :^)
        return matches[::-1]
    if X[i - 1] == Y[j - 1]:
        # if the letters are the same or equal they are within the set of lcs
        # print with recursion call to lcs
        matches.append(X[i - 1]) #append list
        print(f"Matched: {X[i - 1]}") #print matched
        print(f"Matches: {matches}") #print matches
        return print_lcs(c, X, Y, i - 1, j - 1, matches)
    # if not the same based on the comparison values of c table
    elif c[i - 1][j] > c[i][j - 1]:
        
        return print_lcs(c, X, Y, i - 1, j, matches)
    else:
        
        return print_lcs(c, X, Y, i, j - 1, matches)

# Example on pa pdf
X = "spanking"
Y = "amputation"
m, n = len(X), len(Y) #setting m and n to value of length of x and y
d = [[0] * (n + 1) for _ in range(m + 1)]
print("inital c table:")
for row in d:
    print(row)
# loop to iterate and fill in the c  table with the new values of n and m
c = [[0] * (n + 1) for _ in range(m + 1)]
for i in range(1, m + 1):
    for j in range(1, n + 1):
        if X[i - 1] == Y[j - 1]:
            c[i][j] = c[i - 1][j - 1] + 1
        else:
            c[i][j] = max(c[i - 1][j], c[i][j - 1])
print(" c table:") #print formatting
for row in c:
    print(row)
# Assume c table is filled as per the dynamic programming algorithm
result = print_lcs(c, X, Y, m, n, []) # This will print the LCS between X and Y this world will know PAIN
print(f"Result: {result}")
if len(result) == 0:  # Check if result is empty and assign an empty list if so
    result = []
print(f"Matches: {result}")  # Print the matched characters
print(''.join(result)) #print joined result
