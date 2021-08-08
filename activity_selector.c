#include <stdio.h>

#define n 11

void insert_activ(int[n + 2][n + 2]);

int S[n + 2][n + 2][n + 2]; /* 0 to n に両端のダミーを足したもの*/

int main(void)
{
    int c[n + 2][n + 2]; /* Sijの最適解のサイズを記録 */
    int ans[n + 2];
    int q;       /* 一時記憶 */
    int S_empty; /* Sijが空であるか判定するのに用いるカウンタ */
    int temp = 0;
    int i, j, k;

    insert_activ(c); /* 活動を設定、両立可能な活動を計算 */

    for (j = 0; j < n + 2; j++)
    {
        for (i = 0; i < n + 2 - j; i++)
        {
            q = -100;
            /* k=0(i=i+j)のときはelse以降の下の計算に入れられないので別枠で */
            if (i == i + j)
                q = 0;
            else
            {
                for (k = i; k < i + j; k++)
                {
                    if (c[i][i + j] != 0) /* Sijが空集合でないとき*/
                    {
                        /*、アルゴリズムに従ってqの更新をおこなう */
                        if (q < (c[i][k] + c[k][i + j] + 1) && (S[i][i + j][k] == 1))
                        {
                            q = c[i][k] + c[k][i + j] + 1;

                            ans[k] = 1;
                            // printf("k = %d: q = %d = c[%d][%d] + c[%d][%d] + 1 (i = %d,j = %d)\n", k, q, i, k, k, i + j, i, j);
                        }
                        else
                        {
                            // printf("k = %d: q = 0 (i = %d, j = %d)\n", k, i, j);
                        }
                    }
                    else /* Sijが空集合のとき */
                    {
                        q = 0;
                        // printf("S%d_%d is empty\n", i, i+j);
                        break;
                    }
                }
            }

            c[i][i + j] = q; /* 集合Sijに対する最適解のサイズ */
            printf("c[%d][%d+%d] = %d\n", i, i, j, c[i][i + j]);
        }
    }

    /* 出力 */
    printf(" \nNumber of selected activity: %d\n", c[0][n + 1]);
    printf("Selected activity: ");
    for (i = 1; i < n + 2; i++)
    {
        if (ans[i] == 1)
            printf("%d ", i);
    }
    printf("\n");
    return 0;
}

void insert_activ(int c[n + 2][n + 2])
{
    int si[n + 2] = {-1, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12, 16};
    int fi[n + 2] = {0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16, 17};
    int S_empty; /* 両立できる活動がないかどうかを確かめるためのカウンタ */
    int i, j, k;

    for (j = 0; j < n + 2; j++)
    {
        for (i = 0; i < j; i++)
        {
            S_empty = 0;
            for (k = 0; k < n + 2; k++)
            {
                /* 活動kが活動iおよびjと両立可能であるか判定する */
                if ((si[k] > fi[i]) && (fi[k] <= si[j]))
                {
                    S[i][j][k] = 1;
                }
                else
                {
                    S[i][j][k] = 0;
                    S_empty++;
                    if (S_empty == (n + 2))
                        c[i][j] = 0; /* 両立できる活動がない場合は先に最適解を0に */
                }
            }
        }
    }
}