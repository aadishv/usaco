import random
def generate_test_case():
    THRESHOLD = 10**9
    a = random.randint(0, THRESHOLD)
    b = random.randint(a, THRESHOLD)
    c = random.randint(b, THRESHOLD)
    nums = [a,b,c,a+b,b+c,c+a,a+b+c]
    random.shuffle(nums)
    nums = map(str, nums)
    return " ".join(nums), f"{a} {b} {c}"
NUM_TEST_CASES = 10
for i in range(NUM_TEST_CASES):
    t, a = generate_test_case()
    print("TEST     :", t)
    print("ANSWER   :", a)
