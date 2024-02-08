/*
	Descripcion: functions file that contains the functions for counting words
	Last Modify: 2022-06-15
	Modify by: @rafariva
*/

#include "functions.h"

int count_words(FILE *file){
	int count = 0;
	char palabra[80];

	while ((fscanf(file,"%s",palabra))!=EOF){
		count+=1;
	}

	/* TO-DO: add code for counting words */
	/* TIP: use function fscanf (for read file/words) in a while */

	return count;
}
