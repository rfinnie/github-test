/*
 * dbm2std.c: simple program to convert the dbm type access files to
 *            the traditional flat access type files.
 * 
 *  6-8-95    Written by Stanford S. Guillory 
 */

#include "config.h"
#include "portability.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef GDBM_NDBM
# include <gdbm-ndbm.h>
#endif /* GDBM_NDBM */
#ifndef GDBM_NDBM
# include <ndbm.h>
#endif /* GDBM_NDBM */

#define MAX_STRING_LEN 256

void usage(char* s) 
{
    fprintf(stderr,"Usage: %s dbm-file flat-file\n", s);
    exit(1);
}

int main (int argc, char *argv[]) 
{
    FILE *std_fp;
    DBM  *db;
    datum dtKey, dtRec;
    char rec[MAX_STRING_LEN];
    char key[MAX_STRING_LEN];
    int  ndx;

    if (argc != 3) 
	usage(argv[0]);

    if (!(std_fp = fopen(argv[2], "w"))) {
	fprintf(stderr,"%s: Could not open file %s for writing.\n",
		argv[0],argv[2]);
	perror("fopen");
	exit(1);
    }

    if (!(db = dbm_open (argv[1], O_RDONLY, 0))) {
	fprintf(stderr,"%s: Could not open database file %s.\n", 
		argv[0], argv[1]);
        exit(1);
    }

    for (dtKey = dbm_firstkey(db); dtKey.dptr; dtKey = dbm_nextkey(db)) {
	dtRec = dbm_fetch (db, dtKey);

        strncpy(key, (char *)dtKey.dptr, dtKey.dsize);
        key[dtKey.dsize] = '\0';

        strncpy(rec, (char *)dtRec.dptr, dtRec.dsize);
        rec[dtRec.dsize] = '\0';

	printf ("Storing data <%s> with key <%s>\n",
		rec, key);
	if (strchr (rec, ' '))
	    fprintf (std_fp,"%s: %s\n", key, rec);
	else
	    fprintf (std_fp,"%s:%s\n", key, rec);
    }

    dbm_close(db);
    exit(0);
}
