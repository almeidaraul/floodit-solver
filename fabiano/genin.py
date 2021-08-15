from random import randint as ri

n = 100
m = 100
k = 50
print(n, m, k)
for _ in range(n):
    for _ in range(m):
        print(ri(1, k+1), end=' ')
    print()
