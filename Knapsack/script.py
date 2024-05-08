

def knapsack(w, p, C):
    n = len(w)
    profit = [0] * (C + 1)

    for c in range(1, C + 1):
        for i in range(n):
            if w[i] <= c:
                profit[c] = max(profit[c], profit[c - w[i]] + p[i])
    
    for i, p in enumerate(profit):
        print(f"Capacity {i}: {profit[i]}")

    return profit[C]

weightsA = [4,6,8]
weightsB = [5,6,8]
profits = [7,6,9]
print(knapsack(weights, profits, 14))
