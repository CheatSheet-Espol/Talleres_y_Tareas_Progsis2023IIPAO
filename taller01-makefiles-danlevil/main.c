/*
	Description: 	main.c file of program that count
			the number of words in a file.
	Last modify: 	2022-06-15
	Modify by: 	@rafariva
*/

#include "functions.h"

int main(){
	char file_name[MAXWORD];
	char word[MAXWORD];
	FILE *fileptr;

	/* Ask user to input a file name */
	printf("Please, enter a file name: ");
	scanf("%s", file_name);
	//fscanf(stdin,"%s",file_name);
	// check: https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm

	/* Reading file */
	printf("Reading file %s...\n", file_name);
	fileptr = fopen(file_name, "r");

	/* If file doesnt exists o could be open, fopen returns NULL */
	if (fileptr == NULL){
		//printf("ERROR: Could not open file %s\n", file_name)
		fprintf(stderr,"ERROR: The file '%s' doesnt exits\n", file_name);
		return 1;
	}

	int total_words = count_words(fileptr);

	if (total_words > 0)
		printf("The file '%s' has %d words.\n", file_name, total_words);
	else
		fprintf(stderr, "WARNING: File not found or NO words found.\n");

	fclose(fileptr);

	return 0;
}
