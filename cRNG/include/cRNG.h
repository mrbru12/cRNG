#pragma once

#include <stdlib.h>
#include <memory.h>

// >>> TODO
// void crng_init()
// float crng_next_float()
// double crng_next_double()

// =============================================
//                 INT FUNCTIONS
// =============================================
 
int crng_next_int(int from, int to)
{
    int min_val = min(from, to);
    int max_val = max(from, to);

    if (min_val < 0)
        max_val += abs(min_val);

    max_val += (max_val < 0) ? -1 : 1;
    
    return min_val + rand() % max_val;
}

int crng_next_bool()
{
    return crng_next_int(0, 1);
}

// =============================================
//                ARRAY FUNCTIONS
// =============================================

// Fisher-Yates array shuffle
void* crng_shuffle(void* source, size_t size, size_t type_size)
{
    char* temp_val = (char*)malloc(type_size);
    
    for (int i = size / type_size - 1; i >= 0; i--)
    {
        int j = crng_next_int(0, i);
        
        memcpy(temp_val, (char*)source + j * type_size, type_size);
        memcpy((char*)source + j * type_size, (char*)source + i * type_size, type_size);
        memcpy((char*)source + i * type_size, temp_val, type_size);
    }

    free(temp_val);

    return source;
}

void* crng_choice(void* source, size_t size, size_t type_size)
{
    return &(((char*)source)[crng_next_int(0, size / type_size - 1) * type_size]);
}
