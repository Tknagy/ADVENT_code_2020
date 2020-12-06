print('Exercise of day 3 from Advent of Code')

with open('input.txt') as f:
    lines = [line.rstrip('\n') for line in f]

requiredKeys = ['byr','iyr','eyr','hgt','hcl','ecl','pid']

def hasAllKeys(keys: [str], completeEntry: str) -> bool:
    for key in keys:
        if key not in completeEntry:
            return False
    return True

print(hasAllKeys(requiredKeys, 'byr iyr'))

numValid = 0
print('======== Part 1 ========')
currentEntry = '' 
for line in lines:
    if line.strip() == '' :
        if hasAllKeys(requiredKeys, currentEntry):
            numValid += 1
        currentEntry = ''
    else:
        currentEntry+= ' ' + line

print('Result ' + str(numValid))