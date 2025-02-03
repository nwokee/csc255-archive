#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include "list.h"

//******************************************************************************

int const OneMillion = 1000000;

using namespace std;

//******************************************************************************

double
msDiffTime(struct timespec start, struct timespec finish) {
    long seconds = finish.tv_sec - start.tv_sec;
    long ns = finish.tv_nsec - start.tv_nsec;

    if (start.tv_nsec > finish.tv_nsec) { // clock underflow
        --seconds;
        ns += 1000000000;
    }
    return(1000.0*((double)seconds + (double)ns/(double)(1000000000)));
}

//******************************************************************************

int main(int argc, char *argv[]) {
    int rc = 0;
    int count;
    int cadence;
    struct timespec tStart, tPrevious, tCurrent;

    list *myList;

    if (argc > 1) {
	if ((sscanf(argv[1], "%d", &count) == 1) && (count >= 0)) {
	    cadence = count / 10;
	    if (cadence == 0) {
		cadence = 2;
	    }
	    myList = new list(count);

	    srand(1); // set the seed

	    // Get the start time
	    clock_gettime(CLOCK_MONOTONIC, &tStart);
	    tPrevious = tStart;
	    for (int key = 0; key < count; key++) {
		if (!myList->insert(key)) {
		    cerr << "Failed insert at " << key << endl;
		    rc = -1;
		    break;
		}

		if (key && (key % cadence == 0)) {
		    clock_gettime(CLOCK_MONOTONIC, &tCurrent);
		    cout << "key " << key << " took ";
		    cout << setw(5) << msDiffTime(tPrevious, tCurrent)/1000.0;
		    cout << " seconds since last milestone" << endl;

		    tPrevious = tCurrent;
		}
	    }

	    cout << "All done in ";
	    cout << setw(5) << msDiffTime(tStart, tCurrent)/1000.0 << " seconds" << endl;
	}
    }

    return rc;
}
