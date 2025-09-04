#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/region.h"

FILE *destFile = NULL;
unsigned char *regionCode = NULL;

int main (int argc, char *argv[]) {
	
	int num = 0;
	// Check arguments number
	
	if (argc < 2 || argc > 3) {
		fprintf (stderr, "Invalid number of arguments\n");
		fprintf (stderr, "Usage: %s [option] <target file>\n", argv[0]);
		fprintf (stderr, "Options:\n  --jp\n  --eu\n  --us\n");
		fprintf (stderr, "Default option: --jp\n\n");
		exit (EXIT_FAILURE);
	}
	
	// Open destination file and check it's existance
	
	if (argc == 2) {
		destFile = fopen(argv[1], "r+b");
	}
	else {
		destFile = fopen(argv[2], "r+b");
	}
	
	if (destFile == NULL) {
		perror("Failed");
		exit (EXIT_FAILURE);
	}
	
	// Check choosed option
	
	if (argc == 2) {
		regionCode = getJapCode();
	}
	else {
		if (!strcmp(argv[1], "--jp")) {
			num = 1;
		}
		else if (!strcmp(argv[1], "--eu")) {
			num = 2;
		}
		else if (!strcmp(argv[1], "--us")) {
			num = 3;
		}
		
		switch (num) {
		case 1:
			regionCode = getJapCode();
			break;
		case 2:
			regionCode = getEUCode();
			break;
		case 3:
			regionCode = getUSCode();
			break;
		default:
			fprintf (stderr, "Wrong option\n");
			exit (EXIT_FAILURE);
		}
	}
	
	// Write 11760 byte patch to destination file
	fwrite (regionCode, sizeof regionCode[0], 11760, destFile);
	if (argc = 2) {
		printf ("Patch successfully implementated to %s\n", argv[1]);
	}
	else {
		printf ("Patch successfully implementated to %s\n", argv[2]);
	}
	// Close destination file
	
	fclose (destFile);
	
	return 0;
}
