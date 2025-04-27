n = int(input())
dp = []
dp.append([])
dp.append([])
dp.append([])
for i in range(n+4):
    dp[0].append(0)
    dp[1].append(1)
    dp[2].append(0)
print(dp)
for i in range(n):
    dp[0][i] = int(input())
dp[1][0] = 1
for i in range(1, n):
    for k in range(i-1, -1, -1):
        if(dp[0][k]<=dp[0][i]):
            if(dp[1][k]+1 > dp[1][i]):
                dp[1][i] = dp[1][k]+1
print(f"Максимальная длина подпоследовательности: {max(dp[1])}")