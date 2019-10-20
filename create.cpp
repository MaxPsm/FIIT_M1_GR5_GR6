#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;


double randi(double b, double e)
{
    return b + (rand() % (int)((e - b) * 1000)) / 1000.;
}

int main()
{
    int n = 2880;
    double **mtrx = new double*[n];
    srand((time(NULL)));

    FILE *f1 = fopen("a.txt", "w");
    FILE *f2 = fopen("b.txt", "w");
    for (int i = 0; i < n; ++i)
    {
        mtrx[i] = new double [n];
        for (int j = 0; j < n; ++j)
        {
            if (i > j)
            {
                mtrx[i][j] = mtrx[j][i];
                fprintf(f2, "%.2f ", 0.0);
            }
            else
            {
                mtrx[i][j] = randi(-10,10);           
                fprintf(f2, "%.2f ", randi(-10,10));
            }
        }
        fprintf(f2,"\n");
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            fprintf(f1, "%.2f ", mtrx[i][j]);
        fprintf(f1,"\n");
    }
    fclose(f1);
    fclose(f2);
    for(int i=0; i<n; i++)
        delete [] mtrx[i];
    delete [] mtrx;
    return 0;
}
