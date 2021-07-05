/**************************************
 * Algorithms, 2020-2021              *
 * Set 1, Exercise 1: Roadtrip        *
 * Polyvios Papakonstantinou 03114892 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

// Global declarations.
int N, K, D, T, Ts, Cs, Tf, Cf, lowP, longPath;

// Basic function for swapping two elements. 
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Basic comperator function for qsort();
int cmp (const void *a, const void *b) {
   return ( *(int*)a - *(int*)b );
}

/*
 * A "custom" function for QuickSort an 2D array,
 * based on its 1st column.
 */
void quicksort(int array[N][2], int first, int last) {
	int i, j, pivot, temp1, temp2;

	if (first < last) {
    	pivot = first;
    	i = first;
    	j = last;

    	while (i < j) {
			while ((array[i][0] <= array[pivot][0]) && (i < last)) {
				i++;
			}
        
			while (array[j][0] > array[pivot][0]) {
				j--;
			}

			if (i < j) {
				temp1 = array[i][0];
				temp2 = array[i][1];

				array[i][0] = array[j][0];
				array[i][1] = array[j][1];

				array[j][0] = temp1;
				array[j][1] = temp2;
			}
		}

		temp1 = array[pivot][0];
		temp2 = array[pivot][1];

		array[pivot][0] = array[j][0];
		array[pivot][1] = array[j][1];

		array[j][0] = temp1;
		array[j][1] = temp2;

		quicksort(array, first, j - 1);
		quicksort(array, j + 1, last);
	}
}

/*
 * A function to calculate the time needed between two stations.
 * We have two possible scenarios:
 * When the if statement is true, we have the fuels needed to drive the
 * path in sport speed, for minimum time.
 * In any other case, we have to find the exact distance we have to drive
 * in eco mode (ecoPath) and the rest in sport. 
 */
float calcTime(int currPath, int avFuel) {
	int returnTime, ecoPath;
	
	if (avFuel >= currPath * Cf) {
		returnTime = currPath * Tf;
	} else {
		ecoPath = (avFuel - (Cs * currPath)) / (Cf * Cs);
		returnTime = ecoPath * Tf + (currPath - ecoPath) * Ts;
	}

	return returnTime;
}

/**************************************************************************************/

int main(int argc, char *argv[]) {

	int i, j;
	float currTime;

	// Let's start reading the input.
	scanf("%d", &N);
	scanf("%d", &K);
	scanf("%d", &D);
	scanf("%d", &T);

	int cars[N][2];
	for (i = 0; i < N; ++i) {
		scanf("%d", &cars[i][0]);
		scanf("%d", &cars[i][1]);
	}

	int stations[K + 1];
	for (j = 0; j < K; ++j) {
		scanf("%d", &stations[j]);
	}

	scanf("%d", &Ts);
	scanf("%d", &Cs);
	scanf("%d", &Tf);
	scanf("%d", &Cf);

	stations[K] = D;

	// We will first sort our 2 arrays.
	qsort(stations, K + 1, sizeof(int), cmp);
	quicksort(cars, 0, N - 1);

	/*
	 * We will search the longest path between two
	 * stations.
	 */
	longPath = stations[0];
	if (K == 1) {
		if (stations[0] <= stations[1] - stations[0]) {
			longPath = stations[1] - stations[0];
		}
	} else {
		for (j = 1; j < K + 1; ++j) {
			if (stations[j] - stations[j - 1] >= longPath) {
				longPath = stations[j] - stations[j - 1];
			}
		}
	}

	lowP = -1;

	for (i = 0; i < N; ++i) {
		/*
		 * Make sure that the fuels capacity of the car is
		 * enough for the longest path.
		 */
		if ((cars[i][1] >= longPath * Cs)&&((cars[i][0] < lowP)||(lowP == -1))) {
			currTime = 0;
			for (j = 1; j < K + 1; ++j) {
				currTime = currTime + calcTime(stations[j] - stations[j - 1], cars[i][1]);
				if (currTime > T) {
					break;
				}
			}
			if (currTime <= T) {
				lowP = cars[i][0];
				break;
			}
		}
	}

	printf("%d\n", lowP);
 }