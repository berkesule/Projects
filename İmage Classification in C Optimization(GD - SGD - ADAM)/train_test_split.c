#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PIXEL_COUNT (28 * 28) 

int main() {
	int i,j;
    char *input_file_path = "normalized_output.txt";  
    char *train_file_path = "train.txt";             
    char *test_file_path = "test.txt";               

    FILE *input_file = fopen(input_file_path, "r");
    FILE *train_file = fopen(train_file_path, "w");
    FILE *test_file = fopen(test_file_path, "w");

    srand(time(NULL));

    int label;
    float pixels[PIXEL_COUNT];
    int train_count = 0, test_count = 0;

    while (fscanf(input_file, "%d", &label) == 1) {

        if (rand() % 100 < 80) {

            fprintf(train_file, "%d ", label);
            for (i = 0; i < PIXEL_COUNT; i++) {
                fprintf(train_file, "%.6f ", pixels[i]);
            }
            fprintf(train_file, "\n");
            train_count++;
        } else {
            fprintf(test_file, "%d ", label);
            for (i = 0; i < PIXEL_COUNT; i++) {
                fprintf(test_file, "%.6f ", pixels[i]);
            }
            fprintf(test_file, "\n");
            test_count++;
        }
    }

    printf("Eðitim verisi: %d \n", train_count);
    printf("Test verisi: %d \n", test_count);

    fclose(input_file);
    fclose(train_file);
    fclose(test_file);

    return 0;
}

