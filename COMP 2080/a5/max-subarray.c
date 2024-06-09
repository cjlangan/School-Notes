#include <stdio.h>
#include <stdlib.h>

// Find maximum sub array given an array
int maxSubarray(int *A, int j, int k);

int main(void)
{
    int arr[] = {0, 2, -5, 7, 1, 0, -3, 4, -4, -7, 8, 3, 2, -1};

    printf("The maximum sum within the subarray of contiguous"
            " elements is: %d\n", maxSubarray(arr, 0, 13));

    return EXIT_SUCCESS;
}

int maxSubarray(int *A, int j, int k)
{
    if(j == k)
    {
        return A[j];
    }
    // Middle index of array
    int m = (j + k) / 2;
    
    // find greatest sum starting from midpoint and heading left
    int sum = 0;
    int left = -999999;
    for(int i = m; i >= j; i--)
    {
        sum = sum + A[i];
        if(sum > left)
        {
            left = sum;
        }
    }

    // find greatest sum starting from midpoint (+1) and heading right
    sum = 0;
    int right = -999999;
    for(int i = m + 1; i <= k; i++)
    {
        sum = sum + A[i];
        if(sum > right)
        {
            right = sum;
        }
    }
    
    // Determining max subarrary from midpoint
    int curr_max = left + right;

    // Recursively calling for left and right half of the array
    int left_max = maxSubarray(A, j, m);
    int right_max = maxSubarray(A, m + 1, k);

    // Returning the maximum subarray
    if(curr_max > left_max && curr_max > right_max)
    {
        return curr_max;
    }
    else if(left_max > curr_max && left_max > right_max)
    {
        return left_max;
    }
    else
    {
        return right_max;
    }
}
