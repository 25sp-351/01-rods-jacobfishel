#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

// Function to calculate rod price
float calculate_rod_price(float rod_length, float **length_and_value,
                          int size_of_array, float remainder) {
    if (size_of_array == 0)
        return 0;

    float rod_length_left          = rod_length;
    float max_val                  = 0;
    float **temp_length_and_values = malloc(size_of_array * sizeof(float *));

    if (!temp_length_and_values) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    for (int i = 0; i < size_of_array; i++)
        temp_length_and_values[i] = NULL;

    float temp_max_val[2]  = {-1, -1};
    int temp_size_of_array = size_of_array;
    float temp_remainder   = remainder;
    int arr_pos            = 0;

    for (int i = 0; i < size_of_array; i++) {

        float length = length_and_value[i][0];
        float value  = length_and_value[i][1];

        if (length > rod_length_left)
            continue;

        float total_value = (floor(rod_length_left / length)) * value;

        if (total_value > max_val) {

            if (temp_max_val[0] == -1) { // first iteration

                max_val         = total_value;
                temp_max_val[0] = length;
                temp_max_val[1] = value;

            } else {

                temp_length_and_values[arr_pos] = malloc(2 * sizeof(float));

                if (temp_length_and_values[arr_pos]) {

                    temp_length_and_values[arr_pos][0] = temp_max_val[0];
                    temp_length_and_values[arr_pos][1] = temp_max_val[1];
                    arr_pos++;
                    max_val         = total_value;
                    temp_max_val[0] = length;
                    temp_max_val[1] = value;
                }
            }

        } else {

            temp_length_and_values[arr_pos] = malloc(2 * sizeof(float));

            if (temp_length_and_values[arr_pos]) {

                temp_length_and_values[arr_pos][0] = length;
                temp_length_and_values[arr_pos][1] = value;
                arr_pos++;
            }
        }
    }

    rod_length_left    = fmodf(rod_length_left, temp_max_val[0]);
    temp_remainder     = rod_length_left;
    temp_size_of_array = arr_pos;

    float result =
        max_val + calculate_rod_price(rod_length_left, temp_length_and_values,
                                      temp_size_of_array, temp_remainder);

    for (int i = 0; i < arr_pos; i++)
        free(temp_length_and_values[i]);
    free(temp_length_and_values);

    return result;
}

void write_cutting_lists(float rod_length, float **length_and_value, int size_of_array) {
    for (int i = 0; i < size_of_array; i++) {

        float length = length_and_value[i][0];
        float value = length_and_value[i][1];
        float total_value = (floor(rod_length / length)) * value;
        float remainder = fmodf(rod_length, length);
        printf("\n%.2f @ %.2f = %.2f", length, value, total_value);
        printf("\nRemainder: %.2f", remainder);
    }

}
