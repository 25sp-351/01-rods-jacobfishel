#ifndef FUNCTIONS_H
#define FUNCTIONS_H

float calculate_rod_price(float rod_length, float **length_and_value,
                          int size_of_array, float remainder);

void write_cutting_lists(float rod_length, float **length_and_value,
                          int size_of_array);

#endif // FUNCTIONS_H
