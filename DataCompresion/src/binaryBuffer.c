#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "binaryBuffer.h"


#define UNIT 1


bbufer = newBuffer32(int init_value){
    bbufer myBuffer = NULL;
    myBufffer = calloc(1, sizeof(uint32_t));

    if(init_value)
        return myBufffer;

    *myBufffer = init_value;
    return myBufffer;
}
