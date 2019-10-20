#include <iostream>
#include <vector>
#include <fstream>
#include <omp.h>
#include <time.h> 

using namespace std;

const int n = 2880;


int main()
{
    double **A = new double*[n];
    double **B = new double*[n];
    double **C = new double*[n];
    ifstream in("a.txt");
    for(int i=0;i<n;++i)
    {
        A[i] = new double [n];
        for(int j=0;j<n;++j)
            in>>A[i][j];
    }
        // for(int j=0;j<r;++j)
        // {
        //     in>>A[i][j];
        //     //cout << A[i][j] << " ";
        // }

    in.close();
    ifstream fi("b.txt");
    for(int i=0;i<n;++i)
    {
        B[i] = new double [n];
        for(int j=0;j<n;++j)
        {
            fi>>B[i][j];
            //cout << B[i][j]<< " ";
        }       
        //cout<<endl;
    }

    fi.close();
    for(int i = 0; i<n;++i)
    {
        C[i] = new double [n];
        for(int j = 0; j<n; ++j)
        {
            C[i][j] = 0;
        }
    }
    srand((time(NULL)));
    time_t start, end;
    start = clock();
    //#pragma omp parallel for schedule(auto)
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            for(int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];  
        }
    }
        
    end = clock();
    printf("%d", (end - start) / (CLOCKS_PER_SEC));
    // for(int i=0;i<n;++i)
    // {
    //    for(int j=0;j<n;++j)
    //    {
    //        cout << C[i][j] << " ";
    //    }
    //    cout<<endl;
    // }
    for(int i=0; i<n; i++)
    {
        delete [] A[i];
        delete [] B[i];
        delete [] C[i];
    }
    delete [] A;
    delete [] B;
    delete [] C;
        
}
