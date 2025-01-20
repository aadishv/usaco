import random
from uuid import uuid4
import string
random.seed(42)
#
repeating = "dfgjhdflkjgdfhkjgdf"
s = ""
for i in range(5*10**3):
    if random.random() > 0.10:
        s += repeating
    s += ''.join([random.choice(string.ascii_lowercase) for j in range(1000)])
print(s)
print(repeating)
