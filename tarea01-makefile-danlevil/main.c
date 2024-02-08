/*
	Codigo Principal
	Tarea01
*/

#include <distance.h>

float miles_fact = 1.609;

int main(void) {
	float kilometers, miles;
	
	load_value(&kilometers);
	miles = convert_to_miles(kilometers);
	
    printf("\n>>> %.2f Kms. to miles are %.2f.\n", kilometers, miles);
    return 0;
}