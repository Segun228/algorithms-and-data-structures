n = int(input())
dp = []
for i in range(n+1):
    dp.append(-1)
dp[0] = 1
dp[1] = 1

def fib_querry(n, dp):
    if(dp[n] != -1):
        print(dp[n])
        return dp[n]
    dp[n] = fib_querry(n-1, dp) + fib_querry(n-2, dp)
    return dp[n]

