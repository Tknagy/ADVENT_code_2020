print('Exercise of day 2 from Advent of Code')

with open('input.txt') as f:
    lines = [line.rstrip('\n') for line in f]

print('======== Part 1 ========')

numValidPasswords = 0

for line in lines:
    # whole line separated in columns ['5-6','p:','qpppvzp']'
    columns = line.split()
    # getting min and max
    min = int(columns[0].split('-')[0])
    max = int(columns[0].split('-')[1])
    # getting the letter of the line
    letter = columns[1].rstrip(':')
    # the password itself
    password = columns[2]
    # checking if valid
    if( (password.count(letter) >= min)  and (password.count(letter) <= max)):
        numValidPasswords+=1

print('Answer ' + str(numValidPasswords))
print()
print('======== Part 2 ========')

numValidPasswords = 0

for line in lines:
    # whole line separated in columns ['5-6','p:','qpppvzp']'
    columns = line.split()
    # getting the positions
    index1 = int(columns[0].split('-')[0]) - 1
    index2 = int(columns[0].split('-')[1]) - 1
    # getting the letter of the line
    letter = columns[1].rstrip(':')
    # the password itself
    password = columns[2]
    # checking if valid
    if ( password[index1] == letter and password[index2] != letter ) or ( password[index1] != letter and password[index2] == letter ) :
        numValidPasswords+=1


print('Answer ' + str(numValidPasswords))