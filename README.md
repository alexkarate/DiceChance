# Dice Chance
This program calculates the chances of getting certain values from dice throws.
### Input/Output
This program uses the cin and cout streams to input/output data. To input you use the (cubes)d(sides) format. For example:`3d6` will calculate the chance of all values that you can get from 3 6 sided dices (cubes). You can also add +(value) or -(value) to offset the throws by a value and >(value), <(value) or =(value) to get the chance of the throw being bigger than, smaller than or equal to a certain value, for example `2d10+5>12`.
### Algorithm
The program is split into two parts: the main part which parses the input data and a seperate library that does the actual calculations. The library uses dynamic programming to calculate the chances of throws with n dices by using an interesting pattern that I found. Basically, the amount of possible dice throws (matches) that equal a value 'c' can be calculated by taking the amount of matches that equal a value 'c-1', adding the amount of matches with one less dice that equal a value 'c-1', and subtracting the ammount of matches with one less dice that equal to a value 'n-c', where n is the largest possible value, that a dice throw can equal (dices * sides). You can visualize the algorithm by writing the matches of the current dice throw in the middle, and the matches of the previous to the left and to the right:
```
 1: 0  0  0
 2: 1  0  0
 3: 2  1  0
 4: 3  3  0
 5: 4  6  0
 6: 3  10 1
 7: 2  12 2
 8: 1  12 3
 9: 0  10 4
10: 0  6  3
11: 0  3  2
12: 0  1  1
13: 0  0  0
```
In this example (3d4) you can see that any value in the middle equals to the value above + the value to the top left - the value on the top right.
### Why
Some time ago my brother asked me to make a program that would calculate the probability of getting certain values from dices. I made the program, but it was slow and limited, so I wanted to try out dynamic programming and compare it with my old method. With smaller numbers the difference is minimal, but when above 6 cubes my old program can take a couple of seconds to finish and 10d10 would take (probably) a couple of hours. But this program can calculate any number of cubes/sides pretty much instantly.
