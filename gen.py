import sys
from random import randint
tipo = sys.argv[1]
n, m, k = None, None, None
if tipo == "pequeno":
    n, m, k = 10, 10, 3
elif tipo == "medio":
    n, m, k = 31, 31, 5
else:
    n, m, k = 100, 100, 20
print(n, m, k)
for _ in range(n):
    for _ in range(m):
        print(randint(1, k), end=' ')
    print()
