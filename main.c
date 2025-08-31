#include <stdio.h>
#include <stdlib.h>
#include "japcode.h"

FILE *destFile;
unsigned char *japCode;


int main (int argc, char *argv[]) {
	
	// Check arguments number
	
	if (argc != 2) {
		fprintf (stderr, "Invalid number of arguments\n");
		fprintf (stderr, "Usage: %s <target file>\n", argv[0]);
		exit (EXIT_FAILURE);
	}
	
	// Open destination file
	
	destFile = fopen(argv[1], "r+b");
	
	// Write 11760 byte patch to destination file
	japCode = getJapCode ();
	fwrite (japCode, sizeof japCode[0], 11760, destFile);
	printf ("Patch successfully implementated to %s\n", argv[1]);
	
	// Close destination file
	
	fclose (destFile);
	
	return 0;
}
