/**************************************
 * Algorithms, 2020-2021              *
 * Set 2, Exercise 1: Chem            *
 * Polyvios Papakonstantinou 03114892 *
 **************************************/

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

// Global declarations.
int N, K, A[2501][2501], cost[2501][2501], DPfin[2501][701];

int min(int a, int b) {
	if (a >= b) {
		return b;
	} else {
		return a;
	}
}

// A function for initializing our matrices.
void init() {
	int i, j;

	for (i = 0; i < N; ++i){
		for(j = 0; j < N; ++j) {
			A[i][j] = 0;
			cost[i][j] = 0;
		}  
	}
}

/*
 * Part of the solution below taken from this article:
 * https://www.geeksforgeeks.org/submatrix-sum-queries/
 */

void preProcess() {
	int i, j;

	for (i = 0; i <= N; i++) { 
		cost[0][i] = A[0][i];
	}

	// Do column wise sum.
	for (i = 1; i <= N; i++) {
		for (j = 0; j <= N; j++) {
			cost[i][j] = A[i][j] + cost[i-1][j];
		}
	}

	// Do row wise sum.
	for (i = 0; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			cost[i][j] = cost[i][j] + cost[i][j-1];
		}
	}
}

int sumQueryC(int tli, int tlj, int rbi, int rbj) {
	int res = cost[rbi][rbj];

	if (tli > 0) {
		res = res - cost[tli-1][rbj];
	}

	if (tlj > 0) {
		res = res - cost[rbi][tlj-1];
	}

	if ((tli > 0)&&(tlj > 0)) {
		res = res + cost[tli-1][tlj-1];
	}
 
	return res;   
}

/*
 * Our custom DP function for solving the problem.
 * First we cover specific sub-problems and then
 * the generic cases.
 */
int customDP() {
	int i, j, l_prev, l, sum;

	for (i = 1; i <= N; i++) {
		DPfin[i][0] = 0;
	}

	for (i = 1; i <= N; i++) {
		DPfin[i][1] = cost[i][i];
	}

	for (j = 0; j <= K; j++) {
		DPfin[0][j] = 0;
	}

	for (j = 1; j <= K; j++) {
        DPfin[1][j] = 0;
    }

	for (i = 2; i <= N; i++) {
		l_prev = 0;
		for (j = 2; j <= K; j++) {
			DPfin[i][j] = INT_MAX;

			for (l = l_prev; l < i; l++) {
				sum = sumQueryC(l+1, l+1, i, i);

				if (DPfin[i][j] > sum + DPfin[l][j - 1]) {
					DPfin[i][j] = sum + DPfin[l][j - 1];
					l_prev = l;
				}
            }
        }
    }

    return DPfin[N][K];
}   

/**************************************/

int main() {
	int i, j, ans;

	// Initialize our arrays...
	init();

	// Start reading input...  
	scanf("%d", &N);
	scanf("%d", &K); 
	
	for (i = 0; i < N; ++i) {
		for (j = 1+i; j < N; ++j) {
			scanf("%d", &A[i+1][j+1]);
		}
	}

	preProcess();

	ans = customDP();  
	
	printf("%d\n", ans);  
}  