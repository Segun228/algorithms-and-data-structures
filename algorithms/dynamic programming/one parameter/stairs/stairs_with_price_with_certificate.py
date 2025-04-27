n = int(input())
dp = []
dp.append([])
dp.append([])
dp.append([])
for i in range(n+4):
    dp[0].append(0)
    dp[1].append(0)
    dp[2].append(0)
print(dp)
for i in range(1, n+1):
    dp[0][i] = int(input())
dp[0][0] = 0
dp[1][1] = dp[0][1]
dp[1][2] = dp[0][2]+dp[1][1]
dp[2][2] = 1
print(dp)
for i in range(3, n+1):
    if(dp[1][i-1] > dp[1][i-2]):
        dp[1][i] = dp[0][i] + dp[1][i-1]
        dp[2][i] = i-1
    else:
        dp[1][i] = dp[0][i] + dp[1][i-2]
        dp[2][i] = i-2
print(f"Ответ: {dp[1][n]}")
consequence = []
last_step = dp[2][n]
print(dp)
while(last_step!=0):
    consequence.append(last_step)
    last_step = dp[2][last_step]

consequence.reverse()
print("Последовательность шагов:")
print(consequence)