n = int(input())
dp = []
for i in range(n+1):
    dp.append(-1)
dp[0] = 1
dp[1] = 1
print(dp[0], sep="\t")
print(dp[1], sep="\t")
for i in range(2, n+1):
    dp[i] = dp[i-1] + dp[i-2]
    print(dp[i], sep="\t")