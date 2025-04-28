import sys


def main():
    def dfs(matrix, current, target, steps, n):
        if current == target:
            return steps
        
        flag = -1
        for i in range(n):
            if matrix[current][i] == 1:
                matrix[current][i] = -1
                matrix[i][current] = -1
                new_way = dfs(matrix, i, target, steps + 1, n)
                if flag == -1:
                    flag = new_way
                elif new_way != -1:
                    flag = min(flag, new_way)
        return flag

    n = int(input())
    matrix = [list(map(int, input().split())) for _ in range(n)]
    a, b = map(int, input().split())
    result = dfs(matrix, a-1, b-1, 0, n)
    print(result if result != -1 else -1)

if __name__ == "__main__":
    main()