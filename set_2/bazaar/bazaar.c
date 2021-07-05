/**************************************
 * Algorithms, 2020-2021              *
 * Set 2, Exercise 2: Bazaar          *
 * Polyvios Papakonstantinou 03114892 *
 **************************************/
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

// Global declarations.
unsigned int N, M, _1A[1500][2], _1B[1500][2], _1C[1500][2], _2A[1500][2], _2B[1500][2], _2C[1500][2], _3A[1500][2], _3B[1500][2], _3C[1500][2];
unsigned int _1Afin[1501][5001], _1Bfin[1501][5001], _1Cfin[1501][5001], _2Afin[1501][5001], _2Bfin[1501][5001], _2Cfin[1501][5001], _3Afin[1501][5001], _3Bfin[1501][5001], _3Cfin[1501][5001];

unsigned int min(unsigned int a, unsigned int b) {
	if (a >= b) {
		return b;
	} else {
		return a;
	}
}

/*
 * A custom KnapSack function for our problem.
 * 0 or INT_MAX in K[i][j] means that there is no solution
 * for such i and j.
 * array -> the array in which we have stored our input.
 * cap -> a "pointer" for how many elements of the array we actually use.
 * K -> the array in which we will store the results of our algorithm.
 */
void customKnapSack(unsigned int array[1500][2], unsigned int cap, unsigned int K[1501][5001]) {
	unsigned int i, j;

	//K[i][j] -> the best price for the first i offers, when we want j items.
	for (i = 0; i <= cap; ++i) {
		for (j = 0; j <= N; ++j) {
			if (j == 0) {
				K[i][j] = 0;
			} else if (i == 0) {
				K[i][j] = INT_MAX;
			} else if (j < array[i-1][1]) {
				K[i][j] = min(K[i-1][j], array[i-1][0]);
			} else {
				K[i][j] = min(K[i-1][j], K[i-1][j - array[i-1][1]] + array[i-1][0]);
			}
		}
	}
}

/**************************************/

int main() {
	long int fin;
	unsigned int i, j, k, x;
	unsigned int _1Aptr, _1Bptr, _1Cptr, _2Aptr, _2Bptr, _2Cptr, _3Aptr, _3Bptr, _3Cptr;
	_1Aptr = _1Bptr = _1Cptr = _2Aptr = _2Bptr = _2Cptr = _3Aptr = _3Bptr = _3Cptr = 0;
	char y;

	// Start reading input...
	scanf("%u", &N);
	scanf("%u", &M);

	for (i = 0; i < M; ++i) {
		// xy A P
		// x -> vendor: 1, 2, 3
		// y -> item: A, B, C
		// A -> quantity
		// P -> price
		scanf("%u", &x);
		scanf("%c", &y);

		switch(x) {
			case 1:
				switch(y) {
					case 'A':
						scanf("%u", &_1A[_1Aptr][1]);
						scanf("%u", &_1A[_1Aptr][0]);
						_1Aptr++;
						break;

					case 'B':
						scanf("%u", &_1B[_1Bptr][1]);
						scanf("%u", &_1B[_1Bptr][0]);
						_1Bptr++;
						break;

					case 'C':
						scanf("%u", &_1C[_1Cptr][1]);
						scanf("%u", &_1C[_1Cptr][0]);
						_1Cptr++;
						break;
				}
				break;

			case 2:
				switch(y) {
					case 'A':
						scanf("%u", &_2A[_2Aptr][1]);
						scanf("%u", &_2A[_2Aptr][0]);
						_2Aptr++;
						break;

					case 'B':
						scanf("%u", &_2B[_2Bptr][1]);
						scanf("%u", &_2B[_2Bptr][0]);
						_2Bptr++;
						break;

					case 'C':
						scanf("%u", &_2C[_2Cptr][1]);
						scanf("%u", &_2C[_2Cptr][0]);
						_2Cptr++;
						break;
				}
				break;

			case 3:
				switch(y) {
					case 'A':
						scanf("%u", &_3A[_3Aptr][1]);
						scanf("%u", &_3A[_3Aptr][0]);
						_3Aptr++;
						break;

					case 'B':
						scanf("%u", &_3B[_3Bptr][1]);
						scanf("%u", &_3B[_3Bptr][0]);
						_3Bptr++;
						break;

					case 'C':
						scanf("%u", &_3C[_3Cptr][1]);
						scanf("%u", &_3C[_3Cptr][0]);
						_3Cptr++;
						break;
				}
				break;
		}
	}

	/*
	 * Input was separated for each type of item and each vendor,
	 * meaning we have to use our KnapSack algorithm 9 times.
	 */
	customKnapSack(_1A, _1Aptr, _1Afin);
	customKnapSack(_1B, _1Bptr, _1Bfin);
	customKnapSack(_1C, _1Cptr, _1Cfin);
	unsigned int sets1 = 0;
	/*
	 * Now that we have computed KnapSack for 1st vendor's all items,
	 * find how many sets we can buy from him.
	 */
	for (j = 1; j<= N; ++j) {
		if ((_1Afin[_1Aptr][j] != INT_MAX)&&(_1Bfin[_1Bptr][j] != INT_MAX)&&(_1Cfin[_1Cptr][j] != INT_MAX)) {
			sets1++;
			_1Afin[_1Aptr][j] = _1Afin[_1Aptr][j] + _1Bfin[_1Bptr][j] + _1Cfin[_1Cptr][j];
		} else {
			break;
		}
	}

	customKnapSack(_2A, _2Aptr, _2Afin);
	customKnapSack(_2B, _2Bptr, _2Bfin);
	customKnapSack(_2C, _2Cptr, _2Cfin);
	unsigned int sets2 = 0;
	for (j = 1; j<= N; ++j) {
		if((_2Afin[_2Aptr][j] != INT_MAX)&&(_2Bfin[_2Bptr][j] != INT_MAX)&&(_2Cfin[_2Cptr][j] != INT_MAX)) {
			sets2++;
			_2Afin[_2Aptr][j] = _2Afin[_2Aptr][j] + _2Bfin[_2Bptr][j] + _2Cfin[_2Cptr][j];
		} else {
			break;
		}
	}

	customKnapSack(_3A, _3Aptr, _3Afin);
	customKnapSack(_3B, _3Bptr, _3Bfin);
	customKnapSack(_3C, _3Cptr, _3Cfin);
	unsigned int sets3 = 0;
	for (j = 1; j<= N; ++j) {
		if((_3Afin[_3Aptr][j] != INT_MAX)&&(_3Bfin[_3Bptr][j] != INT_MAX)&&(_3Cfin[_3Cptr][j] != INT_MAX)) {
			sets3++;
			_3Afin[_3Aptr][j] = _3Afin[_3Aptr][j] + _3Bfin[_3Bptr][j] + _3Cfin[_3Cptr][j];
		} else {
			break;
		}
	}

	fin = LONG_MAX;

	// Compute the final answer.
	for (i = 0; i <= sets1; ++i) {
		for (j = 0; j <= sets2; ++j) {
			for (k = 0; k <= sets3; ++k) {
				if (i + j + k == N) {
					if ((_1Afin[_1Aptr][i] + _2Afin[_2Aptr][j] + _3Afin[_3Aptr][k] < fin)&&((_1Afin[_1Aptr][i]!=INT_MAX)||(_2Afin[_2Aptr][j] != INT_MAX)||(_3Afin[_3Aptr][k] != INT_MAX))) {
						fin = _1Afin[_1Aptr][i] + _2Afin[_2Aptr][j] + _3Afin[_3Aptr][k];
					}
				}
			}
		}
	}

	if (fin == LONG_MAX) {
		fin = -1;
	}

	printf("%ld\n", fin);
}