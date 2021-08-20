#include <iostream>
using namespace std;

#define N 7

int main(void)
{
    int A[N] = {2, 14, 3, 6, 7, 5, 8}; /* ソートしたい配列 */

    /*
     配列Aの最初からn-1番目の要素において以下を繰り返す
        最小の要素を見つけてA[1]と交換する
        2番目に小さい要素を見つけてA[2]と交換する
    */

    int min = A[0];
    int buff = A[0];
    int num = 0;
    for (int i = 0; i < N - 1; i++)
    {
        min = A[i];
        num = i;
        for (int j = i; j < N; j++)
        {
            if (min > A[j])
            {
                printf("%d-%d:%d is smaller than %d\n", i, j, A[j], min);
                min = A[j];
                num = j;
            }
            else
            {
                printf("%d-%d:%d is bigger than %d\n", i, j, A[j], min);
            }
        }

        if (num != i) /* 最小値が暫定のものから変化しているかどうか判定 */
        {
            printf("->switch %d and %d\n", A[num], A[i]);
            buff = A[num];
            A[num] = A[i];
            A[i] = buff;
        }

        for (int i = 0; i < N; i++)
        {
            printf("%d ", A[i]);
        }
        printf("\n\n");
    }

    printf("\nresult:");
    for (int i = 0; i < N; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}