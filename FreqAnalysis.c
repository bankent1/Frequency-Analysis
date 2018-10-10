/*

FreqAnalysis [file.txt]

Author: Travis Banken

This program will read a file given through the command line and calculate the
occurance frequency of the standard a-z letters (NOT case-sensitive). The result is printed to the 
console.

*/

#include <stdio.h>
#include <stdlib.h>

void fileAnalysis(FILE*, int[]);
int findTotalLetters(int[]);
int* sort(int[], int);

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("Missing arguments!\n");
		printf("Usage: FreqAnalysis [filename.txt] where filename is input file to be analyzed.\n\n");
		exit(1);	
	}
	
	// analzye each file given
	int lettCount[26] = {0};
	for (int i = 1; i < argc; i++) {	
		printf("Analyzing %s........", argv[i]);
		FILE *filename = fopen(argv[i], "r");
		fileAnalysis(filename, lettCount);	
		printf("Done\n");
		fclose(filename);
	}

	// Print Results and find total counts	
	int totLett = findTotalLetters(lettCount);
	int *pos = sort(lettCount, 26);
	printf("\nLETTER\t\tCOUNT\t\tFREQUENCY\n");
	for (int i = 0; i < 26; i++) {
		double freq = 100 * ((double)lettCount[i])/totLett;
		printf("%c:\t\t%d\t\t%.2lf%%\n", pos[i]+65, lettCount[i], freq);
	}

}

/*
Reads a file one char at a time and counts the occurances of each letter.

Params: filename - string of the file name to be read from
	lettCount - int array countaing the count for all letter of alphabet.
*/
void fileAnalysis(FILE *filename, int lettCount[]) {
	int c;
	
	if (filename == NULL) {
		printf("\n*** ERROR: FILE NOT FOUND ***\n");
		exit(1);
	}	

	// read the file
	while ((c = getc(filename)) != EOF) {
		// first check for capital letter, then lowercase
		if (c >= 65 && c <= 90) {
			lettCount[c-65] = lettCount[c-65] + 1;
		}
		else if (c >= 97 && c <= 122) {
			lettCount[c-97] = lettCount[c-97] + 1;
		}
	}

}

/*
Returns the total number of letters read in the file.

Params: lettCount - int array containing the count for all letters of the alphabet.
*/
int findTotalLetters(int lettCount[]) {
	int sum = 0;
	for (int i = 0; i < 26; i++) {
		sum += lettCount[i];
	}
	return sum;	
}

/*
Sorts the given array using insertion sort algorithm.

Params: arr - int array to be sorted
Returns: int array contianing the sorted letter values (i.e. A, B, ...)
*/
int* sort(int arr[], int size) {
	static int pos[26] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
			 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

	for (int i = 1; i < size; i++) {
		int j = i;
		while (j != 0 && arr[j] > arr[j-1]) {
			// swap values
			int temp = arr[j];
			arr[j] = arr[j-1];
			arr[j-1] = temp;
			// swap position
			temp = pos[j];
			pos[j] = pos[j-1];
			pos[j-1] = temp;
			j--;
		}	
	} // end for	
	return pos;
}
