v = int(input("Введите количество вершин\n"))
print()
e = int(input("Введите количество ребер\n"))
matrix = []
for i in range(v):
    matrix.append([])
    for j in range(v):
        matrix[i].append(0)

for i in range(e):
    print(f"Введите вершины {i+1} ребра")
    pair = (input()).split(" ")
    first = int(pair[0])
    second = int(pair[1])
    matrix[first-1][second-1] = matrix[second-1][first-1] = 1

for i in range(v):
    for j in range(v):
        print(matrix[i][j], end="\t")
    print()

