import random
random.seed(42)
# Generate test case
def generate_test():
    n = 500_000
    q = 0

    # Create a sequence with some patterns
    sequence = []
    for i in range(2, n+2):
        sequence.append(i % n//1.5)
    random.shuffle(sequence)

    print(f"{n}, {q}")
    print(" ".join(map(str, sequence)))
generate_test();
