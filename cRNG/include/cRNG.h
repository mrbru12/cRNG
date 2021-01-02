#pragma once

/*
Copyright (c) 2020-2021 Bruno Moretto M.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
