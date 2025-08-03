import random
print(1)
N = 1_000_000
M = 1_000_000
print(N, M)
l = list(map(str, range(1, N + 1)))
random.shuffle(l)
print(' '.join(l))
