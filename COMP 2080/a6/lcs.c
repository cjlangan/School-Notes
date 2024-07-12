// Longest Common Substring Problem, where "cat" counts as a substring to "Cowabanter".
// R and S are string, indexed at j and k respectively.  Here is my memoization solution:

// Memoization
lcs(R, j, S, k)
    T is a j by k table, you can index it by T[j][k]. All values are initialised to negative infinity (-inf)
    if(T[j][k] != -inf)
        return T[j][k]
    else if(j == 0)
        for(int i = 0; i <= k; i++)
            if(R[0] == S[k])
                T[j][k] = 1
                return 1
            T[j][k] = 0
            return 0
    else if(k == 0)
        for(int i = 0; i <= j; i++)
            if(R[j] == S[0])
                T[j][k] = 1
                return 1
            T[j][k] = 0
            return 0
    else
        if(R[j] == S[k])
            T[j][k] = lcs(R, j-1, S, k-1)
            return T[j][k]
        else
            opt1 = lcs(R, j-1, S, k)
            opt2 = lcs(R, j, S, k-1)
            T[j][k] = max(opt1, opt2)
            return T[j][k]

// Tabulation
lcs(R, S)
    j = R.length -1
    k = S.length -1
    T is a j by k table
    
    // Handle all base cases
    for(int m = 0; m <= j; m++)
        for(int n = 0; n <= k; n++)
            if(R[m] == S[n])
                T[m][n] = 1
            else
                T[m][n] = 0;

    // Handling Recursive cases
    for(int m = 0; m <= j; m++)
        for(int n = 0; n <= k; n++)
            if(R[m] == S[n])
                T[m][n] = T[m-1][n-1] + 1
            else
                T[m][n] = max(T[m-1][n], T[m][n-1])

