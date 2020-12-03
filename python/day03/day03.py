print('Exercise of day 3 from Advent of Code')

with open('input.txt') as f:
    lines = [line.rstrip('\n') for line in f]

def walk_count(steps_right, steps_down):
    xPos = 0
    yPos= 0
    numTrees = 0
    while yPos < len(lines):
        line = lines[yPos]
        if line[xPos] == '#':
            numTrees += 1
        xPos += steps_right
        yPos += steps_down
        if(xPos >= len(line)):
            xPos = xPos - len(line)
    return numTrees

print('======== Part 1 ========')
        
print('Answer 3_1 -> ' + str(walk_count(3, 1)))

print('======== Part 2 ========')
ans1_1 = walk_count(1, 1)
ans3_1 = walk_count(3, 1)
ans5_1 = walk_count(5, 1)
ans7_1 = walk_count(7, 1)
ans1_2 = walk_count(1, 2)
print('Multiplied ' + str(ans1_1 * ans3_1 * ans5_1 * ans7_1 * ans1_2))