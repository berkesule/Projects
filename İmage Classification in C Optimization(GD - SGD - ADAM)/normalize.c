#include <stdio.h>
#include <stdlib.h>

#define PIXEL_COUNT (28 * 28) 

int main() {
    char *input_file_path = "output.txt";  
    char *output_file_path = "normalized_output.txt"; 
    int i,j;

    FILE *input_file = fopen(input_file_path, "r");
    FILE *output_file = fopen(output_file_path, "w");

    int label;                
    int pixels[PIXEL_COUNT];  

    while (fscanf(input_file, "%d", &label) == 1) { 
        fprintf(output_file, "%d ", label); 
        for (i = 0; i < PIXEL_COUNT; i++) {
            float normalized_pixel = pixels[i] / 255.0f;
            fprintf(output_file, "%.6f ", normalized_pixel); 
        }
        fprintf(output_file, "\n"); 
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}

