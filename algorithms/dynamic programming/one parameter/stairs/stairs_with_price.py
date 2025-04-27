n = int(input())
dp = [[0]*(n+5)]*2
print(dp)
for i in range(1, n+1):
    dp[0][i] = int(input())
dp[0][0] = 0
dp[1][1] = dp[0][1]
dp[1][2] = dp[0][2]+dp[1][1]
for i in range(3, n+1):
    dp[1][i] = dp[0][i] + max(dp[1][i-1], dp[1][i-2])
print(f"Ответ: {dp[1][n+1]}")