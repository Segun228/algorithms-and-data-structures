v = int(input("Введите количество вершин\n"))
print()
e = int(input("Введите количество ребер\n"))
connection_list = []
for i in range(v):
    connection_list.append([])
    

for i in range(e):
    print(f"Введите вершины {i+1} ребра")
    pair = (input()).split(" ")
    first = int(pair[0])
    second = int(pair[1])
    connection_list[first-1].append(second-1)
    connection_list[second-1].append(first-1)

for i in range(v):
    print(f"{i+1}:", end="\t")
    for j in range(len(connection_list[i])):
        print(connection_list[i][j]+1, end="\t")
    print("\n")