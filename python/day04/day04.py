import re

print('Exercise of day 4 from Advent of Code')

with open('input.txt') as f:
    lines = [line.rstrip('\n') for line in f]

requiredKeys = ['byr','iyr','eyr','hgt','hcl','ecl','pid']

def hasAllKeys(completeEntry: str, keys: [str]) -> bool:
    for key in keys:
        if key not in completeEntry:
            return False
    return True

def extractValue(text: str, key: str):
    something = re.search(r'{0}(\w+) '.format(key), text)
    if something is not None:
        return something.groups()[0]
    else:
        # print('it will fail here')
        # print('extract {0}'.format(key))
        # print('${0}$'.format(text))
        return '0'

def isInRange(value: int, min: int, max: int) -> bool:
    return value <= max and value >= min     

def isValid(currentEntry: str) -> bool: 
    # checking at first if it has all needed entries
    if not hasAllKeys(currentEntry, requiredKeys):
        return False

    byr = int(extractValue(currentEntry, 'byr:'))
    if(not isInRange(byr, 1920, 2002)):
        return False
    iyr = int(extractValue(currentEntry, 'iyr:'))
    if(not isInRange(iyr, 2010, 2020)):
        return False
    eyr = int(extractValue(currentEntry, 'eyr:'))
    if(not isInRange(eyr, 2020, 2030)):
        return False
    hgt = extractValue(currentEntry, 'hgt:')
    if 'cm' in hgt:
        if(not isInRange(int(hgt.replace('cm', '')), 150, 193)):
            return False
    elif 'in' in hgt:
        if(not isInRange(int(hgt.replace('in', '')), 59, 76)):
            return False
    else:
        return False
    hcl = extractValue(currentEntry, 'hcl:#').strip()
    if(not re.match(r'([a-fA-F]|[0-9]){6}$', hcl)):
        return False
    ecl = extractValue(currentEntry, 'ecl:').strip()
    if(not re.match(r'(amb|blu|brn|gry|grn|hzl|oth)$', ecl)):
        return False
    pid = extractValue(currentEntry, 'pid:').strip()
    if(not re.match(r'([0-9]{9})$', pid)):
        return False

    return True

numValid = 0
print('======== Part 1 ========')
currentEntry = '' 
for line in lines:
    if line.strip() == '' :
        if hasAllKeys(requiredKeys, currentEntry):
            numValid += 1
        currentEntry = ''
    else:
        currentEntry+= line + ' '

print('Result ' + str(numValid))

numValid = 0
print('======== Part 2 ========')
currentEntry = '' 
for line in lines:
    if line.strip() == '':
        if isValid(currentEntry):
            numValid += 1
        currentEntry = ''
    else:
        currentEntry+= line + ' '

print('Result ' + str(numValid))