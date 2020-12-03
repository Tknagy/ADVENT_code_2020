import csv
import time

print('Exercise 1 from Advent of Code')

numbersArray = []

with open('ex1input.csv', newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
    for row in spamreader:
        # print(', '.join(row))
        numbersArray.append(int(', '.join(row)))

print('======== Part 1========')
# going through all the numbers and checking which one sums up 2020
for num1 in numbersArray:
    for num2 in numbersArray:
        if(num1 + num2 == 2020):
            print(num1)
            print(num2)
            print('Multiplied ' + str(num1*num2))
            break

start = time.time()

# Now doing the part 2, for 3 numbers
print()
print()
print('======== Part 2========')
# going through all the numbers and checking which one sums up 2020
for num1 in numbersArray:
    for num2 in numbersArray:
        for num3 in numbersArray:
            if(num1 + num2 + num3 == 2020):
                print(num1)
                print(num2)
                print(num3)
                print('Multiplied ' + str(num1*num2*num3))
                break

end = time.time()
print()

print('Execution time 2nd part ' + str(end - start) + 's')