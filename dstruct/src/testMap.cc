
#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <new.h>

#define srandom	srand48
#define random	lrand48

#include "SArray.h"
#include "LHash.h"

#include "SArray.cc"
#include "LHash.cc"

#define PRINTN	20
#define KEY_T	unsigned int
#define DATA_T	int

#if 0
#define CLASS	LHash
#define MAP_T	CLASS<KEY_T,DATA_T>
#define ITER_T	LHashIter<KEY_T,DATA_T>
#ifdef __GNUG__
INSTANTIATE_LHASH(KEY_T, DATA_T);
#endif
#else
#define CLASS	SArray
#define MAP_T	CLASS<KEY_T,DATA_T>
#define ITER_T	SArrayIter<KEY_T,DATA_T>
#ifdef __GNUG__
INSTANTIATE_SARRAY(KEY_T, DATA_T);
#endif
#endif

static MAP_T myarray;

int compKeys(KEY_T key1, KEY_T key2)
{
	return key2 - key1;
}

void
printmap(MAP_T &myarray)
{
    cout << myarray.numEntries() << " distinct entries" << endl;

    { 
	int i;
	ITER_T myiter(myarray);
	KEY_T key;
	DATA_T *value;

	cout << PRINTN <<  " first keys:";
	for (i = 0; i < PRINTN && myiter.next(key); i++) {
	    cout << " " << key;
	}
	cout << endl;

	cout << PRINTN <<  " first values:";
	myiter.init();
	for (i = 0; i < PRINTN && (value = myiter.next(key)); i++) {
	    cout << " " << *value;
	}
	cout << endl;
    }
}

int sortem(KEY_T k1, KEY_T k2) {
	return k1 - k2;
}

int
main(int argc, char **argv)
{
    int size = 10, delsize;
    int i;
    KEY_T key;
    Boolean found;
    char mapspace[sizeof(MAP_T)];
    MemStats stats;

    /*
     * Test copy/assignment
     */
    {
	MAP_T *another_map;
	another_map = new ((void *)mapspace) MAP_T(11);

	MAP_T yet_another_map(myarray);

	yet_another_map = *another_map;
    }

    if (argc > 1) {
	size = atoi(argv[1]);
    }
    delsize = size/2;
    if (argc > 2) {
	delsize = atoi(argv[2]);
    }

    cout << "sizeof(_Map) = " << sizeof(_Map) << endl;
    cout << "sizeof(myarray) = " << sizeof(myarray) << endl;

    cout << "inserting ..." << endl;

    srandom(0);
    for (i = 1; i <= size; i++) {
	key = random();
	*myarray.insert(key) = i;
	// myarray.dump();
	DATA_T val = *myarray.find(key);
	assert(i == val);
    }

    cout << "checking ..." << endl;

    srandom(0);
    for (i = 1; i <= size; i++) {
	key = random();
	DATA_T *val = myarray.find(key);

	assert (val != 0);
	if (i != *val) {
	    cout << "key " << key << " was overwritten with " << *val << endl;
	}
    }

    printmap(myarray);

    myarray.memStats(stats);
    stats.print();


    cout << "deleting ..." << endl;

    /*
     * now delete half the entries
     */
    srandom(0);
    for (i = 1; i <= delsize; i++) {
	key = random();
	myarray.remove(key, found);
	assert(found);
    }

    cout << "checking ..." << endl;

    /*
     * Check the result
     */
    srandom(0);
    for (i = 1; i <= delsize; i++) {
	key = random();
	myarray.find(key,found);

	assert(!found);
    }
    for (; i <= size; i++) {
	key = random();
	DATA_T *val = myarray.find(key);

	if (val == 0) {
	    cout << "key " << key << " was deleted" << endl;
	} else if (i != *val) {
	    cout << "key " << key << " was reassigned to " << *val << endl;
	}
    }

    printmap(myarray);
    stats.clear();
    myarray.memStats(stats);
    stats.print();

    myarray.clear(0);
    printmap(myarray);


    /*
     * Populate again
     */
    for (i = 1; i <= size; i++) {
	key = i;
	*myarray.insert(key) = i;
    }
    cerr << "numEntries = " << myarray.numEntries() << endl;
    printmap(myarray);

    /*
     * Delete all using iterator
     */
    ITER_T myiter(myarray);
    //ITER_T myiter(myarray, sortem);
    
    i = 0;
    while (myiter.next(key)) {
	myarray.remove(key);
	i++;
    }
    cerr << "deleted " << i << " entries\n";
    cerr << "numEntries = " << myarray.numEntries() << endl;

    printmap(myarray);


    exit(0);
}
