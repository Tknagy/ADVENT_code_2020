import csv
import time
import numpy as np
# print('Exercise 1 from Advent of Code')


numbersArray = []

with open('entries', newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
    for row in spamreader:
        num = int(', '.join(row))
        numbersArray.append( num)



# print('======== Part 1========')
# going through all the numbers and checking which one sums up 2020
# for num1 in numbersArray:
#     for num2 in numbersArray:
#         if(num1 + num2 == 2020):
#             # print(num1)
#             # print(num2)
#             print('Multiplied ' + str(num1*num2))

start = time.process_time()

# Now doing the part 2, for 3 numbers
print()
print()
print('======== Part 2========')
# going through all the numbers and checking which one sums up 2020
for index1 in range(0,len(numbersArray)):
    num1 = numbersArray[index1]
    for index2 in range(index1,len(numbersArray)):
        num2 = numbersArray[index2]
        for index3 in range(index2,len(numbersArray)):
            num3 = numbersArray[index3]
            if(num1 + num2 + num3 == 2020):
                print(num1)
                print(num2)
                print(num3)
                num4 = num1*num2*num3
                print('Result: ' + str(num4))
                


end = time.process_time()


print('Execution time ' + str(end - start) + 's')
