#include <stdio.h>

int main(int argc, char *args[]) {
	int distance = 100;
	float power = 2.345f;
	double super_power = 56789.4532;
	char initial = 'A';
	char first_name[] = "Angel";
	char last_name[] = "Recinos";

	printf("You are %d miles away.\n",distance);
	printf("not typing this all cuz i already understand this :D\n");
	
	// this does not make sense just showing strange things
	int bugs = 100;
	char nul_byte = '\0';
	int care_percentage = bugs * nul_byte;
	printf("Which means you should care: %d%%.\n", care_percentage);
	printf("Null byte, %%s: %s, %%c:%c\n", nul_byte, nul_byte);

	return 0;
}
