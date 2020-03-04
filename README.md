# Dice Chance
This program calculates the chances of getting certain values from dice throws.
### Input/Output
This program uses the cin and cout streams to input/output data. To input you use the (cubes)d(sides) format. For example:`3d6` will calculate the chance of all values that you can get from 3 6 sided dices (cubes). You can also add +(value) or -(value) to offset the throws by a value and >(value), <(value) or =(value) to get the chance of the throw being bigger than, smaller than or equal to a certain value, for example `2d10+5>12`.
### Why
I wanted to try out dynamic programming and compare it with my old method. With smaller numbers the difference is minimal, but when above 6 cubes my old program can take a while to finish and 10d10 will take (probably) a couple of hours, while this program can calculate any number of cubes/sides pretty much instantly.
