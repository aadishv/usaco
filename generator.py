import random
random.seed(43)
N = 100_000
for i in range(N):
    print(random.choice("1234567890"), end="")
