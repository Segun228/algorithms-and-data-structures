n = int(input())
dp = []
dp.append([])
dp.append([])
dp.append([])
for i in range(n+4):
    dp[0].append(0)
    dp[1].append(1)
    dp[2].append(0)
for i in range(n):
    dp[0][i] = int(input())
dp[1][0] = 1
dp[2][0] = 0
for i in range(1, n):
    for k in range(i-1, -1, -1):
        if(dp[0][k]<=dp[0][i]):
            if(dp[1][k]+1 > dp[1][i]):
                dp[1][i] = dp[1][k]+1
                dp[2][i] = k
print(f"Максимальная длина подпоследовательности: {max(dp[1])}")
consequence = []
last_el = dp[1].index(max(dp[1]))
while(last_el!=0):
    consequence.append(dp[0][last_el])
    last_el = dp[2][last_el]
consequence.append(dp[0][last_el])
consequence.reverse()
print(consequence)