#include <stdlib.h>
int* countBits(int n, int* returnSize) {
    *returnSize = n + 1;
    int* ans = (int*)malloc((*returnSize) * sizeof(int));
    ans[0] = 0;
    for (int i = 1; i <= n; i++) {
        if(i%2==0){
            ans[i]=ans[i/2];
        }
        else{
            ans[i]=ans[i/2]+1;
        }
    }


Input: n = 2
Output: [0,1,1]
Explanation:
0 --> 0
1 --> 1
2 --> 10

   Input: n = 5
Output: [0,1,1,2,1,2]
Explanation:
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101
