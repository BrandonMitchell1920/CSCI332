from random import *
weight = [randint(1, 100) for x in range(randint(4, 14))]
val = [randint(1, 100) for x in range(len(weight))]
with open("test99.in", 'w') as file:
    file.write(str(randint(50, 150)) + " " + str(len(weight)) + "\n")
    for x in range(len(weight)):
        file.write(str(weight[x]) + " " + str(val[x]) + "\n")