MAX = 510000
MOD = 1000000007

fac = [1] * MAX
finv = [1] * MAX

def COMinit():
    for i in range(2,MAX):
        fac[i] = fac[i-1] * i
        fac[i] %= MOD
        finv[i] = pow(fac[i],MOD-2,MOD)

def COM(n,k):
    if n < k:
        return 0
    if n < 0 or k < 0:
        return 0
    return fac[n] * (finv[k] * finv[n-k] % MOD) % MOD


COMinit()

N = int(input())
K = int(input())

print(COM(N-1+K,K))