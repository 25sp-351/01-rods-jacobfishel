#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "functions.h"


int main() {

    float rod_length;
    printf("Input rod length: ");
    scanf("%f", &rod_length);

    int rows          = 2;
    int cols          = 2;
    int size_of_array = 0;
    int position      = 0;
    float length;
    float value;

    float **length_and_value = malloc(rows * sizeof(float *));
    
    if (!length_and_value) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    while (true) {
        printf("Input length and value of rod pieces (format: length, value),");
        printf(" -1 to exit: ");
        if (scanf("%f, %f", &length, &value) != 2 || length == -1 ||
            value == -1) {
            break;
        }

        if (size_of_array == rows) {
            rows *= 2;

            float **temp = realloc(length_and_value, rows * sizeof(float *));

            if (!temp) {
                printf("Realloc failed.\n");
                for (int j = 0; j < size_of_array; j++)
                    free(length_and_value[j]);
                free(length_and_value);
                return -1;
            }
            length_and_value = temp;
        }

        length_and_value[position] = malloc(cols * sizeof(float));

        if (!length_and_value[position]) {
            printf("Memory allocation failed.\n");
            for (int j = 0; j < size_of_array; j++)
                free(length_and_value[j]);
            free(length_and_value);
            return -1;
        }

        length_and_value[position][0] = length;
        length_and_value[position][1] = value;
        size_of_array++;
        position++;
    }

    write_cutting_lists(rod_length, length_and_value, size_of_array);
    float rod_price = calculate_rod_price(rod_length, length_and_value, size_of_array, 0);
    printf("\n\nValue: %.2f", rod_price);

    for (int i = 0; i < size_of_array; i++)
        free(length_and_value[i]);
    free(length_and_value);
}
