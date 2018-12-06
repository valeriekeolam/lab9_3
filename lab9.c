/*
 *Location: Temple University Computer Science
 *Programmer: Valerie Lam
 *Class: Introduction to Programming in C 1057, Fall 2018
 *Assignment: Lab #9 - Bubble CSV and GitHub
 *Date: December 5th, 2018
 *Version: 1
 *Description: Organize and combine the data of two files and print it to a single output file.
 *Then, use GitHub to create a repository, and submit that.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_QUESTIONS_PER_STUDENT 11
#define PROGRAMMER_NAME "Valerie Lam"
#define NAME_LEN 40

void display_startup_banner (void);
void process_OMR_data (char *fname, char *fname2);

int
main ( )
{
	int i, students;
	int wrong_total [NUMBER_OF_QUESTIONS_PER_STUDENT] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	display_startup_banner ( );
	process_OMR_data ("newomr.txt", "test_taker_names.txt");

	return EXIT_SUCCESS;
}


/*
 *Function: display_startup_banner
 *Programmer: Valerie Lam
 *Date: September 26th, 2018
 *Inputs: None.
 *Outputs: None.
 *Globals: PROGRAMMER_NAME - includes name of program author.
 *Returns: None.
 *Description: Displays startup text stating program's purpose, author, and time.
 */

void
display_startup_banner(void)
{
         puts("\nCREATING A CSV FILE.");
         puts("---------------------------------------");

         printf("\nProgram written by %s.\n", PROGRAMMER_NAME);
         printf("Program compiled on %s at %s.\n", __DATE__, __TIME__);
}



/*
 *Function: process_OMR_data
 *Programmer: Valerie Lam
 *Date: November 28th, 2018
 *Inputs: fname - a string that contains a file name.
 *	  fname2 - a string that contains another name file.
 *Outputs: None.
 *Globals: None.
 *Returns: None.
 *Description: This function reads in the answer key from the fname, then scans the ID2 from fname2. It will proceed
 *	       to find a matching ID from fname. When a match is found, the ID and name are printed to the output file,
 * 	       as well as the answers from fname.
 */

void
process_OMR_data (char *fname, char *fname2)
{
	int id, id2, i, v;
	char key [NUMBER_OF_QUESTIONS_PER_STUDENT];
	char key2 [NUMBER_OF_QUESTIONS_PER_STUDENT];
	char scores [NUMBER_OF_QUESTIONS_PER_STUDENT];
	char name[NAME_LEN];
	char buffer[NAME_LEN];

	FILE *IN;
	IN = fopen (fname, "r");		//The "r" indicates that data is meant to be read in from the file opened.
	FILE *IN2;
	IN2 = fopen (fname2, "r");
	FILE *OUT;
	OUT = fopen ("full_data.csv", "w");


	//In the event that either file cannot be found, the following messages will print off.
	if (!IN) {
		printf ("Error opening input file titled \"%s\".");
		perror (fname);
	}

	if (!IN2) {
		printf ("Error opening input file titled \"%s\".");
		perror (fname2);
	}

	/*Scans in the first line of fname. With regard to newomr.txt,
	 *it will scan in the standard ID of 0, and the answer key.
	 *This information will not be printed out to the output file, full_data.csv.
	 */
	fscanf(IN, "%d", &id);
	printf ("\nStandard ID: %d\n", id);
	printf ("Scanning in key from %s...\n", fname);
	for (i = 0; i < NUMBER_OF_QUESTIONS_PER_STUDENT; i++) {
		fscanf (IN, "%c", &key[i]);
	}

	//Prints out what the first row of the csv file should be. These are the "categories".
	fprintf (OUT, "IDENTITY,NAME,Q1,Q2,Q3,Q4,Q5,Q6,Q7,Q8,Q9,Q10,Q11\n");

	/*The first while loop will scan in IDs from fname2, print that ID, then open fname,
	 *so long as there is a line to scan, or the end of file has not been reached.
	 */
	while (fscanf (IN2, "%d", &id2) == 1) {
		printf("ID2: %d\n", id2);
		IN = fopen(fname, "r");
		/*This while loop will scan in the ID from fname, which contains the ID and answers.
		 *It will print that ID, and if ID2  matches, it will scan in the name from fname2,
		 *then scan and print off the answers. Then the loop breaks so that the next ID2 from
		 *fname2 can be matched. If it doesn't match, the answers are scanned in,
		 *but not printed to the output file. Scanning in the answers moves the pointer in fname
		 *to the next line to check if the next ID is a match.
		 */
		while (fscanf (IN, "%d", &id)) {
			printf("Current ID: %d\n", id);
			if (id != id2) {
				fgets(buffer, NAME_LEN, IN);
				printf("%s\n",buffer);
				printf ("No match.\n");
			}
			else {
				puts ("ID Match. Printing to output file.");
				fprintf (OUT, "%d,", id);
				fgets (name, NAME_LEN, IN2);
				name [strlen(name) - 1] = 0;
				fprintf (OUT, "%s,", name);

				for (v = 0; v < (NUMBER_OF_QUESTIONS_PER_STUDENT - 1); v++ ) {
					fscanf (IN, "%c", &scores [v]);
					fprintf (OUT, "%c,", scores [v]);
				}
				while (v == (NUMBER_OF_QUESTIONS_PER_STUDENT - 1)) {
					fscanf (IN, "%c", &scores [v]);
                                        fprintf (OUT, "%c\n", scores [v]);
					v++;
                                }
				break;
			}
		}
	}
}
