#include <iostream>
#include <vector>
#include <fstream>
#include <omp.h>
#include <time.h>

using namespace std;

void read(vector<double>& vec, int n, int b, string st)
{
	ifstream in(st);
	vec.resize(n * (n + b) / 2);
	for (int i = 0; i < n / b; ++i)
		for (int bi = 0; bi < b; ++bi)
		{
			for (int bj = 0; bj < b * i; ++bj)
				in >> vec.back();

			for (int j = 0; j < n / b - i; ++j)
				for (int bj = 0; bj < b; ++bj)
					in >> vec[(i + j) * b * b * (i + j + 1) / 2 + i * b * b + b * bi + bj];
		}

	in.close();
}

void mult(vector<double>& A, vector<double>& B, vector<double>& C, int n, int b)
{
	// n / b == blockcount
	// b * b == blocksize
	//#pragma omp parallel for schedule(auto)
	for (int i = 0; i < n / b; ++i)
	{
		int ai = i * b * b * (i + 1) / 2 + i * b * b;
		int bi = 0;
		for (int j = 0; j < n / b; ++j)
		{
			int aj = ai - i * b * b;
			int ci = i * b * n + j * b * b;
			int kkk = j;
			int s = 0;
			// #pragma omp parallel for schedule(auto)
			for (kkk; kkk >= i; --kkk)
			{				
				for (int ii = 0; ii < b; ++ii)
					for (int jj = 0; jj < b; ++jj)
						for (int kk = 0; kk < b; kk++)
							C[ci + jj * b + ii] += A[aj + jj + kk * b] * B[bi + kk * b + ii];
				aj += b * b;
				bi += b * b;
			}
			// #pragma omp parallel for schedule(auto)
			for (kkk; kkk >= 0; --kkk)
			{				
				for (int ii = 0; ii < b; ++ii)
					for (int jj = 0; jj < b; ++jj)
						for (int kk = 0; kk < b; kk++)
							C[ci + jj * b + ii] += A[aj + jj * b + kk] * B[bi + kk * b + ii];
				aj += b * b * (s++ + 1);
				bi += b * b;
			}
		}
	}
}

int main()
{
	int n = 2880;
	int b = 80;
	vector<double> A;
	vector<double> B;
	read(A, n, b, "a.txt"); // simetric
	read(B, n, b, "b.txt"); // down treangualr
	vector<double> C(n * n);

	int t=clock();
    mult(A, B, C, n, b);
    cout<<clock()-t<<endl;

	return 0;
}

