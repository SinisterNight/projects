#Dewey Holland

#Desc this contains two seperate functions a main and greedy change
#Greedy change takes the values of n and denominations
#it initalizes the coin array, count, loops through the denominations 
# and appends the coun array with the coin value so that you can get a
#visual  representation of the coins in the 'main' section the user
#is prompted input as long as the user does not submit nothing the order
#in which the denominations are submitted does not matter
#it is sorted into ascending order using sort()
#spliced to reverse it into descending order so the algo
#can run properly
def greedyChange(n, denominations):
#creation of greedyChange let the fate of your money be left to me
    coinArray = []
    count = 0
    #declarations of coinArray and  Count
    for i in range(len(denominations)):
    #continues loop as long as the numbers are in range
        while n >= denominations[i]:
        #while n is greather than denominations
            coinArray.append(denominations[i])
            # appending coinArray with denominations[index]
            n = n - denominations[i]
            # setting value to n minus denominations index 
            count += 1
#return coinArray also incrementing the value of count
    return coinArray

# Main
n = int(input("Enter treasure return value:[change amount N] "))
#change amount
denominations = []
#set denominations and  denom input we are needing to get user input to handle indefinate value
denomInput = int(input("Present thou Scarabs [denomination M]: "))
for i in range(denomInput):
    denomination = int(input(f"Enter Scarab Value [denominations Value] {i+1}: "))
    denominations.append(denomination)
#list needs to be sorted or it will mess up our greedy
denominations.sort()
#it needs to be sliced so that it is facing the correct way desc order
denominations = denominations[::-1]
treasure = greedyChange(n, denominations)
#call to greedyChange setting value to treasure(Change)
print("Here doth go thou change ---> Feral imps await the treasure ", treasure)
