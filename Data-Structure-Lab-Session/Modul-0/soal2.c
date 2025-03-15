#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct dynamicarr_t {
    int *_arr;
    unsigned _size, _capacity;
} DynamicArray;

bool dArray_isEmpty(DynamicArray *darray) {
    return (darray->_size == 0);
}

void dArray_insertAt(DynamicArray *darray, unsigned index, int value) {
    if (darray->_size + 1 > darray->_capacity) {
        unsigned it;
        darray->_capacity *= 2;
        int *newArr = (int*) malloc(sizeof(int) * darray->_capacity);

        for (it=0; it < darray->_size; ++it)
            newArr[it] = darray->_arr[it];
        
        int *oldArray = darray->_arr;
        darray->_arr = newArr;
        free(oldArray);
    }
    for(unsigned it = darray->_size + 1; it > index; it--) {
        darray->_arr[it] = darray->_arr[it - 1];
    }
    darray->_arr[index] = value;
    darray->_size++;
}

void dArray_removeAt(DynamicArray *darray, unsigned index) {
    if (!dArray_isEmpty(darray)) {
        for(unsigned it = index; it < darray->_size; it++) {
            darray->_arr[it] = darray->_arr[it + 1];
        }
        darray->_size--;
        if (darray->_size <= darray->_capacity/2) {
            unsigned it;
            darray->_capacity /= 2;
            int *newArr = (int*) malloc(sizeof(int) * darray->_capacity);

            for (it=0; it < darray->_size; ++it)
                newArr[it] = darray->_arr[it];
        
            int *oldArray = darray->_arr;
            darray->_arr = newArr;
            free(oldArray);
        }
    } else return;
}

int main() {
    
}