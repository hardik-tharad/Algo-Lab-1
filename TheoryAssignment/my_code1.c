// Returns count of all possible parenthesizations that lead to true with OR
#include <stdlib.h>
#include <stdio.h>
//T[i][j] stores the number of ways of parenthesizing the expression from i...j such that it evaluates T
int countParenth(char expression[], int n)
{
    int i,j,g,gap;
    int F[n][n], T[n][n];
    for (i = 0; i < n; i++)
    {
        F[i][i] = (expression[i] == 'F')? 1: 0;
        T[i][i] = (expression[i] == 'T')? 1: 0;
    }
    for (gap=1; gap<n; ++gap)
    {
        for (i=0, j=gap; j<n; ++i, ++j)
        {
            T[i][j] = 0;
            F[i][j] = 0;
            for (g=0; g<gap; g++)
            {
                // Find place of parenthesization using current value of gap
                int k = i + g; 
                // Store Total[i][k] and Total[k+1][j]
                int tik = T[i][k] + F[i][k];
                int tkj = T[k+1][j] + F[k+1][j];
                // Follow the recursive formula
                F[i][j] += F[i][k]*F[k+1][j];
                T[i][j] += (tik*tkj - F[i][k]*F[k+1][j]);
            }
        }
    }
    return T[0][n-1];
}
int main()
{
    printf("Enter Expression in term of T and F only (e.g FTTF would mean F|T|T|F) (less than 100 characters) = ");
    char expression[100];
    scanf("%s", expression);
    int i,n;
    for(i=0; expression[i]!='\0'; ++i);
        n = i;
    printf("Entered Expression = %s\nNumber of characters in expression = %d\nNumber of possible parenthesizations = %d\n", expression, n, countParenth(expression, n));
    return 0;
}