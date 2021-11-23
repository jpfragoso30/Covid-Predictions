#include "../libs/Euler.h"


static inline float suma(float x, float y);



void euler_method(float* x, float* y, float width, uint8_t n){

    for (uint8_t index = 1; index < n; index++) {
        
        y[index] = y[index - 1] + (width * suma(x[index - 1], y[index - 1]));
        x[index] = x[index - 1] + width;
    } 
}


static inline float suma(float x, float y){
    
    return x + y;
}