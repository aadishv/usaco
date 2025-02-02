import random
random.seed(43)
# N = 7500
print(1)
MULT = 632
print(5*MULT, 1, 2)
s = """GWGWW
WGWWW
WBWGW
WWWWW
WWGWW"""
mys = s.split('\n')
for i in range(MULT):
    for l in mys:
        for j in range(MULT):
            print(l, end="")
        print()

# we expect the answer to be 4 * MULT^2
